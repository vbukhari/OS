/*
Vasim & Kenny
Operating System Project - Summer 2013

This file includes all the library & global variable & functions declaration 
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#ifdef BSD
#include <unistd.h>/*FOR FUNCTIONS LIKE getpass() FROM LINUX*/
/*USED AS PREPROCESSOR FOR WUNTRACED IN THE WAITPID F^n OF HELP*/
#include <sys/wait.h>
#include <dirent.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

using namespace std;

#define BUFFER_MAX_SIZE 1024/*MAXIMUM BUFFER SIZE*/
#define FILENAME_MAX_SIZE 256/*MAXIMUM NUMBER OF CHARACTERS TO NAME FILE*/
#define MAX_ARGUMENTS 64/*MAXIMUM NUMBER OF STRING ARGUMNET*/
#define SEP_TAB_NWline "\t\n"/*TOKEN DELIMITERS*/
/*FUNCTION TO READ THE FILE*/
void File_Read( char nameFile[ FILENAME_MAX_SIZE] )
{
  FILE *file;
	int loc = 1;
	/*OPENS FILE*/
	file = fopen( nameFile, "r" );
	if( file == NULL )/*IF FILE IS EMPTY DISPLAY ERROR MESSAGE*/
	{ ERROR("File of Batch Doesn't exist"); }
	/*READS THE FILE LINE BY LINE*/
	while( fgets( Input, BUFFER_MAX_SIZE, file ) )
	{
		cout << loc++ << ". " << Input;/*DISPLAYS USER INPUT*/
		TOKENIZE();/*MAKES TOKENS OF CHARS IN FILE*/
		Exe_Cmnd();/*PERFORMS COMMAND*/
		cout << "\n";
	}
	fclose( file );/*ONCE FILE IS DONE CLOSES FILE*/
	exit( 0 );/*EXITS FUNCTION*/
}
/*EXECUTES USER INPUT/COMMAND*/
void Exe_Cmnd()
{
	char *tmp_I, *tmp_II;
	char *User_Input;
	int STAT;
	pid_t pid;
	if( ARG_S[ 0 ] )/*SOME MATCH IN INTERNAL COMMAND TO EXECUTE*/
	{
		/*CHANGE DIRECTORY*/
		if( !strcmp( ARG_S[ 0 ], "cd" ) )
		{
			if( !ARG_S[ 1 ] )
			{ cout << PATH_O_S << endl; }
			else
			{
				if( chdir( ARG_S[ 1 ] ) )/*IF EXISTS A DIRECT*/
				{ 	Path_NEW(); 
					/*SHELL COMND: assigns values to environment variables*/
					setenv( "PWD", PATH_O_S, 1 );
				}
				else
				{ cout << ARG_S[ 1 ] << "DOES NOT EXISTS IN CURRENT DIRECTORY OR FILE" << endl; }
			}
		}
		/*CLEAR ALL INPUTS ON THE SCREEN*/
		if( strcmp( ARG_S[0], "clr" ) )
		{ system("clear" ); }
		/*DISPLAY ALL FILES IN CURRENT DIRECTORY*/
		if( !strcmp( ARG_S[ 0 ], "dir" ) )
		{
			Change_IO( 0 );/*IO MANIPULATION*/
			tmp_I[ BUFFER_MAX_SIZE ];
			strcpy( tmp_I, "ls -la " );
			if( ARG_S[1] )
			{
				strcat( tmp_I, ARG_S[ 1 ] );
				system( tmp_I );/*EXTERNAL COMMAND FROM SHELL*/
				Close_IO();/*RETURN FROM PREVIOUS*/
			}

		}
		/*DISPLAYS BACK INPUT FROM USER*/
		if( !strcmp( ARG_S[ 0 ], "echo" ) )
		{
			Change_IO( 0 );
			User_Input[ BUFFER_MAX_SIZE ];
			strcpy( User_Input, "" );
			ARG_N = &ARG_S[ 1 ];
			while( *ARG_N )
			{
				strcat( User_Input, *ARG_N++ );
				strcat( User_Input, " " );/*IF EXTRA SPACES THEN DISPLAY ONLY ONE*/
			}
			cout << User_Input << endl;/*displays user input*/
			memset( User_Input, 0, BUFFER_MAX_SIZE );/*erases input in mem buff*/
			free( User_Input );
			Close_IO();/*RETURN FROM PREVIOUS*/
		}
		/*REVISE***REVISE***REVISE***REVISE***REVISE*/
		/*DISPLAYS USER MANUAL*/
		if( !strcmp( ARG_S[ 0 ], "help" ) )
		{
			Change_IO( 1 );
			tmp_II[ BUFFER_MAX_SIZE ];
			getcwd( tmp_II, BUFFER_MAX_SIZE );
			strcat( tmp_II, INIT_PATH );
			strcat( tmp_II, "/readme");
			pid = getpid();
			switch( pid = fork() )
			{
			case -1:
				syserr("fork");
			case 0:
				setenv( "parent", getenv("shell"), 1 );
				if( Flag_Change[ 1 ] == 1 )
				{  freopen( File_Change[ 1 ], "w", stdout ); }
				if( Flag_Change[ 0 ] == 1 )
				{ freopen( File_Change[ 0 ], "a", stdout ); }
				if( execlp( "more", "more", tmp_II, NULL ) < 0 )
				{ syserr( "execlp" ); }
			default:
				if( arg_n > 1 && !strcmp( ARG_S[ arg_n - 1], "&") )
				{ waitpid( pid, &STAT, WUNTRACED); }
			}
		}
		if( !strcmp( ARG_S[ 0 ], "pause" ) )/*PAUSES UNTIL USER PRESS ENTER*/
		{ getpass("PRESS ENTER TO CONTINUE\n"); }
		if( !strcmp( ARG_S[ 0 ], "quit" ) )/*TERMINATE SHELL*/
		{ exit( 0 ); }
		else/*COMMANDS FROM USER NOT FOUND*/
		{
			signal( SIGINT, SIG_IGN );
			switch( pid = fork() )
			{
			case -1:
				ERROR("ERROR: OPERATION DID NOT FORK");
				break;
			case 0:
				setenv("PARENT", PATH_OF_SHELL, 1 );
				Change_IO( 1 );
				if( execvp( ARG_S[ 0 ], ARG_S ) == -1 )
				{ ERROR( "INPUT COMMAND NOT FOUND" ); exit( 1 ); }
				break;
			}
		}
		fflush(stdout);
		waitpid( pid, &STAT, 0 );/*HOLDS FOR CHILD PROCESS TO TERMINATE*/
	}

}
//CHANGE REDIRECT PATH THEN CLOSE
void Close_IO()
{
	if( Flag_Change[ 0 ] || Flag_Change[ 0 ] )
	{ freopen("/dev/tty", "w", stdout); }
}
/*CHANGES DIRECTION OF IO TO FILE*/
void Change_IO( int Per_To_Read )/*permission to read*/
{
	if( Flag_Change[ 0 ] == 1 )
	{ freopen( File_Change[ 0 ], "a", stdout ); }/*APPEND TO FILE*/
	if( Flag_Change[ 1 ] == 1 )
	{ freopen( File_Change[ 1 ], "w", stdout ); }/*WRITE TO FILE*/
	if( Flag_Change[ 2 ] == 1 && Per_To_Read == 1)
	{ freopen( File_Change[ 2 ], "r", stdin ); }/*READ FROM FILE*/
}
/*ASSIGNS HANDLE TO CHILD PROCESS ON EXIT SIGNAL( CTRL + C*/
void Child_Activate()
{
	signal( SIGINT, SIG_IGN );
	cout << "\n" << endl;
}
/*BREAKS UP CHARACTERS INTO TOKENS*/
void TOKENIZE()
{
	char *tmp_I, *tmp_II;
	for( int i = 0; i < 3; i++ )
	{ 
		/**************
		 * 0 = APPEND *
		 * 1 = WRITE  *
		 * 2 = READ   *
		 **************/
		Flag_Change[ i ] = 0;
		if( (tmp_II = strstr( Input, Input_Sym[ i ] ) ) != NULL )
		{
			/*ASSIGNS FILE NAME TO TMP_I*/
			tmp_I = strtok( tmp_II + strlen(Input_Sym[ i ]), SEP_TAB_NWline);
			strcpy( File_Change[ i ], tmp_I );
			Flag_Change[ i ] = 1;

			*tmp_II = '\O';
			if( ( tmp_II = strtok( NULL, SEP_TAB_NWline) ) != NULL )
			{ strcat( Input, tmp_I); }
		}
	}
	/* MAKE TOKENS CONVERT TO ARG_S */
	arg_n = 1;
	ARG_N = ARG_S;
	*ARG_N++ = strtok( Input, SEP_TAB_NWline );/*TOKENIZING*/
	while( ( *ARG_N++ = strtok(NULL, SEP_TAB_NWline ) ) )
	{ arg_n++; }/*LAST ENTRY = NULL*/
}
/*CHANGE TO CURRENT PATH*/
void Path_NEW()
{ getcwd(PATH_O_S, BUFFER_MAX_SIZE - 1 ); }
/*DISPLAYS ERROR MESSAGE*/
void ERROR( char chars[ BUFFER_MAX_SIZE ] )
{
	char *tmp = chars;
	cout << tmp << "\n";
	exit( 1 );
}
