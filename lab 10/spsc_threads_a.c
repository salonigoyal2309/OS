#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#define size 10
int thread1wantstoenter=0,thread2wantstoenter=0;
int favouredthread=1;

int pindex=0,cindex=0,n=0;
int buf[10];

int myrand(int n){
 
    time_t t; 
    srand((unsigned)time(&t)); 
    return (rand() % n + 1); 
} 


void *Producer()
{

	int i;
	while(1){
	
		favouredthread=2;
		printf("Producer is in Non Critical Section!\n");
		sleep(1);
		thread1wantstoenter=1;
		while(thread2wantstoenter==1 && favouredthread==2){
		
			printf("Producer is waiting for entering in Critical Section!\n");
			sleep(1);
			
		}
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
		sleep(1);
		thread1wantstoenter=0;
	
	}
	pthread_exit(NULL);
	
}

void *Consumer()
{
	int i;
	while(1){
	
		favouredthread=1;
		printf("Consumer is in Non Critical Section!\n");
		sleep(1);
		thread2wantstoenter=1;
		while(thread1wantstoenter==1 && favouredthread==1){
		
			printf("Consumer is waiting for entering in Critical Section!\n");
			sleep(1);
			
		}
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
		sleep(1);
		thread2wantstoenter=0;
	
	}
	pthread_exit(NULL);
}
  
int main(void){

	long int i;
	
	for(i=0;i<size;i++){
		buf[i]=-1;
	}
	
        pthread_t tid,tid1[2];
   	pthread_create(&tid, NULL, Producer,NULL);
        pthread_create(&tid1, NULL, Consumer,NULL);
	pthread_join(tid,NULL);
        pthread_join(tid1,NULL);
	
        pthread_exit(NULL);

        
}
