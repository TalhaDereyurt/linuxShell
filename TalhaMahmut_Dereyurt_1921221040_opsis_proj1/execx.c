#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    char value[110];
    int sizeValue = 1;
    read(3, value, 110); // value have number and progress name

    for (int j = 0; j < 110; j++) // finding the size of value array
    {
        if (value[j] == ' ')
            sizeValue++;
    }
    char *valueArray[sizeValue];
    int i = 0;
    char *token = strtok(value, " ");
    while (token != NULL) // adding values to array
    {
        valueArray[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    int num = atoi(valueArray[0]); // time of work the proccess
    if (strcmp(valueArray[1], "writef") == 0 && strcmp(valueArray[2], "-f") == 0)
    {
        char newName[80];
        strcpy(newName, valueArray[3]); // copying value to another string 
        char *file = newName; 
        int pid;
        int ev;
        for (int i = 0; i < num; i++) 
        {
            ev = 0;
            pid = fork();
            if (pid == 0)
            {   
                write(4, file, strlen(file)); // write file name to pipe
                ev = execv("writef", NULL);
                perror("");
                
            }else{
                wait(&ev);
            } 
        }
    }
}