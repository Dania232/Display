PC Host Software & Toolchain

This directory contains the control plane for the custom display system. It is built using C++17, CMake, and FLTK. The system is designed with a modular architecture, separating low-level hardware communication from the application logic using abstract interfaces.
🏗 Architecture Overview

The software is split into three distinct layers:

    Core Libraries (./libs): Reusable components for Serial I/O (termios), image processing (stb_image), and bit-manipulation algorithms.

    CLI Tools (./cli): A suite of small, single-purpose utilities designed to follow the Unix Philosophy. They communicate via stdin/stdout pipes.

    GUI Application (./app): An interactive dashboard allowing real-time drawing and hardware control, utilizing multithreading to separate rendering from hardware flushing.

Tech Stack

    Language: C++17

    GUI Framework: FLTK (Fast Light Toolkit)

    Build System: CMake

    OS: Linux (Direct usage of unistd.h, fcntl.h for serial communication)

🛠 Command Line Tools (The Pipeline)

The CLI tools are designed to be chained together. This decouples the source of the image from the transmission logic.

Data Flow: [Image Source] -> [Processing] -> [Remapping] -> [Transmission]
Tool	Responsibility
mkmnchrom	Reads a standard image (PNG/JPG), resizes it to 128x64, applies a threshold, and outputs raw bits.
remapimg	Transforms standard raster data into the specific page-addressing memory layout required by the SSD1306 driver.
flush	The "Driver" node. Reads the final byte stream and handles the Serial/UART handshake with the microcontroller.
show	A debug utility that renders the raw binary stream into the terminal using ASCII art.
Usage Example

To take a standard PNG and send it to the hardware:
Bash

./build/bin/mkmnchrom image.png -th 128 | ./build/bin/remapimg | ./build/bin/flush

To preview the output in the terminal without hardware:
Bash

./build/bin/mkmnchrom image.png | ./build/bin/show

🎨 GUI Controller (./app)

The GUI provides an interactive canvas. It demonstrates Multithreading and Resource Locking to ensure a smooth UI while handling slow serial I/O.
Key Implementation Details

    Interfaces & Polymorphism: The application relies on IDrawableCanvas and ITransportLayer. This allows the UI to be decoupled from the specific hardware implementation.

    Concurrency & Thread Safety:

        The Problem: Serial transmission (9600 baud) is slow. Blocking the main thread would freeze the UI.

        The Solution: A dedicated Flusher worker thread handles transmission.

        Synchronization: A std::mutex protects the shared Framebuffer (buffer), ensuring the UI thread (writer) and Flusher thread (reader) do not cause data races.
    C++

    // Snippet from Canvas.cpp demonstrating thread safety
    void Monochrom128x64Canvas::setPixel(uint16_t x, uint16_t y, bool color)
    {
        std::lock_guard<std::mutex> lock(mtx); // RAII Lock
        // ... bitwise manipulation ...
    }

    Bitwise Logic: The drawing engine manually calculates byte indices and bit offsets to manipulate the 1-bit color depth buffer efficiently.

🔧 Building the Project

Ensure you have CMake and FLTK installed (e.g., sudo apt install libfltk1.3-dev).
Bash

mkdir build
cd build
cmake ..
make

Protocol 
+--------+------+-------+---------+---------+
| SYNC   | TYPE | LEN   | PAYLOAD | CHECK   |
+--------+------+-------+---------+---------+
| 0xAA55 | 1 B  | 2 B   | N bytes | 1 B     |
