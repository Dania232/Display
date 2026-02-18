MCU = atmega328pb
F_CPU = 16000000UL
TARGET = src/main
PORT = /dev/ttyUSB0
BAUD = 115200

# avr-gcc умеет компилировать и C, и C++, но для порядка можно разделить
CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRDUDE = avrdude

# Общие флаги компилятора
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# 1. СПИСОК ВСЕХ ОБЪЕКТНЫХ ФАЙЛОВ ПРОЕКТА
# Добавь сюда все свои .c файлы, заменив расширение на .o
OBJS = src/main.o \
       src/uart.o \
       src/ring_buffer.o \
       src/fsm.o \
       src/i2c.o \
       src/display.o \
	   src/gpio.o \
	   src/timer.o

all: flash

# 2. ПРАВИЛО ДЛЯ КОМПИЛЯЦИИ ВСЕХ C-ФАЙЛОВ В ПАПКЕ src/
# Символ % работает как маска. $< - исходный файл, $@ - целевой файл
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 3. ПРАВИЛО ДЛЯ КОМПИЛЯЦИИ C++ ФАЙЛОВ В ПАПКЕ Display/
Display/%.o: Display/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

# 4. ЛИНКОВКА: собираем все OBJS в один elf-файл
# $^ - означает подставить сюда ВЕСЬ список из OBJS
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -c arduino -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$<:i

disasm: $(TARGET).elf
	$(OBJDUMP) -D -m avr5 $< > disasm.txt

clean:
	rm -f src/*.o Display/*.o *.elf *.hex disasm.txt

.PHONY: all flash disasm clean