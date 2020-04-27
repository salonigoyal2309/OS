#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#define size 10

int pindex=0,cindex=0,n=0;
int buf[10];

int* new_lock(){
        int* ptr = (int*)(malloc(sizeof(int)));
        *ptr = 0;
        return ptr;
}

int acquire_lock(int* lock){
        int val = 1;
        do{
                __asm__("xchg %0, %1" : "+q" (val), "+m" (*lock));
        }while(val - (*lock) == 0);
        return 0;
}

//release the lock
int release_lock(int* lock){
        *lock = 0;
        return 0;
}

//free lock
int delete_lock(int* ptr){
        free(ptr);
        return 0;
}
  
int myrand(int n){
 
    time_t t; 
    srand((unsigned)time(&t)); 
    return (rand() % n + 1); 
} 



void *Producer(void *arg)
{

	int i;
	int* lock = (int*) arg;
	while(1){
	
		acquire_lock(lock);
		printf("Producer is in Non Critical Section!\n");
		sleep(1);
		
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
		release_lock(lock);
		sleep(1);

	
	}
	pthread_exit(NULL);
	
}

void *Consumer(void *arg)
{
	int i;
	int* lock = (int*) arg;
	while(1){
	
		acquire_lock(lock);
		printf("Consumer is in Non Critical Section!\n");
		sleep(1);
		
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
		release_lock(lock);
		sleep(1);
	
	}
	pthread_exit(NULL);
}
  
int main(void){

	long int i;
	
	for(i=0;i<size;i++){
		buf[i]=-1;
	}
	
	int* lock = new_lock();
	
	pthread_t tid[2],tid1[2];
   	
   	for(i=0;i<2;i++){
   		pthread_create(&tid, NULL, Producer,lock);
        	pthread_create(&tid1, NULL, Consumer,lock);
        }
	
	for(i=0;i<2;i++){
		pthread_join(tid,NULL);
		pthread_join(tid1,NULL);
	}

        pthread_exit(NULL);

        
}
