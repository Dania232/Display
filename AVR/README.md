Markdown

# AVR Firmware: SSD1306 Display Controller

This directory contains the **bare-metal C++ firmware** for the **ATmega328PB** microcontroller. The firmware acts as a bridge, receiving graphical data via UART from a PC and rendering it to an OLED display via I2C.

This project demonstrates low-level driver implementation, custom protocol parsing using a **Finite State Machine (FSM)**, and Object-Oriented design in an embedded environment without relying on the Arduino HAL.

## 📂 Project Structure

The codebase is organized into logical layers of abstraction:

* **`./LowLevel`**: Hardware Abstraction Layer (HAL).
    * Contains direct register manipulations for UART (Asynchronous, 9600 baud, 8N1) and I2C (Master mode, ~100kHz).
    * Implementation depends specifically on the ATmega328PB registers (`TWCR0`, `UBRR0`, etc.).

* **`./Display`**: Device Driver Layer.
    * `Display_ssd1306`: encapsulating the SSD1306 command set. It initializes the screen (charge pump, contrast, addressing mode) and handles pixel data transfer.

* **`./TransportLayer.hpp`**: Interface Layer.
    * Implements the `ITransportLayer` interface (from Shared), wrapping the low-level UART functions into a generic send/receive API.

* **`ProtocolImpl.hpp`**: Application Logic / Protocol Layer.
    * Implements the application-specific communication protocol.
    * Contains the **Finite State Machine (FSM)** used to parse incoming packets byte-by-byte.

## ⚙️ Technical Specifications

* **MCU:** ATmega328PB (16 MHz External Clock)
* **Flash Size:** ~2.5KB (approx)
* **Communication Interfaces:**
    * **UART:** 9600 Baud, Polling-based reception with timeout.
    * **I2C:** Hardware TWI (Two Wire Interface), Standard Mode.
* **Display:** SSD1306 128x64 OLED.

## 📡 Communication Protocol

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

As this is a study project, several design choices were made for simplicity that would be optimized in a production environment.
1. Blocking I/O vs. Interrupts

    Current State: The UART and I2C drivers use polling/blocking loops. The CPU waits for flags (like RXC0 or TWINT) to be set.

    Limitation: This wastes CPU cycles and prevents the MCU from performing other tasks while communicating.

    Improvement: Implement Interrupt Service Routines (ISRs) for UART RX/TX and use a ring buffer. This would allow the FSM to process data asynchronously.

2. Tight Coupling

    Current State: The ProtocolImpl class writes directly to the Display object inside the RX_PAYLOAD state.

    Limitation: This tightly couples the communication logic with the rendering logic.

    Improvement: Implement a callback system or a Frame Buffer mechanism. The Protocol should fill a buffer and notify the main application, keeping the layers independent.

3. Error Recovery

    Current State: If a checksum fails, the system sends no ACK and resets the state machine.

    Improvement: Implement a NACK (Negative Acknowledge) response so the PC knows immediately to retransmit, rather than waiting for a timeout.

4. Hardcoded Configuration

    Current State: Baud rates and I2C frequencies are hardcoded in the constructor/init functions.

    Improvement: Move configuration to a centralized Config.h or pass configuration structs to the drivers for better portability.
