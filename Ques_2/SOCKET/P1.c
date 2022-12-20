#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define FILENAME "file"
#define PORT 1010

//@ https://www.geeksforgeeks.org/socket-programming-cc/
//@ https://beej.us/guide/bgipc/html/single/bgipc.html#unixsock

struct sockaddr_in serv_addr;

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$`~^&*()_+-=abcdefghijklmnopqrstuvwxyz0123456789";

int filevar,fileexec;

int Ninti(int n) {return rand() % n;}

//@ https://siongui.github.io/2017/02/09/c-generate-random-string/

char *randomString(int len) {
  char *rstr = malloc((len + 1) * sizeof(char));
  int i;
  for (i = 0; i < len; i++) {
    rstr[i] = alphabet[Ninti(strlen(alphabet))];
  }
  rstr[len] = '\0';
  return rstr;
}


int main(void)
{
  int x=0;

  char* str_arr[50];

  for(int i=0;i<50;i++){
    char *p;
    p = randomString(8);
    str_arr[i] =p;
    // printf("%s ",str_arr[i]);
  }
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  int inet =inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
  int client_fileexec = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));


    fileexec = open(FILENAME, O_WRONLY);


    for(int i=0;i<10;i++){
    char str[100]="";
    for(int j=0;j<5;j++){
        char result[10];

        strcat(str,str_arr[i+j]);
        

        //@ https://www.geeksforgeeks.org/what-is-the-best-way-in-c-to-convert-a-number-to-a-string/#:~:text=Solution%3A%20Use%20sprintf()%20function.&text=You%20can%20also%20write%20your%20own%20function%20using%20ASCII%20values%20of%20numbers.

        
        sprintf(result, "%d", x);
        if(strlen(result)==1){
            char num[10]="0";
        strcat(num,result);
        strcat(num," ");
        strcat(str," ");
        strcat(str,num);

        x+=1;
        
        }

        else{
            strcat(result," ");
        strcat(str," ");
        strcat(str,result);

        x+=1;
        }
    }
        // printf("%s \n",str);

        send(sock, str, strlen(str), 0);
        printf("P1rocess successfull P1:",x-1);
            printf("\n");
        
  }

    
	// closing the connected socket
	close(client_fileexec);
	return 0;
}
