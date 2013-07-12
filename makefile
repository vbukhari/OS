/*
Vasim & Kenny
Operating System Project - Summer 2013

This file is our makefile where we goint to call 'make' to compile the code
*/
myshell: myshell.c utility.c myshell.h
	gcc -Wall myshell.c utility.c -o myshell
clean:
	rm -rf *.o
	
