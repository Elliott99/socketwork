#include "dg.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
int main(){
 int sfd;
 struct sockaddr_un svadr,cladr;
 size_t msglen;
 char buf[BUF_SIZE];
 socklen_t len;
 int j;
 ssize_t numBytes;
 sfd=socket(AF_UNIX,SOCK_DGRAM,0);
 memset(&svadr,0, sizeof(struct sockaddr_un));
 svadr.sun_family=AF_UNIX;
 strncpy(svadr.sun_path,SV_SOCK_PATH,sizeof(svadr.sun_path)-1);
 bind(sfd,(struct sockaddr_un*) &svadr, sizeof(struct sockaddr_un));
 //Now that I've binded my server socket to the server address path, I 
 //can receive messages
 for (;;){
 	len=sizeof(struct sockaddr_un);
 	//I receive the message through the socket from the address the client lives at
 	numBytes=recvfrom(sfd,buf,BUF_SIZE,0,
 		(struct sockaddr_un*) &cladr,&len);
	printf("Server received message %s",buf);
 	//I send the message I got back from the socket address back to the client uppercased
 	for (j=0;j<numBytes;j++){
 		buf[j]=toupper((unsigned char) buf[j]);
 		sendto(sfd,buf,numBytes,0,(struct sockaddr *) &cladr,len);
	}
 		}
 	}
 