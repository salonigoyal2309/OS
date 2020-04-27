#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define size 10

enum pstate {IDLE,WAITING,ACTIVE};
enum pstate flag[size];

int myrand(int n){
 
    time_t t; 
    srand((unsigned)time(&t)); 
    return (rand() % n + 1); 
} 

  
void *EisenAndMcG(void *arg){
	
	int i = (int)arg;
	int index;
	int turn = myrand(size);
	do{
		flag[i] = WAITING;
		index = turn;
		while(index!=i){
			if(flag[index]!=IDLE) index=turn;
			else index = (index+1)%size;
		}
		flag[i]=ACTIVE;
		index=0;
		while((index<size)&&((index==i)||(flag[index]!=ACTIVE))){
			index++;
		}
		
		if((index>=size)&&((turn==i)||(flag[index]!=ACTIVE))) break;
		
	}while(1);
	
	turn=i;
	printf("Entering critical section for process %d \n",turn+1);
	printf("Executing %d's critical section.....\n",turn+1);
	printf("Exiting critical section for process %d \n",turn+1);
	
	index = (turn+1)%size;
	while(flag[index]!=IDLE){
		index = (index+1)%size;
	}
	
	turn=index;
	flag[i]=IDLE;

	
}

  
int main(void){

	long int i;
	
        pthread_t tid[size];
        for(i=0;i<size;i++){
   		pthread_create(&tid[i] , NULL, EisenAndMcG ,(void *)i);
        }
        
        for(i=0;i<size;i++){
		pthread_join(tid[i],NULL);
	}
	
        pthread_exit(NULL);

        
}
