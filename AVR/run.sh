avr-g++ -mmcu=atmega328pb -DF_CPU=16000000UL -Os -o bmtry.elf bmtry.cpp
avr-objcopy -O ihex bmtry.elf bmtry.hex
avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:bmtry.hex:i
