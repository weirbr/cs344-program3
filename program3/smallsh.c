/*****************************************************************************
 ** Filename:    smallsh.c
 ** Author:      Scott Milton
 ** Date:        11/23/15
 **
 ** Description: This program is a small shell that runs command line
 **              instructions and returns results. It allows redirection of
 **              standard input and standard output and supports both
 **              foreground and background processes. The shell supports three
 **              built in commands: exit, cd, and status. It also supports
 **              comments, which are lines beginning with the # character.
 **
 ** Input:       from the keyboard: type char*
 **              from files:        type char*
 **
 ** Output:      to the console and files : type char*, int
 **              to files:                  type char*, int
 **
 **
 **
 *****************************************************************************/

#include <errno.h>     // for errno
#include <signal.h>
#include <stdio.h>     // for fgets (, fopen, fclose, fseek)
#include <string.h>    // for strcpy, strcat
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for waitpid

/*
#include <stdlib.h>    // for rand and srand
#include <unistd.h>    // getpid
#include <sys/stat.h>  // for stat
#include <time.h>      // for time
#include <fcntl.h>     // for open
*/

#define MAX_ARGS        512 // maximum arguments accepted on command line
#define MAX_LENGTH     2048 // maximum length for a command line

/*
#define BUFFER_SIZE     512 // used for I/O operations
*/

// define bool as type
typedef enum { false, true } bool;



int main(int argc, char** argv) {

    // declare variables
    bool repeat = true;
    char input[MAX_LENGTH];
    char* token;
    pid_t cpid;
    int status;
//    int argCount;


    // conditional check: is this child process
    // if so, behave appropriately
    // do this here or in other files???

    do
    {

        // check to see if any bg process completed by using waitpid
            // lec 9 pg 5
        cpid = waitpid(-1, &status, WNOHANG);

        // POINT A
        // if command is bg process
        // then print process id when begins
        // when bg process terminates
        // then print process id and exit status

        // flush out prompt each time it is printed
        fflush(stdin);

        // prompt user for input
        printf(": ");

        // get user input
        fgets(input, MAX_LENGTH, stdin);

        // validate input?
            // do not need to do error checking for syntax

        // check for blank line
        if (input[0] == '\n')
        {
            printf("blank line\n");
            continue;
        }

        // loop to process args (up to 512)
        // make sure not more than max length for command line
            // error if too long? or just truncate and ignore excess?

        // parse user input
        // problem here is that single-word command will end with newline
        // while command with args will end with space
        token = strtok(input, "\n");
        // possible solution -- could tokenize for space first / each time
        // then compare length, if equal, there were no spaces, so then
        // tokenize for newline character
        // or token returns null pointer if no match found so could check for that
            // but can still use string after that???
        // or could use diff approach with strchr()
            // which gets the index of 1st matched char or returns null if not found


        // be better to remove leading space(s) before 1st command
            // implement this if time permits

        // if one of three built in commands
        // do not need to support I/O redirection
        // do not have to set any exit status

        if (strncmp(token, "#", 1) == 0)
        {
            printf("comment\n");
        }
        else if (strcmp(token, "exit") == 0)
        {
            // if command is exit
            // then kill any processes or jobs that shell has started
            kill(0, SIGTERM);       

            // and then exit the shell
            repeat = false;
        }
        else if (strcmp(token, "cd") == 0)
        {
            printf("cd\n");
            // if command is cd
            // then change directories
            // if no args, change to directory specified in HOME env var
            // if one arg, change to dir provided
                // support absolute and relative paths
            // this is working directory
            // when process exits
        }
        else if (strcmp(token, "status") == 0)
        {
            printf("status\n");
            // if command is status
            // then print exit status or terminating signal of last fg command
        }
        else
        {
            printf("default\n");
            // pass through to BASH
        }

    } // repeat until user exits shell
    while(repeat == true);

    // use fork, exec, and waitpid to execute commands
    // conditional check: foreground or background
    // shell will wait for fg commands before prompting for next command
    // shell will not wait for bg commands before prompting for next command
    // conditional check: did user specify file to take standard input?
    // if so, use that
    // if not, bg command redirect standard input from /dev/null

    // use the PATH variable to look for commands
    // allow shell scripts to be executed
    // the right version of exec will do this automatically
    // if command fails b/c shell could not find command to run
    // then print error message
    // exit with status 1

    // after fork
    // input/output redirection
    // redirected input file is opened for reading only
    // if cannot open file for reading
    // then print error message
    // and exit with status 1
    // before exec


    // if command is terminated by signal
    // then print message indicating which signal terminated the process

    // catch CTRL-C interrupts from keyboard
    // make sure they do not terminate shell or bg commands, but only fg command

    // any other command is passed on to member of exec() family of functions

    // if command is blank line or comment
    // then ignore it, do nothing, and reprompt for another command

    return 0;
}
