# Simple makefile to expose convenience commands "make posix", "make clean" and "make stm32mp1"
.PHONY: clean posix stm32mp1 flash format

clean:
	rm -rf build

posix:
	mkdir -p build && cd build && cmake .. --preset posix && cd posix && make; cd ..

stm32mp1:
	mkdir -p build && cd build && cmake .. --preset stm32mp1 && cd stm32mp1 && make; cd ..

flash:
	./scripts/flash

format:
	./scripts/format