/*  Code to run a simple client in the internet domain communication via
    TCP.
    Peter Vincent
    Adapted from http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
    If the server recieves -1, it closes the socket with the client.
    If the server recieves -2, the program exits.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, portno = 52596, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 2){
        fprintf(stderr,"usage %s hostname, portnum \n", argv[0]);
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd < 0) error((const char*) "ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Host not found, check arguments\n");
        exit(1);
    }
    bzero((char*)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server -> h_addr_list[0],(char*)&serv_addr.sin_addr.s_addr,
    server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) error((const char *) "ERROR connecting");
    printf("Enter commands now \n");
    bzero(buffer,256);


    
    int com;
    system ("/bin/stty raw");
    bool live = true;
    while (live){
        com=getchar();
        buffer[0] = com;
        buffer[1] = '\n';
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) fprintf(stdout,"Message not sent");
        printf("\b");
        if (*buffer == 'k') live = false;
    }
    system ("/bin/stty cooked");
    fprintf(stdout,"connection terminated \n");
    return 0;

    //while


}