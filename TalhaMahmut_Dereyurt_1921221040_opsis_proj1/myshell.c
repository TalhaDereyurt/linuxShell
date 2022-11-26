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

int main()
{
    char entry[150];
    bool catControl = true; // cat control
    bool errorControl = true; // if input invalid
    while (1)
    {
        printf("myshell>>");
        fgets(entry, 150, stdin); 
        char *token = strtok(entry, " ");
        while (token != NULL)
        { 
            if (strcmp(token, "cat") == 0)
            {
                printf("%s:", token);
                catControl = false;
            }
            else if (catControl == false)
            {
                printf(" %s", token);
            }
            token = strtok(NULL, " ");
            if (catControl == true)
            {

                if (strcmp(entry, "exit\n") == 0)
                { // compare
                    exit(0);
                }
                if (strcmp(entry, "bash\n") == 0)
                {
                    runBash();
                }
                else if (strcmp(entry, "ls\n") == 0)
                {
                    runLs();
                }
                else if (strcmp(entry, "clear\n") == 0)
                {
                    system("clear");
                }
                else
                {
                    if (errorControl == true)
                    {
                        printf("Entered wrong entry\n");
                        errorControl = false;
                    }
                }
            }
        }
        errorControl = true;
        catControl = true;
    }
}

void runBash()
{
    int pid = fork();
    if (pid == 0)
    {
        int e = execvp("bash", NULL);
        perror("");
    }
    else
    {
        wait(&pid);
    }
}

void runLs()
{
    int pid = fork();
    if (pid == 0)
    {
        int e = execvp("/bin/ls", NULL);
        perror("");
    }
    else
    {
        wait(&pid);
    }
}