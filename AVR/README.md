Markdown

# AVR Firmware: SSD1306 Display Controller

This directory contains the **bare-metal C++ firmware** for the **ATmega328PB** microcontroller. The firmware acts as a bridge, receiving graphical data via UART from a PC and rendering it to an OLED display via I2C.

<<<<<<< HEAD
This project demonstrates low-level driver implementation, custom protocol parsing using a **Finite State Machine (FSM)**, and Object-Oriented design in an embedded environment without relying on the Arduino HAL.

## 📂 Project Structure
=======


## ⚙️ Technical Specifications

* **MCU:** ATmega328PB (16 MHz External Clock)
* **Flash Size:** ~2.5KB (approx)
* **Communication Interfaces:**
    * **UART:** 9600 Baud, Polling-based reception with timeout.
    * **I2C:** Hardware TWI (Two Wire Interface), Standard Mode.
* **Display:** SSD1306 128x64 OLED.

## 📡 Communication Protocol
=======

⚙️ Technical Specifications

    MCU: ATmega328PB (16 MHz External Clock)

    Flash Size: ~2.5KB (approx)

    Communication Interfaces:

        UART: 9600 Baud, Polling-based reception with timeout.

        I2C: Hardware TWI (Two Wire Interface), Standard Mode.

    Display: SSD1306 128x64 OLED.

📡 Communication Protocol

The firmware implements a custom binary protocol to ensure data integrity. The packet structure is as follows:

| Byte 0 | Byte 1 | Byte 2 | Byte 3-4 | Byte 5...N | Byte N+1 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **0xAA** | **0x55** | **TYPE** | **LENGTH** | **PAYLOAD** | **CHECKSUM** |

* **Sync:** `0xAA`, `0x55` preamble to align the receiver.
* **Checksum:** XOR checksum of header and payload to detect transmission errors.
* **Flow Control:** The firmware sends an ACK (`'c'`) upon successful verification.

## 🛠 Building and Flashing

This project uses `avr-g++` and `make`.

1.  Connect the programmer (e.g., USB-UART bridge) to the MCU.
2.  Run the makefile:

```bash
make flash
```
    Note: Ensure the programmer path in Makefile matches your system (e.g., /dev/ttyUSB0).


🧐 Critical Analysis & Future Improvements


=======
    Run the makefile:
    Bash

    make flash

(Note: Ensure the programmer path in Makefile matches your system, e.g., /dev/ttyUSB0)

🧐 Critical Analysis & Future Improvements

----



