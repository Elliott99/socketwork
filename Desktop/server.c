#include <stdio.h>
#include <stdlib.h>
#include "us_xfr.h"//sock_path is the path I will bind my socket's path to
#include <unistd.h>
//Our "address" is a struct that contains the comms type and the path
int main(){
 struct sockaddr_un addr; 
 char buffer[BUF_SIZE];
 int fd;
 int cfd;
 ssize_t numRead;
 //socket: takes AF_UNIX (IPC comms), SOCK_STREAM(not datagrams)
 fd=socket(AF_UNIX,SOCK_STREAM,0);
 //zero out memory: need address of address struct, and size of struct
 memset(&addr,0,sizeof(struct sockaddr_un));
 addr.sun_family=AF_UNIX;
 strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path)-1);
 //bind: Takes 3 args: socket, pointer to memory address of address struct, sizeof adress struct
 bind(fd,(struct sock_addr *) &addr, sizeof(struct sockaddr_un)-1);
 listen(fd,5);
 //Now: I iterate over every prospective request to join from the client(s)
 //I do this in an infinite loop. If the connection is accepted, then I
 //keep the listening socket open and spawn a new socket from accept
 for (;;){
 	cfd=accept(fd,NULL,NULL);
 	while (numRead=read(cfd,buffer,sizeof(buffer)-1)>0){
 		if (write(STDOUT_FILENO,buffer,numRead)!=numRead){
 			printf("failed write");
 		}
 	}
 }
 close(cfd);

}