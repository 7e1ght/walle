.PHONY: build flash bin
.SILENT: build bin
.ONESHELL: build bin

NAME = walle

build: 
	if [ -d build ]
	then 
		cd build && make 
	else 
		mkdir build && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake .. && make
	fi

bin: build
	if [ ! -d build/bin ] 
	then
		mkdir -p build/bin 
	fi

	arm-none-eabi-objcopy -O binary build/${NAME}.elf build/bin/firmware.bin

flash: bin 
	st-flash write build/walle.bin 0x8000000