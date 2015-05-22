PRG 			= or-clock

MCU_TARGET		= atmega328p
SYSTEM_CLOCK	= 8000000UL

DEFS			=
LIBS			=

CC 				= avr-gcc
CSTANDARD 		= gnu99 

OBJCOPY			= avr-objcopy
OBJDUMP			= avr-objdump

ODIR			= obj
SOURCES			= main.c cb.c
OBJECTS			= $(addprefix $(ODIR)/, $(SOURCES:.c=.o))
DEPS 			= cb.h

all: $(PRG).hex

$(PRG).hex: $(PRG).elf
	$(OBJCOPY) -O ihex -R .eeprom $(PRG).elf $(PRG).hex

$(PRG).elf: $(OBJECTS)
	$(CC) --std=$(CSTANDARD) -mmcu=$(MCU_TARGET) $(OBJECTS) -o $(PRG).elf

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Os --std=$(CSTANDARD) -DF_CPU=$(SYSTEM_CLOCK) -mmcu=$(MCU_TARGET) -c -o $@ $< $(LIBS)

$(PRG).lst: $(PRG).elf
	$(OBJDUMP) -h -S $(PRG).elf > $(PRG).lst

$(PRG).map: $(PRG).elf $(OBJECTS)
	$(CC) -g -mmcu=$(MCU_TARGET) -Wl,-Map,$(PRG).map -o $(PRG).elf $(OBJECTS)

fuses: 
	avrdude -F -V -c stk500v2  -p atmega328p -P /dev/stk500-programmer0 -b 115200 -D -U lfuse:w:0xe2:m -U hfuse:w:0xda:m -U efuse:w:0xfe:m

flash: $(PRG).hex
#	avrdude -F -V -c stk500v2  -p ATMEGA328P -P /dev/stk500-programmer0 -b 115200 -U flash:w:$(PRG).hex
	avrdude -F -V -c arduino  -p ATMEGA328P -P /dev/ttyUSB0 -b 57600 -U flash:w:$(PRG).hex
#	avrdude -F -V -c arduino  -p ATMEGA328P -P /dev/tty.usbserial-A900cbEu -b 57600 -U flash:w:$(PRG).hex

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *.elf *.lst *.map

