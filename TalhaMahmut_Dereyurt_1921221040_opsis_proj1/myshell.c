#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

int myPipe[2];

int isNum(char s[]){ // checking str if its number
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
}
void ls(){
    int pid = fork();
    if (pid == 0)
    {
        int ev = execvp("/bin/ls", NULL);
        perror("");
    }
    else{
        wait(&pid);
    }
}

void myWrite(char *file){
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    {
        write(myPipe[1], file, strlen(file));
        ev= execv("writef", NULL);
        perror("");
        close(myPipe[1]);
    }else{
        wait(&ev);
    }
}
void myExecx(char *file){
    int ev = 0;
    int pid = fork();
    if (pid == 0)
    {
        write(myPipe[1], file, strlen(file));
        ev = execv("execx", NULL);
        perror("");
        close(myPipe[1]);
    }
}
void bash()
{
    int pid = fork();
    if (pid == 0)
    {
        int ev = execvp("bash", NULL);
        perror("");
    }else{
        wait(&pid);
    }
}

int main()
{
    if(pipe(myPipe) < 0){
        perror("");
        exit(1);
    }
    char value[110];
    int valueSize = 1;
    while (1)
    {

        printf("myshell>>");
        fgets(value, 110, stdin); // value reading
        for (int i = 0; i < 110; i++)
        {
            if (value[i] == ' ') { // finding value size
                valueSize++;
            }
        }
        char *token = strtok(value, " ");
        char *valueArray[valueSize];
        int i = 0;
        while (token != NULL){ // adding values to array, split with space
            valueArray[i++] = token;
            token = strtok(NULL, " ");
        }

        if(strcmp(value, "exit\n") == 0){
            exit(0);
        }else if(strcmp(value, "clear\n") == 0){
            system("clear");
        }else if(strcmp(value, "bash\n") == 0){
            bash();
        }else if(strcmp(value, "ls\n") == 0){
            ls();
        }else if(valueArray>1 && strcmp(valueArray[0], "cat") == 0){
            for (int i = 0; i < valueSize; i++)
            {
                if(i==0){
                    printf("%s:",valueArray[i]);
                }else{
                    printf(" %s",valueArray[i]);
                }
            }
            
        }else if(valueSize == 6 && strcmp(valueArray[0], "execx") == 0 && strcmp(valueArray[1], "-t") == 0 && isNum(valueArray[2])
        && strcmp(valueArray[3], "writef") == 0 && strcmp(valueArray[4], "-f") == 0 ){
            char myInput[100];
            strcpy(myInput,valueArray[2]);
            strcat(myInput," ");
            strcat(myInput,valueArray[3]);
            strcat(myInput," ");
            strcat(myInput,valueArray[4]);
            strcat(myInput," ");
            strcat(myInput,valueArray[5]);
            myExecx(myInput);
        }else if(valueSize == 3 && strcmp(valueArray[0], "writef") == 0 && strcmp(valueArray[1], "-f") == 0){
            char myFile[30];
            strcpy(myFile,valueArray[2]);
            myWrite(myFile);
        }else{
            printf("invalid value\n");
        }
        valueSize = 1;
    }
    return 0;
}