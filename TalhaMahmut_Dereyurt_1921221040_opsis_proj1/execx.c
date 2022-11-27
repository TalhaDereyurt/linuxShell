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
#include <stdbool.h>

int main(){
    char input[80];
    read(3,input,80);
    char *token = strtok(input," ");
    int size = 1;
    int j = 0;
    for (int k = 0; k < 80; k++)
    {
        if(input[k]==' ')
        size++;
    }
    char *arr[size];
    while(token != NULL){
        arr[j] = token;
        token = strtok(NULL," ");
        j++;
    }
    int number = atoi(arr[0]);
    if(strcmp(arr[1],"exit") == 0) {
        for (int i = 0; i < number; i++)
        {
            
        }
        
    }
}