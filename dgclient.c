#include "dg.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char*argv[]){
	int fd;
	struct sockaddr_un svadr,cladr,cladr2;
	size_t msglen;
	ssize_t numBytes;
	char resp[BUF_SIZE];
	char msg[BUF_SIZE];
	int j;
	ssize_t numBytes2;
	socekt_t len;
	fd=socket(AF_UNIX, SOCK_DGRAM,0);
	//clear out the address of the socket just in case something previously existed thete
	memset(&cladr,0,sizeof(struct sockaddr_un));
	cladr.sun_family=AF_UNIX;
	//I bind a unique pathname for my client socket on the PID
	snprintf(cladr.sun_path,sizeof(cladr.sun_path),
		"/tmp/ud_ucase_cl.%ld",(long) getpid());
	//Now i can bind my client socket to the struct for the address
	bind(fd, (struct sockaddr_un*) &cladr,sizeof(struct sockaddr_un));
	//Now I create the address of my server
	memset(&svadr,0,sizeof(struct sockaddr_un));
	strncpy(svadr.sun_path,SV_SOCK_PATH,sizeof(svadr.sun_path));
	svadr.sun_family=AF_UNIX;
	for (;;){
		for (j=1;j<argc;j++){
			sendto(fd,argv[j],msglen,0,(struct sockaddr_un*) &svadr, 
			sizeof(struct sockaddr_un));
			printf("Response %d: %.*s\n",j,(int) numBytes,resp);
	}
		len=sizeof(struct sockaddr_un);
		numBytes2=recvfrom(fd,msg,BUF_SIZE,0,(struct sockaddr_un*) &cladr2,&len);
		printf("Message received from client2: %s", msg);
}
}