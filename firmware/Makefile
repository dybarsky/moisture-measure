SOURCES = src
HEADERS = src
OUT = build

export OBJ
OBJ += $(OUT)/main.o
OBJ += $(OUT)/led.o
OBJ += $(OUT)/timer.o
OBJ += $(OUT)/sensor.o

CC = msp430-gcc
CFLAGS = -g -mmcu=msp430g2553
INCFLAGS = -I/usr/local/include -I$(HEADERS)

help:
	@echo "Targets: clean, build, flash, all" 

all: clean build flash

clean:
	@echo "Clean"
	rm -rf build

build-dir:
	mkdir -p build

flash: $(OUT)/firmware.elf
	@echo "Flashing";\
	mspdebug rf2500 "prog $(OUT)/firmware.elf"

build: $(OUT)/firmware.elf
	@echo "SUCCESSFUL";\

$(OUT)/firmware.elf: | build-dir $(OBJ)
	@echo "Link firmware";\
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(OUT)/firmware.elf

$(OUT)/main.o: $(SOURCES)/main.c $(HEADERS)/*.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/main.c -o $(OUT)/main.o

$(OUT)/led.o: $(SOURCES)/led.c $(HEADERS)/led.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/led.c -o $(OUT)/led.o

$(OUT)/sensor.o: $(SOURCES)/sensor.c $(HEADERS)/sensor.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/sensor.c -o $(OUT)/sensor.o

$(OUT)/timer.o: $(SOURCES)/timer.c $(HEADERS)/timer.h
	@echo "Compile $<";\
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SOURCES)/timer.c -o $(OUT)/timer.o
	
.SILENT: clean build-dir
.PHONY: clean build-dir flash build











