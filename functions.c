/* 
 * This file will have all of the functions that call system commands and return strings.
 * Each function will return 0 on success and -1 on error and take a string, res, to 
 * return the result in. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* getTop();
char* getNetwork();
char* getKernelName();
char* getDate();
char* getDiskSpace();
char* getLoggedInUsers();
/*End prototypes*/


char* getTop()
{
//Get the header froml the top command and put it in res
    sleep(.25);
    int pipes[2];
	int pipes2[2];
    static char test[5000];
    int pid;
	int pid2;
    int status;

    if(pipe(pipes) == -1)
    {
        printf("%s\n", "Pipe error");
        fprintf(stderr, "Error creating pipe");
    }

	pid = fork();

    if(pid == -1)
    {
        printf("%s\n", "Fork error");
        fprintf(stderr, "Error forking");
    }
    else if (pid > 0)
    {
        wait(pid);
        close(pipes[1]);
        read(pipes[0], test, sizeof(test));
        close(pipes[0]);
        return test;
    }
    else if(pid == 0)
    {
		if(pipe(pipes2) == -1)
		{
		    printf("%s\n", "Pipe error");
		    fprintf(stderr, "Error creating pipe");
		}

		pid2 = fork();

		if (pid2 == -1)
		{
		    printf("%s\n", "Fork error");
		    fprintf(stderr, "Error forking");
		}
		else if (pid2 > 0)
		{
			wait(pid2);

			close(pipes2[1]);
		    dup2(pipes2[0], 0);
			close(pipes2[0]);

		    close(pipes[0]);
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[1]);

			execlp("head", "head", "-5", (char*)0);
		}
		else if (pid2 == 0)
		{
			close(pipes2[0]);
			dup2(pipes2[1], STDOUT_FILENO);
			close(pipes2[1]);
			execlp("top", "top", "-n 1", "-b", (char*)0);
		}
    }
}

char* getNetwork()
{
//Get the network info from the command ss -s 
    sleep(.25);
    int pipes[2];
    static char test[5000];
    int pid;
    int status;

    if(pipe(pipes) == -1)
    {
        printf("%s\n", "Pipe error");
        fprintf(stderr, "Error creating pipe");
    }

    pid = fork();

    if( pid == -1)
    {
        printf("%s\n", "Fork error");
        fprintf(stderr, "Error forking");
    }
    if(pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        execlp("ss", "ss", "-s", (char*)0);
    }
    else
    {
        wait();
        close(pipes[1]);
        read(pipes[0], test, sizeof(test));
        close(pipes[0]);
        return test;
    }
}

char* getKernelName()
{
    //Get the kernel name and info from uname -a
    sleep(.25);
    int pipes[2];
    static char test[5000];
    int pid;
    int status;

    if(pipe(pipes) == -1)
    {
        printf("%s\n", "Pipe error");
        fprintf(stderr, "Error creating pipe");
    }

    pid = fork();

    if( pid == -1)
    {
        printf("%s\n", "Fork error");
        fprintf(stderr, "Error forking");
    }
    if(pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        execlp("uname", "uname", "-a", (char*)0);
    }
    else
    {
        wait();
        close(pipes[1]);
        read(pipes[0], test, sizeof(test));
        close(pipes[0]);
        return test;
    }
}

char* getDate()
{
    //Get the kernel name and info from uname -a
    sleep(.25);
    int pipes[2];
    static char test[5000];
    int pid;
    int status;

    if(pipe(pipes) == -1)
    {
        printf("%s\n", "Pipe error");
        fprintf(stderr, "Error creating pipe");
    }

    pid = fork();

    if( pid == -1)
    {
        printf("%s\n", "Fork error");
        fprintf(stderr, "Error forking");
    }
    if(pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        execlp("date", "date", (char*)0);
    }
    else
    {
        wait();
        close(pipes[1]);
        read(pipes[0], test, sizeof(test));
        close(pipes[0]);
        return test;
    }
}

char* getDiskSpace()
{
//Get disk space used from command df
    sleep(.25);
    int pipes[2];
    static char test[5000];
    int pid;
    int status;

    if(pipe(pipes) == -1)
    {
        printf("%s\n", "Pipe error");
        fprintf(stderr, "Error creating pipe");
    }

    pid = fork();

    if( pid == -1)
    {
        printf("%s\n", "Fork error");
        fprintf(stderr, "Error forking");
    }
    if(pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        execlp("df", "df", (char*)0);
    }
    else
    {
        wait();
        close(pipes[1]);
        read(pipes[0], test, sizeof(test));
        close(pipes[0]);
        return test;
    }
}

char* getLoggedInUsers()
{
//Get all of the logged in users using command who -a
    sleep(.25);
    int pipes[2];
    static char test[5000];
    int pid;
    int status;

    if(pipe(pipes) == -1)
    {
        printf("%s\n", "Pipe error");
        fprintf(stderr, "Error creating pipe");
    }

    pid = fork();

    if( pid == -1)
    {
        printf("%s\n", "Fork error");
        fprintf(stderr, "Error forking");
    }
    if(pid == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        execlp("who", "who", "-a", (char*)0);
    }
    else
    {
        wait();
        close(pipes[1]);
        read(pipes[0], test, sizeof(test));
        close(pipes[0]);
        return test;
    }
}

/*int main(int argc, char const *argv[])
{
    while(1){
        char* test1;
        test1 = getKernelName();
        char* test2;
        test2 = getDate();
        printf("%s\n", test1);
        printf("%s\n", test2);
    }
}*/
