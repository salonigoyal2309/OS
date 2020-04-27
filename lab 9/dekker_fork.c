#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(){

	int favouredthread = 1; 
	int thread1wantstoenter = 0; 
	int thread2wantstoenter = 0; 
  
        int pid,i;
        if((pid=fork())<0)
                printf("fork error\n");
        else if(pid==0){
        
        	while(1){
        
        		printf("Process 1 is in non critical section \n");
        		thread1wantstoenter = 1; 
        		while (thread2wantstoenter == 1) { 
  
            			if (favouredthread == 2) { 
  
                		thread1wantstoenter = 0; 
                		while (favouredthread == 2){
                			printf("process 1 is waiting for cs\n");
                			sleep(1);
                		}
  				thread1wantstoenter = 1; 
           			
           			} 
        		} 
        		
  			printf("process 1 is in critical section\n");
  			for(i=0;i<2;i++) printf("child\n");
  
        		favouredthread = 2; 
        		
        		printf("process 1 is out of critical section \n");
        		sleep(1);
        		
        		thread1wantstoenter = 0; 
        		
        	}

    		
    	}
        
        else{
        
        	while(1){
  			printf("Process 2 is in non critical section\n");
        		thread2wantstoenter = 1; 
        		while (thread1wantstoenter == 1) { 
  
            			if (favouredthread == 1) { 
  
                		thread2wantstoenter = 0; 
                		while (favouredthread == 1){ 
                			printf("process 2 is waiting for cs\n");
                			sleep(1);
                		}
  				thread2wantstoenter = 1; 
           			
           			} 
        		} 
        		
  			printf("process 2 is in critical section\n");
  			for(i=0;i<2;i++) printf("parent\n");
  
        		favouredthread = 1; 
        		
        		printf("process 2 is out of critical section\n");
        		sleep(1);
        		
        		thread2wantstoenter = 0; 
        		
        	}
    		
                
        }
        exit(0);
        
}

