include Config.mk

SHELL := env PATH=$(TOOLCHAIN):$(PATH) /bin/bash


NEWLIB_ARCH := aarch64-none-circle
CIRCLEHOME  := lib/circle-stdlib/libs/circle
NEWLIBDIR   := lib/circle-stdlib/install/$(NEWLIB_ARCH)

FLASHY_OPTS ?= --cpu-boost:yes \
			   --baud:$(FLASHY_BAUD) \
			   --flashBaud:$(FLASHY_BAUD)

MCUFONT := bin/mcufont
MFDIR := lib/mcufont/decoder
include lib/mcufont/decoder/mcufont.mk

FLASHY_CMD_REBOOT_LOADER := exec "reboot"
FLASHY_CMD_REBOOT := reboot $(FLASHY_REBOOT_MAGIC_WORD)

CXX_SRCS := $(shell find src -type f -name "*.cpp")
C_SRCS := $(shell find src -type f -name "*.c") \
		  $(shell find lib/mcufont/decoder -type f -name "*.c")

OBJS := $(CXX_SRCS:.cpp=.o) \
		$(C_SRCS:.c=.o)

LIBS := $(shell find lib -type f -name "*.a")

include lib/circle-stdlib/Config.mk
include $(CIRCLEHOME)/Rules.mk


# Create an auto-incrementing build number.
BUILD_NUMBER_FILE=build_number.txt
BUILD_NUMBER_LDFLAGS := --defsym __BUILD_DATE=$(shell date +'%Y%m%d')
BUILD_NUMBER_LDFLAGS += --defsym __BUILD_NUMBER=$(shell cat $(BUILD_NUMBER_FILE))
BUILD_NUMBER_LDFLAGS += --defsym __VERSION_MAJOR=$(shell git describe --tags | cut -d"." -f1)
BUILD_NUMBER_LDFLAGS += --defsym __VERSION_MINOR=$(shell git describe --tags | cut -d"." -f2)
BUILD_NUMBER_LDFLAGS += --defsym __VERSION_MICRO=$(shell git describe --tags | cut -d"." -f3 | cut -d"-" -f1)
BUILD_NUMBER_LDFLAGS += --defsym __BUILD_COMMIT=$(shell printf $$((16#`git rev-parse --short HEAD`)))

# Build number file.  Increment if any object file changes.
$(BUILD_NUMBER_FILE): $(OBJS)
	@printf $(shell expr `cat $(BUILD_NUMBER_FILE)` + 1) > $(BUILD_NUMBER_FILE)

CPPFLAGS += --std=gnu++2b \
			-I include \
			-I include/fonts \
		  	-I $(MFINC) \
		  	-I $(NEWLIBDIR)/include \
		  	-I $(STDDEF_INCPATH) \
		  	-I lib/circle-stdlib/include \
			-DSERIAL_BUF_SIZE=4096 \
			-DKERNEL_MAX_SIZE=$(KERNEL_MAX_SIZE) \
			-DMF_RLEFONT_INTERNALS=1 \
			-MMD \
			-O3 \
			-Wno-sign-compare \
			-Wfatal-errors \
			-Wno-unused-function

CFLAGS += -I include \
		  -I include/fonts \
		  -I $(MFINC) \
		  -I $(NEWLIBDIR)/include \
		  -I $(STDDEF_INCPATH) \
		  -I lib/circle-stdlib/include \
		  -DSERIAL_BUF_SIZE=4096 \
		  -DKERNEL_MAX_SIZE=$(KERNEL_MAX_SIZE) \
		  -DMF_RLEFONT_INTERNALS=1 \
		  -MMD \
		  -O3 \
		  -Wno-sign-compare \
		  -Wfatal-errors \
		  -Wno-unused-function

LDFLAGS += $(BUILD_NUMBER_LDFLAGS)

-include $(OBJS:.o=.d)

$(TARGET).img: $(BUILD_NUMBER_FILE)

$(MCUFONT):
	@make -C lib/mcufont
	@cp -f lib/mcufont/encoder/mcufont bin/mcufont

.PHONY:
fonts: $(MCUFONT)
	@make -C fonts
	@make -C fonts install

.PHONY:
bootconfig:
	@echo "Regenerating boot files..."
	@cp -f boot.in/*.bin boot/
	@cp -f boot.in/*.dtb boot/
	@cp -f boot.in/*.dat boot/
	@cp -f boot.in/*.elf boot/
	@cp -f boot.in/*.dtbo boot/

	@FRAMEBUFFER_WIDTH=$(FRAMEBUFFER_WIDTH) \
	 FRAMEBUFFER_HEIGHT=$(FRAMEBUFFER_HEIGHT) \
	 m4 boot.in/config.txt.in > boot/config.txt

	@FRAMEBUFFER_WIDTH=$(FRAMEBUFFER_WIDTH) \
	 FRAMEBUFFER_HEIGHT=$(FRAMEBUFFER_HEIGHT) \
	 m4 boot.in/cmdline.txt.in > boot/cmdline.txt

.PHONY:
clean: distclean font-clean

.PHONY:
font-clean:
	@make -C fonts clean

.PHONY:
distclean:
	@find src -type f -name "*.o" -delete
	@find src -type f -name "*.d" -delete
	@find $(MFDIR) -type f -name "*.o" -delete
	@find $(MFDIR) -type f -name "*.d" -delete
	@rm -f *.elf *.img *.lst *.map *.txz
	@rm -f boot/*
	@rm -f pkg/boot/*

.PHONY:
package: bootconfig $(TARGET).img 
	@echo "Creating archive pkg/Capi.txz"
	@rm -f pkg/boot/*
	@cp boot/* pkg/boot/
	@cp $(TARGET).img pkg/boot
	@tar -C pkg -cJf pkg/Capi.txz boot

.PHONY:
reboot:
	@echo "Rebooting target..."
	@flashy $(FLASHY_TARGET) $(FLASHY_CMD_REBOOT)

.PHONY:
reflash: bootconfig $(TARGET).img reboot
	@flashy $(FLASHY_OPTS) --port:$(FLASHY_TARGET) push boot/cmdline.txt  
	@flashy $(FLASHY_OPTS) --port:$(FLASHY_TARGET) push boot/config.txt
	@flashy $(FLASHY_OPTS) --port:$(FLASHY_TARGET) push images/test/basn2c08.png
	@flashy $(FLASHY_OPTS) --port:$(FLASHY_TARGET) push images/test/sample.png
	@echo "Rebooting target..."
	@flashy $(FLASHY_OPTS) --port:$(FLASHY_TARGET) $(FLASHY_CMD_REBOOT_LOADER)
	@flashy $(FLASHY_OPTS) --port:$(FLASHY_TARGET) flash $(TARGET).img monitor

.PHONY:
bootload: bootconfig reboot 
	@flashy $(FLASHY_TARGET) push boot/*.* $(FLASHY_OPTS) 
	@flashy $(FLASHY_TARGET) push flashy/$(TARGET).img $(FLASHY_OPTS)

.PHONY:
run: reflash