CC=cl65

default:
	$(CC) -O -o DRVUTILS.PRG -t cx16 main.c disk.c screen.c menu.c
	x16emu -rtc -ram 2048 -scale 2 -prg DRVUTILS.PRG -run -debug

clean:
	rm -f *.PRG
	rm -f *.o
