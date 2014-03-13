/*
 * The main program file. This will have all of the code that opens a socket and calls all of
 * functions in functions.c when a connection is made. 
 */
#include <stdio.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include "functions.c"
/*End includes*/

int sockfd; // The socket pointer
/*End globals*/

void cleanExit() 
{
    // close sockfd
    close(sockfd);
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGTERM, cleanExit);
    signal(SIGINT, cleanExit);
    int newsockfd; // The socket you get with a connection
    int port = 8000; // The port you listen on
    int clilen; // The length of the client's address
    int yes = 1;
    int n;
    char buffer[2048];
    struct sockaddr_in serv_addr; // The server's address
    struct sockaddr_in cli_addr; // The client's address
    clilen = sizeof(cli_addr);

    //Try to open up the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Could not open socket");
        return EXIT_FAILURE;
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&yes, sizeof(int) );

    bzero((void*) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    //Bind the host address to the socket
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    {
        perror("ERROR on binding");
        return EXIT_FAILURE;
    }

    //Listen till you get a connection
    listen(sockfd, 1);

    while (1) { // go forever!
        // Accept actual connection from the client
        if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
            perror("ERROR on accept");
            return EXIT_FAILURE;
        }

        if((n = read(newsockfd, buffer, 2048)) > 0){
            //Do some stuff here.  
            char* dateData;
            char* kernelData;
            char* networkData;
            char* diskSpace;
            char* loggedIn;
            kernelData = getKernelName();
            dateData = getDate();
            networkData = getNetwork();
            diskSpace = getDiskSpace();
            loggedIn = getLoggedInUsers();
            write(newsockfd, "uname -a: \n", strlen("uname -a: \n"));
            write(newsockfd, kernelData, strlen(kernelData));
            write(newsockfd, "date: \n", strlen("date: \n"));
            write(newsockfd, dateData, strlen(dateData));
            write(newsockfd, "ss -s: \n", strlen("ss -s: \n"));
            write(newsockfd, networkData, strlen(networkData));
            write(newsockfd, "df: \n", strlen("df: \n"));
            write(newsockfd, diskSpace, strlen(diskSpace));
            write(newsockfd, "who -a: \n", strlen("who -a: \n"));
            write(newsockfd, loggedIn, strlen(loggedIn));
        }
        // close newsockfd
        close(newsockfd);
    }
    // close sockfd
    close(sockfd);

    exit(0);
    //Open socket and wait for something to happen
    return 0;
}