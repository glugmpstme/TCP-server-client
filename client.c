#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>


void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd,var,portno,flag=0;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buff[500];
    server = gethostbyname(argv[1]);
    if (server == NULL) 
        error("ERROR, no such host");
    portno = atoi(argv[2]);  

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    	error("socket won't open");
    
    bzero((char *) &serv_addr , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

   
    printf("Enter the message: ");
    bzero(buff,500);
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

