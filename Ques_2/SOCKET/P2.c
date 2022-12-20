#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#define PORT 1010
#define FILENAME "file"

//@ https://beej.us/guide/bgipc/html/single/bgipc.html#unixsock

//@ https://www.geeksforgeeks.org/socket-programming-cc/

struct sockaddr_in address;
int var = 1;
int fileexec,filevar;
int addresslen = sizeof(address);
int r;
   

int main(void)
{
    int server_fileexec = socket(AF_INET, SOCK_STREAM, 0);
    int scokadd= setsockopt(server_fileexec, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &var,sizeof(var));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    int bindi= bind(server_fileexec, (struct sockaddr*)&address,sizeof(address));
    int listi= listen(server_fileexec, 3);

    int new_socket = accept(server_fileexec, (struct sockaddr*)&address, (socklen_t*)&addresslen);
    fileexec = open(FILENAME, O_RDONLY);

    char str[100];

    do {
        if ((filevar = read(fileexec, str, 60)) == -1)
            perror("read");
        else {
            str[strlen(str)] = '\0';
            printf("In process P2: %s",str);
            printf("\n");
        }
    } while (filevar > 0);

	close(new_socket);
	shutdown(server_fileexec, SHUT_RDWR);
	return 0;
}
