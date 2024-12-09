TOOLCHAIN ?= /opt/arm-gnu-toolchain-13.3.rel1-x86_64-aarch64-none-elf/bin/

FLASHY_TARGET ?= /dev/ttyACM1

#FLASHY_BAUD ?= 2000000
#FLASHY_BAUD ?= 1700000
#FLASHY_BAUD ?= 1500000
#FLASHY_BAUD ?= 1200000
#FLASHY_BAUD ?= 1000000
FLASHY_BAUD ?= 921600
#FLASHY_BAUD ?= 576000
FLASHY_REBOOT_MAGIC_WORD ?= DEADC0DE

FRAMEBUFFER_WIDTH ?= 960
FRAMEBUFFER_HEIGHT ?= 540
