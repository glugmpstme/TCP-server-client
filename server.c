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
char buff[500];
int sockfd,newsockfd,portno,clength,var,flag=0;
struct sockaddr_in serv_addr , cli_addr;

/*
   sin_family, sin_port,sin_zero[8]
*/
//using the socket() function
sockfd = socket(AF_INET,SOCK_STREAM,0);
if(sockfd < 0)
    error("socket won't work");
//assigning all the values
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = INADDR_ANY;

//using the bind() function
if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    error("error in binding");

//using the listen() function
listen(sockfd,10);

//using the accept function
clength= sizeof(cli_addr);
newsockfd=accept(sockfd, (struct sockaddr *)&cli_addr,&clength);

if(newsockfd < 0)
    error("error");
bzero(buff,200);
//read function

var=read(newsockfd,buff,200);
if(var<0)
    error("error reading");
//printing the stuff
printf("%s",buff);
//writing back to the server
printf("enter the reply\n");
fgets(buff,500,stdin);
var=write(newsockfd,buff,500);
if(var < 0)
    error("error writing");


close(sockfd);
return 0;
}

