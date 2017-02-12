

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd,var,portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buff[500];
    portno=atoi(argv[2]);  
    server= gethostbyname(argv[1]);

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    	error("socket won't open");

    serv_addr.sin_family=AF_INET;
    
    bcopy((char *)server->h_addr,((char *)&serv_addr.sin_addr.s_addr,server->h_length));
    
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("error connecting");
    printf("Enter the message: ");
    fgets(buff,500,stdin);
    var=write(sockfd,buff,strlen(buff));
    if(var<0)
    	error("error writing");
    bzero(buff,500);
    var= read(sockfd,buff,500);
    if(var<0)
    	error("error reading");
    printf("%s",buff);

    close(sockfd);
return 0;
}

