/*
Vasim & Kenny
Operating System Project - Summer 2013

This file includes the main function of program
*/#include"myshell.h"

/*READ FILE LINES*/
void File_Read( char * );

/*EXECUTES COMMANDS*/
void Exe_Cmnd();

//CHANGE PATH THEN CLOSE
void Close_IO();

/*CHANGE IO DIRECTION*/
void Change_IO( int );/*permission to read*/

/*ACTIVATES CHILD*/
void Child_Activate();

/*CONVERTS FILE CHARS TO TOKENS*/
void TOKENIZE();

/*PATH IS UPDATED*/
void Path_NEW();

/*DISPLAYS ERROR MESSAGE TO USER*/
void ERROR( char * );/*
