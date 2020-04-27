#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define size 10

int pindex=0,cindex=0,n=0;
int buf[10];
sem_t full,empty,s;
  
int myrand(int n){
 
    time_t t; 
    srand((unsigned)time(&t)); 
    return (rand() % n + 1); 
} 



void *Producer(void *arg)
{

	int i;

	while(1){
	
		sem_wait(&empty);
		printf("Producer is in Non Critical Section!\n");
		sleep(1);
		
		sem_wait(&s);
		printf("Now Producer is in Critical Section!\n");
		
		if(n==size){
			printf("buffer is full , cannot produce more\n");
		}
		else{
			buf[pindex] = myrand(50);
			printf("job %d is produced\n",buf[pindex]);
			pindex = (pindex+1)%size;
			n++;
		}
		
		for(i=0;i<size;i++){
			printf("%d ",buf[i]);
		}
		printf("\n");
		
		printf("Finally Producer is out of Critical Section!\n");
		sem_post(&s);

		sleep(1);
		sem_post(&full);

	
	}
	pthread_exit(NULL);
	
}

void *Consumer(void *arg)
{
	int i;
	
	while(1){
	
		sem_wait(&full);
		printf("Consumer is in Non Critical Section!\n");
		sleep(1);
		
		
		sem_wait(&s);
		printf("Now Consumer is in Critical Section!\n");
		
		if(n==0){
			printf("buffer is empty , cannot consume more\n");
		}
		else{
		
			printf("job %d is consumed\n",buf[cindex]);
			buf[cindex]=-1;
			cindex = (cindex+1)%size;
			n--;
		}
		
		for(i=0;i<size;i++){
			printf("%d ",buf[i]);
		}
		printf("\n");
		
		printf("Finally Consumer is out of Critical Section!\n");
		sem_post(&s);

		sleep(1);
		sem_post(&empty);
	
	}
	pthread_exit(NULL);
}
  
int main(void){

	long int i;
	
	sem_init(&empty,0,size);
	sem_init(&full,0,0);
	sem_init(&s,0,1);
	
	for(i=0;i<size;i++){
		buf[i]=-1;
	}
	
	
        pthread_t tid,tid1;
   	pthread_create(&tid, NULL, Producer,NULL);
        pthread_create(&tid1, NULL, Consumer,NULL);
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
        pthread_exit(NULL);

        
}
