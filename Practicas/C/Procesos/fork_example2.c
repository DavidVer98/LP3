#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_CHILD 5

int doSomething(void)
{
    int ret;
    srand(getpid());
    ret = (rand() %256);
    printf("Hijo PID: %d, valor aleatorio calculado %d \n", getpid(), ret);
    return ret;
}

int main(void)
{
    pid_t pidC ;
    int status;
    for(int i=0; i<NUM_CHILD; i++)
    {
        pidC = fork();
        if(pidC > 0)    // padre
        {
            continue;
        }
        else if (pidC ==0)      //hijo
        {
            exit(doSomething());
        }
        else{} /*Error*/
    }
    for (int i = 0; i < NUM_CHILD; i++)
    {
        pidC =wait(&status);
         printf("Padre de PID: %d, valor %d terminado, st = %d \n", getpid(), pidC, WEXITSTATUS(status));
        
    }
    
    while (1){
        sleep(10);
    }

    return 0;
}