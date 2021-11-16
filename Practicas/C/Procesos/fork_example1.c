#include <stdio.h>
#include <unistd.h>

int var = 22;

int main(void){

    pid_t pidC;

    printf("** Proceso PID = %d comineza ... ***\n",getpid());
    pidC = fork();
    printf("Proceso PID = %d ejecutandose ...\n",getpid());

    if(pidC > 0)
    {
        var = 44;
    }
    else if(pidC ==0){
        var = 33;
    }
    else /*Error*/
        return -1;
    while(1)
    {
        sleep(2);
          printf("Proceso PID = %d, var = %d ejecutandose ...\n",getpid(), var);
    }

    return 0;
}