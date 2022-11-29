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
#include <time.h>
//
int main()
{
    int pid = getpid();   // get pid
    int ppid = getppid(); // get ppid
    char value[60];
    read(3, value, 60);                   // reading from pipe
    char *fileName = strtok(value, "\n"); // deleting extra line from file name
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime); // getting time info

    FILE *file = fopen(fileName, "a"); // opening file with append mode
    fprintf(file, "system time: %s",strtok(asctime(timeinfo),"\n"));
    fprintf(file, " pid: %d",pid);
    fprintf(file, " ppid: %d\n",ppid);
    fclose(file);

    return 0;
}