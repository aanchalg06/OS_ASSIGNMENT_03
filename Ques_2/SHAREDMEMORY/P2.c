#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


#define FIFO_NAME "file"

//@ https://beej.us/guide/bgipc/html/single/bgipc.html#fifos

int fileexec,filevar;

int main(void)
{
    char str[100];


    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    fileexec = open(FIFO_NAME, O_RDONLY);

    do {
        if ((filevar = read(fileexec, str, 60)) == -1)
            perror("read");
        else {
            str[strlen(str)] = '\0';
            printf("In process P2: %s",str);
            printf("\n");
        }
    } while (filevar > 0);

    return 0;
}