#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "file"

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$`~^&*()_+-=abcdefghijklmnopqrstuvwxyz0123456789";

int filevar,fileexec;

int Ninti(int n) { return rand() % n; }

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

int main(int argc, char **argv) {
//   srand(time(NULL));
  int x=0;

    mknod(FIFO_NAME, S_IFIFO | 0666, 0);
    // printf("waiting for readers...\n");
    fileexec = open(FIFO_NAME, O_WRONLY);
    // printf("got a reader--type some stuff\n");
  char* str_arr[50];

  for(int i=0;i<50;i++){
    char *p;
    p = randomString(8);
    str_arr[i] =p;
    // printf("%s ",str_arr[i]);
  }

  
  

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

        if ((filevar = write(fileexec, str, strlen(str))) == -1){
            perror("some error occured");
        }

        else{
            printf("String number %d written successfully!!",x-1);
            printf("\n");
        }
  }

}
