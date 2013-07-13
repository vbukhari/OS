/*********************************************
 *BY: Vasimraza Bukhari and Kenneth Mendoza  *
 *      								 *
 *				MYSHELL						 *
 *											 *
 *********************************************/

#include "myshell.h"

char PATH_OF_SHELL[ BUFFER_MAX_SIZE ];/*PATH OF THE SHELL*/
char PATH_O_S[ BUFFER_MAX_SIZE ];/*ARRAY TO */
char INIT_PATH[ BUFFER_MAX_SIZE ];/*PATH IS INITIALIZED*/
int arg_n;/*# ARGS*/
char **ARG_N;/*POINTER FOR ARGS*/
char *ARG_S[ MAX_ARGUMENTS ];/*STRING POINTER TO ARGUMENTS*/
char Input[ BUFFER_MAX_SIZE ];/*BUFFER*/

//extern char **_ENVIRONMENT;



/* CHANGE DIRECTION OF IO VARIABLES*/
const int file_row = 3;
char File_Change[ file_row ][ FILENAME_MAX_SIZE ];
char Flag_Change[ file_row ];
char *Input_Sym[ file_row] = { ">", ">>", "<"};
/*MAIN FUNCTION*/
int main( int argc, char ** argv )
{
	int In_The_Back;
	int last = 1;
	signal( SIGINT, SIG_IGN );/*DO NOTHING WITH CTRL + C*/

	/*GETS CURRENT WORKING DIRECTORY FOR UNIX*/
	getcwd( INIT_PATH, BUFFER_MAX_SIZE - 1 );
	strcpy( PATH_OF_SHELL, INIT_PATH );
	strcat( PATH_OF_SHELL, "/myshell" );

	/*SETS THE ENVIRONMENT */
	setenv("SHELL", PATH_OF_SHELL, 1 );
	/*HANDLES THE BATCH FILE*/
	if( argc > 2 )
	{ cout << "TOO MANY ARGUMENTS " << endl; }
	/*RUNS THE BATCH FILE*/
	if( argc == 2 )
	{ File_Read( argv[ 1 ] ); }

	while( !feof( stdin ) )/*READS FILE UNTIL QUIT*/
	{
		Path_NEW();
		cout << PATH_O_S << " " << endl;

		if( fgets( Input, BUFFER_MAX_SIZE, stdin ) )
		{
			TOKENIZE();
			In_The_Back = 0;
			if( arg_n > 1 && !strcmp( ARG_S[ arg_n - last], "&") )
			{
				ARG_S[ arg_n - last ] = (char*)0;
				In_The_Back = 1;
			}
			/*HANDLE BACKGROUND*/
			if( In_The_Back )
			{
				switch( fork() )
				{	
					case -1:
						ERROR("ERROR IN FORK");
						break;
					case 0:/*RUN CHILD PROCESS*/
						setenv("PARENT", PATH_OF_SHELL, 1 );
						Exe_Cmnd();
						exit( 0 );/*CHILD PROCESS TERMINATED*/
						break;
				}
			}
			else
			{ Exe_Cmnd(); }
		}
	}

	system("pause");
	/*MAIN FUNCTION TERMINATES*/
	return 0;
}
