
Bare-Metal Display Controller System

This pet project was created to make practical use of an SSD1306 display and an Arduino-compatible MCU, while also implementing the controller software with minimal external libraries, purely for learning purposes.
The project consists of:
MCU firmware
Four command-line utilities
One small UI application
Executable files for PC tools are located in ./PC/build/bin/

Overview
The system allows sending monochrome 128×64 images from a PC to an SSD1306 display via UART → MCU → I2C.
Image flow:
Image → PC tools → UART → MCU → I2C → SSD1306 display

Command-Line Tools
The four command-line applications are designed to be used together via pipes:
mkmnchrom
Takes an image file as an argument
Converts it to raw monochrome binary format
Output format: row-major, 128×64
Writes output to standard output (stdout)
show
Reads raw image bytes from stdin
Displays the image in the terminal
remapimg
Reads raw image bytes from stdin
Remaps them to the SSD1306 display memory format
flush
Reads image data from stdin
Sends it to the display via /dev/ttyUSB0
Example:
./mkmnchrom image.png | ./remapimg | ./flush

UI Application
MyApp
Opens a 128×64 drawing canvas
Allows drawing with the mouse
Updates the display in real time
Can save the image in raw binary row-major format
Examples:
./show < canvas.bin
./remapimg < canvas.bin | ./flush

MCU Firmware (AVR)
The ./AVR directory contains:
Firmware source code
Makefile for flashing the MCU
Details
Target MCU: ATMega328PB
Communication:
UART: receives raw image bytes from PC
I2C: sends data to the display
Display controller: SSD1306
Toolchain: avr-g++, avr-libc, make
Flashing port: /dev/ttyUSB0
⚠️ The firmware is highly platform-dependent and is intended to compile and run only on ATMega328PB.

PC Software
The ./PC directory contains PC-side applications.
Build System
Uses CMake
After configuration and build:
Executables are in ./PC/build/bin/
Dependencies
stb_image.h
stb_image_resize2.h
FLTK (for UI)
Linux-only APIs (read, write)
Access to /dev/ttyUSB0
Directory Structure
./PC/libs – external libraries (stb headers)
./PC/src – source code
./PC/build – build output

Shared Code
The ./Shared directory contains:
Protocol definitions
Transport layer interfaces
These components are shared between MCU and PC code.

Notes
Linux only
Requires SSD1306 display
Requires ATMega328PB MCU
Uses raw binary image transfer