#include <stdlib.h>
#include <stdio.h>

int main(){
	char buffer[30];
	char *msg="New World";
	strcpy(buffer,msg);
	int fd;
	write(fd,buffer,strlen(buffer));
}