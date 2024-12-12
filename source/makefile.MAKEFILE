upload: code.hex
	avrdude -p atmega328p -c avrisp -U flash:w:code.hex:i -F -P COM3 -B12 -v
code.hex: main.c
	avr-gcc -Wall -g -Os -mmcu=atmega328p  main.c -o  code.bin 
	avr-objcopy -j .text -j .data -O ihex .\code.bin .\code.hex