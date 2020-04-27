#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define size 2

sem_t searchers,searchMutex,inserters,insertMutex,insertCriticalSection,deleters;
int n_searchers=0,n_inserters=0;
  
void *Searchers(void *arg){

	while(1){
	
	sem_wait(&searchMutex);
	n_searchers++;
	if(n_searchers==1) sem_wait(&searchers);
	sem_post(&searchMutex);
	sleep(1);
	printf("Entered Searchers critical section\n");
	sleep(1);
	printf("Searching....\n");
	sleep(1);
	printf("Exiting Searchers critical section\n");
	sleep(1);
	sem_wait(&searchMutex);
	n_searchers--;
	if(n_searchers==0) sem_post(&searchers);
	sem_post(&searchMutex);
	
	}

	
}

void *Inserters(void *arg){

	while(1){
	
	sem_wait(&insertMutex);
	n_inserters++;
	if(n_inserters==1) sem_wait(&inserters);
	sem_post(&insertMutex);
	sem_wait(&insertCriticalSection);
	sleep(1);
	printf("Entered Inserters critical section\n");
	sleep(1);
	printf("Inserting....\n");
	sleep(1);
	printf("Exiting Inserters critical section\n");
	sleep(1);
	sem_post(&insertCriticalSection);
	sem_wait(&insertMutex);
	n_inserters--;
	if(n_inserters==0) sem_post(&inserters);
	sem_post(&insertMutex);
	
	}

}

void *Deleters(void *arg){

	while(1){
	
	sem_wait(&searchers);
	sem_wait(&inserters);
	sem_wait(&deleters);
	sleep(1);
	printf("Entered Deleters critical section\n");
	sleep(1);
	printf("Deleting....\n");
	sleep(1);
	printf("Exiting Deleters critical section\n");
	sleep(1);
	sem_post(&deleters);
	sem_post(&inserters);
	sem_post(&searchers);
	
	}
	
}

  
int main(void){

	long int i;
	
	sem_init(&searchers,0,1);
	sem_init(&inserters,0,1);
	sem_init(&deleters,0,1);
	sem_init(&searchMutex,0,1);
	sem_init(&insertMutex,0,1);
	sem_init(&insertCriticalSection,0,1);
	
        pthread_t t1[size],t2[size],t3[size]; 
        for(i=0;i<size;i++){
   		pthread_create(&t1[i] , NULL, Searchers ,NULL);
        	pthread_create(&t2[i] , NULL, Inserters ,NULL);
        	pthread_create(&t3[i], NULL, Deleters ,NULL);
        }
        
        for(i=0;i<size;i++){
		pthread_join(t1[i],NULL);
		pthread_join(t2[i],NULL);
		pthread_join(t3[i],NULL);
	}
	
        pthread_exit(NULL);

        
}
