#include "us_xfr.h"
#include <stdio.h>
#include <unistd.h>

int main(){
	ssize_t numRead;
	int fd;
	struct sockaddr_un addr;
	char buf[BUF_SIZE];
	char buff2[BUF_SIZE]={"Concatenated!"};
	fd=socket(AF_UNIX, SOCK_STREAM,0);
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);
	bind(fd,(struct sockadrr_un*) &addr, sizeof(struct sockaddr_un));
	connect(fd, (struct sockaddr_un*) &addr, sizeof(struct sockaddr_un));
	while (numRead=read(STDIN_FILENO,buf,BUF_SIZE)){
		printf("Enter your message");
 		if (write(STDOUT_FILENO,buf,numRead)!=numRead){
 			printf("failed write");
 		}
 	//exit(EXIT_SUCCESS);
	}
}