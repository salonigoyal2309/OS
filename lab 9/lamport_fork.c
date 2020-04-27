#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int number = 2;
int ticket[2] = {0};
int flag[2] = {0};
int duration = 20000;

void unlock(int i) {
	ticket[i] = 0;
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
 
  
        int pid,i,j;
        if((pid=fork())<0)
                printf("fork error\n");
                
        else if(pid==0){
        
        	while(1){
	
			i= 0,j=0;
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
        
        else{
        
        	while(1){
	
			i=1,j=0;
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
        
        exit(0);
        
}

