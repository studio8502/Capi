# Capi Operating System

Capi is a new operating system for Raspberry Pi systems. Currently it targets the
Pi 4/400, but it is hoped to expand it to the 3 and 5 series as it grows.

## History

Capi began its existence as a fork of the TIC-80 virtual machine. However, growing pains
and missing functionality necessitated a clean slate approach; Capi now contains no
code from the TIC-80 project at all. Starting over from scratch requires writing quite
a bit of lower-level code which TIC-80 previously provided, but doing so allowed Capi
to have things like runtime-variable screen resolution, GPU scaling of the framebuffer,
support for networking, and 32-bit colour.

## Status

At present, it is extremely primitive, little more than thin wrappers around drivers
and functionality provided by the Circle bare-metal library. In its curent state,
it builds cleanly and boots on a Pi 400, but offers absolutely no practical functionality.

As of this writing, effort is focused on implementing the core drawing and GUI functionality,
starting with the Workspace and Window classes. Recently, clipped 2D shape drawing has been
implemented, though it is hardly to be considered optimal.

## Design

The intention behind Capi is architecturally very similar to its TIC-80 roots. The core
OS and utilities are being written in C++, and will eventually expose a Lua-based API
for user programs. It is hoped that Capi will provide usable development tools, such as:

* Syntax highlighting code editor
* Bitmap editor
* Font editor
* Sound editor
* Music tracker
* A tiles/sprites based game coding API
* A WIMP GUI application API

Essentially, the OS consists of a C++ core, with drivers provided by Circle, which provides
a graphical OS and tools for making and running cooperatively-multitasked applications
written in Lua. The goal is to provide an interesting, fun environment for programming and
play on the Raspberry Pi platform; if it develops into what is considered to be a fun thing
to install on a spare Pi you have lying around, then it will be a success.

## Hardware Support

All the hardware driver code in Capi is provided by Circle; the hardware which is planned
to be supported includes:

* USB HID keyboards, mice, and gamepads
* USB mass storage (FAT32/ExFAT [1])
* Gigabit Ethernet networking
* Wireless Ethernet
* Pi GPIO pins

The screen resolution is fixed at 1920x1080, over HDMI. However, the framebuffer resolution
can be set to arbitrary sizes of any aspect ratio, and will be scaled by the GPU to fit into
the 1080p output.

[1] Note that ExFAT support is intentionally delayed until the patents expire in 2027

## Building

There's no reason to build Capi for yourself unless you are working on modifying it,
but if you want to, go right ahead.

First you will need to install a cross-toolchain targeting aarch64-none-elf, from
https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads. Install that
somewhere on your system, then edit `Config.mk` to set the `TOOLCHAIN` variable
to point to the `bin` subdirectory of that toolchain.

You will also need the ImageMagick suite to process the fonts. The `vendor/mcufont` 
directory contains a copy of the `mcufont` utility, which the build process uses to
generate the compressed font files the system uses from standard TTF/OTF fonts.

The contents of the directory `vendor/mcufont` are available under the MIT license.

Once you have cloned the repo, pull in the dependencies:

```sh
    git submodule update --init --recursive
```

Then issue the following commands from the base directory of the repo:

```sh
    pushd libs/circle-stdlib/libs/circle
    git apply ../../../../circle.patch
    cd ../..
    git apply ../../circle-stdlib.patch
    ./configure --opt-tls -r 4 # Replace with 3 for Pi 3, or with 5 for Pi 5.
    make
    # wait for it to finish building
    popd
    make package
```

## Installation

Once Capi is fully built, or if you downloaded a release build, you will find the file 
`Capi.txz` or similar in the `pkg` directory (or wherever you downloaded it!). This 
tarball contains a `boot` directory which contains the files to copy to the root of you
SD card. Insert the SD into the Pi, and it will boot up Capi.