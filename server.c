#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define port 
void error(char *msg)
{
cout<<msg;
    exit();
}
int main(int argc,char *argv[])
{
char hostname[100];
char ipadd[100];
char buff[500];
int sockfd,portno;
struct sockaddr_in serv_addr;

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


}