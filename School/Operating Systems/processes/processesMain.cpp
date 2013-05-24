/* 
 * File:   processesMain.cpp
 * Author: Jonathan Difrancesco 
 
 * This program was created to to fill the requirements of Project 1 
 *  of CSS430 in FALL12 from DR. Joe McCarthy
 
 This program emulates the POSIX command ps -A | grep argv[1] | wc -l 
 using pipes and forked processes. 
 
 RUNNING INSTRUCTIONS - ./Processes.out <argv[1]>
 
 Assumptions:
 
 -There will be one and only one argument passed
 -Program will be compiled and run on a POSIX compatable system 
 -There are sufficent resources available and permissions for program to execute
 
 (Program was tested on OSX v10.8.1)
 
 
 
 * 
 * (Much of the code of this is designed from the "pipedup2X.cpp" 
 * examples provided from the webpage)
 *
 * Created on October 8, 2012, 6:10 PM
 */

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

const int MAXLINE = 80;

using namespace std;



int main (int argc, char** argv)
{
  
  int pipe1[2]; // Initialize 2 pipes arrays
  int pipe2[2];  
  int pid;
  char line[MAXLINE];
  
  assert(argc == 2); //kill the program unless there is an argument (and a .out)
  
  if (pipe(pipe1) < 0 || pipe(pipe2) < 0) // Generate 2 pipes used in program
  {
      perror ("pipe");
      exit( EXIT_FAILURE);
  }
  
  if((pid = fork()) <0) //Fork Processes
  {
      perror("fork");
      exit(EXIT_FAILURE);
  }
  
  if(pid >0)  // This is the parent
  {
    close( pipe1[1]); //close read-end of pipe
    close( pipe1[0]); //close original write-end of pipe
    close( pipe2[1]); 
    close( pipe2[0]);
    wait( NULL);  
    exit ( EXIT_SUCCESS);
    
  }
  else // fd[0] = Read end
  {    // fd[1] = Write end
    if((pid = fork()) <0) 
    {
       perror("fork");
       exit(EXIT_FAILURE);
    }
    
    if(pid>0) // = child
    {
       
       close( pipe1[1] );
       close( pipe2[1]);
       close(pipe2[0]);
       dup2( pipe1[0],0 ); //Read only from pipe1
       close( pipe1[0] );
       wait(NULL);
       
       execlp( "wc", "wc", "-l", NULL);
       perror("execlp (wc)");
       exit(EXIT_FAILURE); 
    }
    
    else
    {
      if((pid = fork()) <0) // Attempt to fork process
      {
          perror("fork");
          exit(EXIT_FAILURE);
      }
      
      if(pid>0) // = grand-child (Executes second command)
      {
          close( pipe1[0]); // close read end of pipe one
          close( pipe2[1]); // close write end of pipe two
          dup2( pipe1 [1], 1); // set up for reading from pipe two
          dup2( pipe2 [0], 0); // and writing to pipe2
          close( pipe1[1]);
          close( pipe2[0]);
          
          wait(NULL);
          

          execlp( "grep", "grep", argv[1] , NULL); // Execute "grep" with supplied arg
          perror("execlp (grep)");
          exit(EXIT_FAILURE);
      }
      
      else
      {
         if((pid = fork()) <0) // Attempt to fork process
         {
             perror("fork");
             exit(EXIT_FAILURE);
         }
      
         if(pid>0)  // = great Grand Child (Executes first command
         {
           close( pipe1[1] );  // Close both ends of Pipe1
           close( pipe1[0] );
           close( pipe2[0] ); // Close read-end of Pipe2 
           dup2( pipe2[1], 1 ); // Copy fd from write end of pipe2
           close( pipe2[1] ); // Close write-end of Pipe2
               
           execlp( "ps", "ps", "-A", NULL ); // Executes first chain of program
           
           perror("fork"); // BAD END -> Should never get here
           exit(EXIT_FAILURE);
         }
      }
    }   
  }
  return 0; // Program ends successfully 
}




