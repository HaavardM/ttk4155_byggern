# List all source files to be compiled; separate with space
SOURCE_FILES := src/main.c src/uart.c src/spi.c src/mcp2515.c src/can.c src/pwm.c src/game_controller.c src/game_timer.c src/ir.c src/game_state_machine.c src/can_msg_handler.c src/solenoid.c src/TWI_Master.c src/dac.c src/motor_controller.c src/pi.c

# Set this flag to "yes" (no quotes) to use JTAG; otherwise ISP (SPI) is used
PROGRAM_WITH_JTAG := yes

# Feel free to ignore anything below this line
PROGRAMMER := atmelice_isp
ifeq ($(PROGRAM_WITH_JTAG), yes)
	PROGRAMMER := atmelice
endif

BUILD_DIR := build
TARGET_CPU := atmega2560
TARGET_DEVICE := m2560

CC := avr-gcc
CFLAGS := -O -std=c11 -mmcu=$(TARGET_CPU) -I include -I ../common -Wall

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

.DEFAULT_GOAL := $(BUILD_DIR)/main.hex

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.hex: $(OBJECT_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/a.out
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/a.out $(BUILD_DIR)/main.hex

.PHONY: flash
flash: $(BUILD_DIR)/main.hex
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U flash:w:$(BUILD_DIR)/main.hex:i

.PHONY: fuse
fuse:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U efuse:w:0xff:m
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U hfuse:w:0x19:m
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -U lfuse:w:0xfd:m

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: erase
erase:
	avrdude -p $(TARGET_DEVICE) -c $(PROGRAMMER) -e
