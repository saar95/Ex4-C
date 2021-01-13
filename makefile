all:frequency frequency_r

main:frequency.o frequency_r.o
	gcc -Wall isort txtfind

frequency_r:frequency_r.c
	gcc -Wall  frequency_r.c -o frequency_r.o
	
frequency:frequency.c
	gcc -Wall  frequency.c -o frequency.o
	
.PHONY:clean

clean:
	rm -f *.o *.out