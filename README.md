Readme

NAME
  A Shell

AUTHORS
	Vasimraza Bukhari
	 U
	Kenneth Mendoza
	 U30768633

SYNOPSIS
	./myshell
	Internal Commands
	External Commands
	Batchfile
	I/O FORK
	Background Execution

DESCRIPTION
	The SHell/Command Line Interpreter is the fundamental User interface to an Operating System.
	This preject is implemented to write a simple - myshell - that has the several Internal and 
	External command operations.
	The User can issue commands by entering them into the keyboard or entered unto a bathfile. If
	the user enters or attempts to run a command not found in the COMMANDS LIST for internal command
	the shell will execute as an external command.

COMMAND LIST
	cd <directory> - Change the current default directory to <directory>.If the <directory> argument
	    is not present, report the current directory. If the directory does not exist an appropriate 
		error should be reported.
	clr - Clear screen
	dir <directory> - List the contents for directory <directory>
	echo <comment> - Display <comment> on the display followed by a new line ( multiple splaces/tabs
	may be reduced to a single splace).
	help - Display the user manual using the more filter.
	pause - Pause opetation fo the shell intil'Enter' is pressed
	quit - Quit the shell.

BATCHFILE
	./myshell batchfile
	The shell reads the batchfile line by line and runs each command as input from the user.

BACKGROUND EXECUTION
	This is used in order to return to the command line prompt after running the program.
	<command> &
