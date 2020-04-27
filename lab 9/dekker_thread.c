#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>

int thread1wantstoenter=0,thread2wantstoenter=0;
int favouredthread=1;

void *Process1(){

	int i;

	while(1){
	
		printf("Process 1 is in Non Critical Section!\n");
		sleep(1);
		thread1wantstoenter=1;
		while(thread2wantstoenter==1){
		
			if(favouredthread==2){
			
				thread1wantstoenter=0;
				sleep(1);
				while(favouredthread==2){
				
					printf("Process 1 is waiting for entering in Critical Section!\n");
					sleep(1);
				}
				thread1wantstoenter=1;
			}
		}
		
		printf("Now Process 1 is in Critical Section!\n");
		for(i=0;i<2;i++) printf("Process 1\n");
		
		favouredthread=2;
		printf("Finally Process 1 is out of Critical Section!\n");
		sleep(1);
		thread1wantstoenter=0;
	
	}
	pthread_exit(NULL);
	
}

void *Process2(){

	int i;

	while(1){
	
		printf("Process 2 is in Non Critical Section!\n");
		sleep(1);
		thread2wantstoenter=1;
		while(thread1wantstoenter==1){
		
			if(favouredthread==1){
			
				thread2wantstoenter=0;
				sleep(1);
				while(favouredthread==1)
				{
					printf("Process 2 is waiting for entering in Critical Section!\n");
					sleep(1);
				}
				thread2wantstoenter=1;
			}
		}
		printf("Now Process 2 is in Critical Section!\n");
		for(i=0;i<2;i++) printf("Process 2\n");
		
		favouredthread=1;
		printf("Finally Process 2 is out of Critical Section!\n");
		sleep(1);
		thread2wantstoenter=0;
	
	}
	pthread_exit(NULL);
}
  
int main(void){

	int i;
        pthread_t tid,tid1;
   	pthread_create(&tid, NULL, Process1,NULL);
        pthread_create(&tid1, NULL, Process2,NULL);
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
        pthread_exit(NULL);
      
}
