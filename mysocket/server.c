/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     /* sockfd and newsockfd are two file descriptors,
      * not a file pointer (FILE*), but a descriptoer in the
      * system, 1 for stdin, 2 for stdout, 3 for stderr, 
      * x for sockfd, y for newsockfd */
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     /* A sockaddr_in is a structure containing an internet address. 
      * This structure is defined in netinet/in.h. */
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     /* 
      * AF_INET is the type of address domain, used for two hosts communicate on the Internet 
      * SOCK_STREAM is the type of socket
      * the third argument '0' is the type of protocol (let the system choose the proper one here) 
      */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     /* sockfd = -1 if socket() failed to create a new socket */
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
