#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int male_counter,female_counter;
sem_t male_mutex;
sem_t female_mutex;
sem_t male_multiplex;
sem_t female_multiplex;
sem_t empty;

void delay(void)
{
    int i;
    int delaytime;
    delaytime = rand()%100;
    for (i = 0; i<delaytime; i++);
}

void *female(void *param)
{
    
  sem_wait(&female_mutex);
   
  female_counter++;
  if(female_counter==1){
    sem_wait(&empty);
;
  }
  sem_post(&female_mutex);

  sem_wait(&female_multiplex);
  printf("female in \n");
  delay();
  printf("\tfemale out \n");
  sem_post(&female_multiplex);


  sem_wait(&female_mutex);
  female_counter--;
  if(female_counter == 0){
    sem_post(&empty);
  }
  sem_post(&female_mutex);

  return 0;
}

void *male(void *param)
{           
  sem_wait(&male_mutex);
  male_counter++;
  if(male_counter==1){
    sem_wait(&empty);
  }
  sem_post(&male_mutex);

  sem_wait(&male_multiplex);
  printf("\tmale in \n");
  delay();
  printf("\t\tmale out \n");
  sem_post(&male_multiplex);

  sem_wait(&male_mutex);
  male_counter--;
  if(male_counter == 0)
    sem_post(&empty);

  sem_post(&male_mutex);
  return 0;

}



int main(void)
{
    int i,p;
    

      sem_init(&empty,0,1);

      sem_init(&male_mutex,0,1);
      sem_init(&male_multiplex,0,3);
      male_counter=0;
      sem_init(&female_mutex,0,1);
      sem_init(&female_multiplex,0,3);
      female_counter=0;

        pthread_t *tid;
        tid = malloc(80*sizeof(pthread_t));


    for(i=0;i<20;i++)
    {
	   p= rand() % 11;
    	if(p>5){
        printf("female created\n");
       		pthread_create(&tid[i],NULL,female,NULL);

	}else{
          printf("male created\n");
            pthread_create(&tid[i],NULL,male,NULL);
    	}
     }
	
	for(i=0;i<20;i++)
    	{     
            pthread_join(tid[i],NULL);
   	 }
   	
		

    return(0);
}