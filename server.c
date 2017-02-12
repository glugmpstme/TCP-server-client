/*socket()---bind()---listen()---accept()---read()---write() */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>


void error(char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc,char *argv[])
{
char hostname[100];
char ipadd[100];
char buff[500];
int sockfd,newsockfd,portno,clength,var;
struct sockaddr_in serv_addr , cli_addr;

/*
   sin_family, sin_port,sin_zero[8]
*/
//using the socket() function
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
    error("socket won't work");
}
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = INADDR_ANY;
//using the bind() function
if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    error("error in binding");
//using the listen() function
listen(sockfd,10);
//no need to check for error as socket argument has to be valid by this point.
clength= sizeof(cli_addr);
newsockfd=accept(sockfd, (struct sockaddr *)&cli_addr,&clength);
if(newsockfd==-1)
    error("error");
if(var=read(newsockfd, buff,200) < 0)
    error("error reading");
printf("%s",buff);

if(var=write(newsockfd,"maacarena",10) < 0)
    error("error writing");

close(sockfd);
return 0;
}

