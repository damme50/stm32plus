Introduction
============
Firstly, welcome to stm32plus, the C++ library that eases the burden of programming the STM32F030, F042, F051, F100, F103, F107 and F4 devices.

The main introduction and getting started guide can be found at [my website](http://www.andybrown.me.uk).

### Travis CI build status

A representative sample of the stm32plus configurations are configured to automatically build with the Travis CI system. The badge below shows the current state of the builds.

[![Build Status](https://travis-ci.org/andysworkshop/stm32plus.svg?branch=master)](https://travis-ci.org/andysworkshop/stm32plus)

How to compile the library
==========================

Before you can use the library you need to build it because, although much of the library is provided _header-only_ there is a substantial amount of compiled code that you must link to.

Please see the INSTALL.md file for detailed compilation instructions.

Releases
========

After cloning this repo you are going to have a choice of what to build based on the branches and tags that have been created. Your options are:

* Download a [release](https://github.com/andysworkshop/stm32plus/releases) and build from that. This is the safe option. Every now and then I will create a tag from the current master branch that represents a release. You can be sure that a release will be fully tested against all the supported MCUs.

* Checkout the `master` branch (the default) and build from that. This is the quite-safe option. The `master` branch is guaranteed to build on all MCUs but the examples may not have been fully regression tested.

* Checkout a named feature or bug-fix branch and build from that. This is the hardcore option. Feature branches  that have not been merged back into `master` represent work in progress and should build but may be incomplete and have bugs.     

Where are the examples?
=======================

In the _examples_ subdirectory you will find dozens of examples nearly all of which will work without modification on the F0, F1 and F4 devices. The examples are heavily commented to help you understand what's going on.

The examples are configured to run out-of-the-box on the following MCUs:

| Device | Flash | SRAM | CPU Clock | External Oscillator |
|--------|-------|------|-----------|---------------------|
| F40x | 1024Kb | 192Kb | 168Mhz | 8 MHz |
| F103 HD | 512Kb | 64Kb | 72 MHz | 8 MHz |
| F107 | 256Kb | 64Kb | 72 MHz | 25 MHz |
| F100 MD VL | 128Kb | 8Kb | 24 MHz | 8 MHz |
| F042 | 32Kb | 6Kb | 48 MHz | none (uses 8MHz internal) |
| F051 | 64Kb | 8Kb | 48 MHz | none (uses 8MHz internal) |
| F030 | 64Kb | 8Kb | 48 MHz | none (uses 8MHz internal) |

If your device is listed but your board has a different oscillator or core clock speed then you may need to adjust `System.c` in the `system` subdirectory
of the example that you are looking at. If your memory configuration is different then you will need to adjust `Linker.ld` in the `system` subdirectory. 

Documentation
=============

HTML documentation can be found in the doc/html subdirectory. This documentation is auto-generated by the [doxygen](http://www.doxygen.org/) tool from the comments in the source code.

I freely admit that the documentation lags in both quantity and quality behind the code itself and it's a future task for me to improve it. In the meantime I hope that the heavily commented examples are enough to get you started.

Contributing
============

Contributions to stm32plus are welcome. Please follow these steps to ensure a smooth workflow:

* Clone the main stm32plus repo into your personal account and create a branch off `master` for your work. Give it a short meaningful name that allows people to get a good idea _at-a-glance_ of what you've done.

* When you're happy with your code, first do a merge back from the current master to ensure you're still compatible and then send me a pull request. I will code-review the pull-request and when we're all happy I will accept it and do the merge back into `master`.

Working in Eclipse
------------------
I do all my development in Eclipse Kepler using the CDT and the [GNU ARM Eclipse plugin](http://gnuarmeclipse.livius.net/blog/). The `.project` and `.cproject` files for the main library and all the examples are included. You can use Eclipse's import option on the root checkout directory to bring them all into your workspace in one go. I recommend that you create a _working set_ to contain all the stm32plus projects because there's a lot of them.

I have found that the recent updates to the plugin have been stable and non-breaking so you can probably just get the latest version. At the time of writing I am using version *1.10.2.201407190854* of the _Cross Compiler Support_ plugin.

How do I report a bug?
======================

If you think that you've found a bug then please enter an issue against the project on github. It really helps if you can give me enough information to reproduce the bug myself.

Alternatively you can fix it yourself and send me a pull-request.

A short walk around the directories
===================================

`/INSTALL.md`: The installation guide. This file explains how to build the library. If you read nothing else, read this!

`/SConstruct`: The top level scons build file, broadly equivalent to a Makefile for those that have not used scons before.

`lib/`: The root directory containing the library source code.

`lib/include`: The include files for the library. This directory and the parent stm32plus directory must be on the include path of any programs that you write. As of 2.0.0 the only include files that you need to know about are those in the `config` subdirectory. It should only ever be necessary to include `config/stm32plus.h` and one each for the peripherals that you want to use, for example `config/usart.h` or `config/spi.h`. These high level files take care of including everything else that they need.

`lib/src`: The C++ source files that make up the library. Everything in here is considered internal.

`lib/fwlib`: Source code to the ST Microelectronics standard peripheral libraries for the F0, F1 and F4 processors.

`examples/`: The examples that demonstrate the features of the library. There is one subdirectory for each example. All the examples follow the same general format. There is the main example source code and a `system` subdirectory. The `system` subdirectory is the same for every example and contains the startup and initialisation code required for the F0, F1 and F4 MCUs. The `SConscript` file takes care of selecting the appropriate code for your target MCU. To build modified example, run `scons` again from the root directory. scons is smart enough to only build changed files and their dependents.

`utils/bm2rgbi`: This PC utility is for converting graphics files (jpeg, png, gif etc.) into an internal format suitable for efficient transfer to a TFT. It also supports compression using the LZG format that results in files roughly the same size as a PNG. You'll need this utility if you decide to use the bitmap functions in the graphics library.

`utils/FontConv`: This PC utility is for converting TrueType bitmap fonts such as those you can download for free from www.dafont.com into font files suitable for compiling and using with the stm32plus text output graphics library functions.

`utils/LzgFontConv`: This PC utility is for converting TrueType vector anti-aliased fonts into compressed graphical representations suitable for compiling and using with the stm32plus bitmap text output graphics library functions.

A quick guide to flashing using OpenOCD
=======================================

At the time of writing the lastest version of openocd is 0.8.0 and it contains full support for the STM32 connected via JTAG and also via ST-Link (e.g. the STM32F4DISCOVERY  and STM32VLDISCOVERY boards). The following guide assumes that you are using either Linux or Windows with a Unix-like shell (cygwin or mingw) and that you have built the binaries.

Flashing the stm32f4discovery board
-----------------------------------

`cd` into the openocd directory and run it with the flags required for the discovery board. For me on Windows 7 x64/cygwin this is:

	$ bin-x64/openocd-x64-0.8.0.exe -f scripts/board/stm32f4discovery.cfg
	Open On-Chip Debugger 0.8.0 (2012-10-07-10:39)
	Licensed under GNU GPL v2
	For bug reports, read
	http://openocd.sourceforge.net/doc/doxygen/bugs.html
	adapter speed: 1000 kHz
	srst_only separate srst_nogate srst_open_drain
	Info : clock speed 1000 kHz
	libusbx: info [cache_config_descriptors] could not access
	configuration descriptor (dummy) for
	'\\.\USB#VID_0424&PID_2504#6&247B17EE&0&1':
	[31] A device attached to the system is not functioning.
	libusbx: info [cache_config_descriptors] could not access
	configuration
	descriptor (dummy) for
	'\\.\USB#VID_1A40&PID_0101#5&476FB6F&0&4':
	[31] A device attached to the system is not functioning.
	Info : stm32f4x.cpu: hardware has 6 breakpoints, 4 watchpoints

openocd is now up and running waiting for you to do something. Don't worry about the libusb 'errors', they are harmless.

Now telnet to openocd and flash your hex image:

	$ telnet localhost 4444
	Trying 127.0.0.1...
	Connected to localhost.
	Escape character is '^]'.
	Open On-Chip Debugger

Reset the device and halt it:

	> reset init
	target state: halted
	target halted due to debug-request, current mode: Thread 
	xPSR: 0x01000000 pc: 0x08000b9c msp: 0x20020000

Flash your hex image:

	> flash write_image erase p:/button.hex
	auto erase enabled
	target state: halted
	target halted due to breakpoint, current mode: Thread 
	xPSR: 0x61000000 pc: 0x20000042 msp: 0x20020000
	wrote 16384 bytes from file p:/button.hex in 1.147065s (13.949 KiB/s)

Reset the device to run the program:

	> reset

Flashing an F1 board using JTAG
-------------------------------

The procedure is much the same as the F4. We will start openocd and then use a telnet connection to flash the image. First start openocd. I can't give you the exact startup command for openocd because it will vary according to the JTAG dongle that you have purchased. I use the Olimex ARM-USB-TINY-H device that has an OpenOCD configuration file dedicated to it. Here's what openocd reports when I start it up:

	Open On-Chip Debugger 0.5.0-dev-00852-gf9feeac-dirty (2011-07-27-21:58)
	Licensed under GNU GPL v2
	For bug reports, read
	   http://openocd.berlios.de/doc/doxygen/bugs.html
	Info : only one transport option; autoselect 'jtag'
	1000 kHz
	adapter_nsrst_delay: 100
	jtag_ntrst_delay: 100
	cortex_m3 reset_config sysresetreq
	Info : device: 6 "2232H"
	Info : deviceID: 364511274
	Info : SerialNumber: OLTMERU�A
	Info : Description: Olimex OpenOCD JTAG ARM-USB-TINY-H A
	Info : max TCK change to: 30000 kHz 
	Info : clock speed 1000 kHz
	Info : JTAG tap: stm32.cpu tap/device found: 0x3ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x3)
	Info : JTAG tap: stm32.bs tap/device found: 0x06414041 (mfg: 0x020, part: 0x6414, ver: 0x0)
	Info : stm32.cpu: hardware has 6 breakpoints, 4 watchpoints

Now we can telnet to openocd:

	$ telnet localhost 4444
	Trying 127.0.0.1...
	Connected to localhost.
	Escape character is '^]'.
	Open On-Chip Debugger

And now we can reset the device
 
	> reset init
	JTAG tap: stm32.cpu tap/device found: 0x3ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x3)
	JTAG tap: stm32.bs tap/device found: 0x06414041 (mfg: 0x020, part: 0x6414, ver: 0x0)
	target state: halted
	target halted due to debug-request, current mode: Thread 
	xPSR: 0x01000000 pc: 0x08000a84 msp: 0x2000fffc

Flash the program hex image to the board:

	> flash write_image erase /tmp/pframe.hex
	auto erase enabled
	device id = 0x10036414
	flash size = 512kbytes
	Padding image section 0 with 4 bytes

Reset the MCU to start the program:

	> reset
	JTAG tap: stm32.cpu tap/device found: 0x3ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x3)
	JTAG tap: stm32.bs tap/device found: 0x06414041 (mfg: 0x020, part: 0x6414, ver: 0x0)

Flashing the stm32vldiscovery board
-----------------------------------

Windows users need to ensure that they can connect to the ST-Link V1 debugger on the VL discovery board using OpenOCD. If the instructions below fail then you probably need to replace the default mass storage USB drivers with the WinUSB or libusb drivers using the [zadig](https://sourceforge.net/projects/libwdi/files/zadig) utility.

`cd` into the openocd directory and run it with the flags required for the discovery board. For me on Windows 7 x64/cygwin this is:

	$ bin-x64/openocd-x64-0.8.0.exe -f scripts/board/stm32vldiscovery.cfg 
	Open On-Chip Debugger 0.8.0 (2012-10-07-10:39)
	Licensed under GNU GPL v2
	For bug reports, read
	        http://openocd.sourceforge.net/doc/doxygen/bugs.html
	adapter speed: 1000 kHz
	Info : clock speed 1000 kHz
	libusbx: info [cache_config_descriptors] could not access configuration descriptor (dummy) for '\\.\USB#VID_0424&PID_2504#6&3734C893&0&1': [31] A device attached to the system is not functioning.
	Info : stm32f1x.cpu: hardware has 6 breakpoints, 4 watchpoints

openocd is now up and running waiting for you to do something. Don't worry about the libusb 'errors', they are harmless.

Now telnet to openocd and flash your hex image:

	$ telnet localhost 4444
	Trying 127.0.0.1...
	Connected to localhost.
	Escape character is '^]'.
	Open On-Chip Debugger

Reset the device and halt it:

	> reset init
	target state: halted
	target halted due to debug-request, current mode: Thread 
	xPSR: 0x01000000 pc: 0x08000b84 msp: 0x20002000

Flash your hex image:

	> flash write_image erase p:/blink.hex
	auto erase enabled
	device id = 0x10016420
	flash size = 128kbytes
	target state: halted
	target halted due to breakpoint, current mode: Thread 
	xPSR: 0x61000000 pc: 0x2000003a msp: 0x20002000
	wrote 3072 bytes from file p:/blink.hex in 0.653037s (4.594 KiB/s)

Reset the device to run the program:

	> reset

Flashing the stm32f0discovery board
--
This is one of the more recent _discovery_ boards from ST and as such it comes equipped with version 2 of the ST-Link debugger on board. Using it with OpenOCD is a very similar procedure to the F4.

`cd` into the openocd directory and run it with the flags required for the discovery board. For me on Windows 7 x64/cygwin this is:

	$ bin-x64/openocd-x64-0.8.0.exe -f scripts/board/stm32f0discovery.cfg
	Open On-Chip Debugger 0.8.0 (2013-05-05-10:44)
	Licensed under GNU GPL v2
	For bug reports, read
	        http://openocd.sourceforge.net/doc/doxygen/bugs.html
	srst_only separate srst_nogate srst_open_drain connect_deassert_srst
	Info : This adapter doesn't support configurable speed
	Info : STLINK v2 JTAG v14 API v2 SWIM v0 VID 0x0483 PID 0x3748
	Info : Target voltage: 2.886506
	Info : stm32f0x.cpu: hardware has 4 breakpoints, 2 watchpoints

openocd is now up and running waiting for you to do something.

Now telnet to openocd and flash your hex image:

	$ telnet localhost 4444
	Trying 127.0.0.1...
	Connected to localhost.
	Escape character is '^]'.
	Open On-Chip Debugger

Reset the device and halt it:

	> reset init
	target state: halted
	target halted due to debug-request, current mode: Thread 
	xPSR: 0xc1000000 pc: 0x080009b8 msp: 0x20002000

Flash your hex image:

	> flash write_image erase p:/blink.hex
	auto erase enabled
	device id = 0x20006440
	flash size = 64kbytes
	wrote 2048 bytes from file p:/blink.hex in 0.423024s (4.728 KiB/s)

Reset the device to run the program:

	> reset

That's all, I hope my experience with OpenOCD can help you get started.
