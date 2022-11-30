all:program
program:	myshell.o	execx.o	writef.o
	gcc	myshell.o	-o	program
writef.o:	writef.c
	gcc	writef.c -o writef
execx.o:	execx.c
	gcc	execx.c -o execx
clean:
	del	*.o	
run:
	program1.exe