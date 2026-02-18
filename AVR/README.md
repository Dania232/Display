# AVR Firmware: SSD1306 Display Controller

This directory contains the bare-metal **C** firmware for the ATmega328PB microcontroller. The firmware acts as a bridge, receiving graphical data via UART from a PC and rendering it to an OLED display via I2C.

This project demonstrates low-level hardware driver implementation, custom protocol parsing using a Finite State Machine (FSM), and asynchronous data reception using interrupts and a Ring Buffer, all without relying on the Arduino HAL.

## 📂 Project Structure

The codebase is organized into `src` and `inc` directories for a clean separation of logic:

* **`display.c/.h`**: SSD1306 OLED driver. Initializes the screen (charge pump, addressing mode) and handles I2C byte transfers for rendering.
* **`fsm.c/.h`**: Finite State Machine (FSM) for byte-by-byte parsing of the custom communication protocol.
* **`ring_buffer.c/.h`**: A 256-byte circular buffer used to safely queue incoming UART data from the interrupt handler.
* **`uart.c/.h`**: UART driver. Features **interrupt-driven RX** (`USART0_RX_vect`) and blocking TX.
* **`i2c.c/.h`**: Hardware TWI (Two-Wire Interface) Master implementation. Uses polling with safety timeouts to prevent deadlocks.
* **`timer.c/.h`**: Hardware Timer0 driver. Provides non-blocking callbacks for visual indications (e.g., error LED blinking).
* **`gpio.c/.h`**: Simple HAL for hardware pin manipulations (used for the status LED).
* **`main.c`**: Application entry point. Orchestrates the UART ring buffer, feeds data into the FSM, handles ACK/NACK responses, and streams payload data to the display.

## ⚙️ Technical Specifications

* **MCU:** ATmega328PB
* **Clock Speed:** 16 MHz
* **Language:** C (Bare-metal)
* **Interfaces:**
    * **UART:** 9600 Baud, 8N1. Asynchronous RX (Interrupts + Ring Buffer), Synchronous TX.
    * **I2C:** Hardware TWI, ~100kHz Standard Mode.
* **Display:** SSD1306 128x64 OLED.

## 📡 Communication Protocol

The firmware implements a custom binary protocol to ensure data integrity and proper frame alignment. 

| Byte 0 | Byte 1 | Byte 2 | Byte 3-4 | Byte 5...N | Byte N+1 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `0xAA` | `0x55` | `TYPE` | `LENGTH` | `PAYLOAD` | `CHECKSUM` |

* **Sync:** `0xAA`, `0x55` preamble to align the receiver.
* **Length:** 16-bit little-endian value. The system expects `1024` bytes for a full-screen frame.
* **Checksum:** XOR checksum of the Type, Length (L & H), and Payload bytes.
* **Flow Control:** The MCU sends an ACK (`'c'`) upon successful frame verification, or a NACK (`'n'`) if the checksum fails.

## 🚀 Recent Improvements



## 🧐 Current Limitations & Future Work

