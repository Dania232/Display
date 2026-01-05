MCU = atmega328pb
F_CPU = 16000000UL
TARGET = bmtry
PORT = /dev/ttyUSB0
BAUD = 115200

CXX = avr-g++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRDUDE = avrdude

all: flash

Display/disp.o: Display/Display_ssd1306.cpp
	$(CXX) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -c $< -o $@

$(TARGET).o: $(TARGET).cpp
	$(CXX) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -c $< -o $@


$(TARGET).elf: $(TARGET).o Display/disp.o
	$(CXX) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -o $@ $^
#$(TARGET).elf: $(TARGET).cpp
#	$(CXX) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -o $@ $<

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$<:i

disasm: $(TARGET).elf
	$(OBJDUMP) -D -m avr5 $< > disasm.txt

clean:
	rm -f *.o Display/*.o *.elf *.hex disasm.txt

.PHONY: all flash disasm
