#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

 int number = 15;
 int ticket[10] = {0};
 int flag[10] = {0};
 int duration = 20000;
 
 
void unlock(int i) {
	ticket[i] = 0;
}


void * Thread(void * id) {
	
	while(1){
	
	int i= id,j=0;
	lock(i);
	printf("Critical section of %d\n", i+1);
	for(j=0;j<2;j++){
		printf("Process %d \n",i+1);
	}
	sleep(1);
	unlock(i);
	printf("Non critical section of %d \n", i+1);
	sleep(1);
	}
	
}


int high(){
	
	int i = 0;	
	int j = 0;
	int highvalue = 0;
	for(i = 0; i < 10; i++){
		if ((ticket[i]) > highvalue)
		{
		highvalue = ticket[i];
		}
	}
	return highvalue;
}


void lock(int i){

	int j;
	flag[i] = 1;
	ticket[i] = 1 + high();
	flag[i] = 0;
	for (j = 1; j <= number; j++){
		while (flag[j]){
			;
		} 
		while ((ticket[j] != 0) &&((ticket[j] < ticket[i]) ||((ticket[j] == ticket[i]) && (j < i)))){ 
			;
		}
	}

}

int main(){

	pthread_t threads[number];
	int t;
	
	for(t = 0; t < number; t++){
		pthread_create(&threads[t], NULL, &Thread, (void *)t);
	}
	
	for(t = 0; t < number; t++){
		pthread_join(threads[t], NULL);
	}
	
	return 0;

}

    
