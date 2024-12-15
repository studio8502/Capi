include Config.mk

SHELL := env PATH=$(TOOLCHAIN):$(PATH) /bin/bash


NEWLIB_ARCH := aarch64-none-circle
CIRCLEHOME  := lib/circle-stdlib/libs/circle
NEWLIBDIR   := lib/circle-stdlib/install/$(NEWLIB_ARCH)

FLASHY_OPTS ?=  \
			   --baud:$(FLASHY_BAUD) \
			   --flashBaud:$(FLASHY_BAUD)

FLASHY_CMD_REBOOT_LOADER := exec "reboot"
FLASHY_CMD_REBOOT := reboot $(FLASHY_REBOOT_MAGIC_WORD)

MFDIR := lib/mcufont/decoder
include lib/mcufont/decoder/mcufont.mk

CXX_SRCS := $(shell find src -type f -name "*.cpp")
C_SRCS := $(shell find src -type f -name "*.c") \
		  $(MFSRC)

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
		  	-I src \
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
		  -I src \
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
clean: distclean

.PHONY:
distclean:
	@find src -type f -name "*.o" -delete
	@find src -type f -name "*.d" -delete
	@rm -f *.elf *.img *.lst *.map *.txz
	@rm -f boot/*
	@rm -f pkg/boot/*

run: $(TARGET).img
	$(FLASHY) \
		$(SERIALPORT) \
		--flashBaud:$(FLASHBAUD) \
		--userBaud:$(USERBAUD) \
		--reboot:$(REBOOTMAGIC) \
		$(FLASHYFLAGS) \
		$< \
		monitor
