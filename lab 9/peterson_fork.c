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
			favouredthread=2;
			printf("Process 1 is in Non Critical Section!\n");
			sleep(1);
			thread1wantstoenter=1;
			while(thread2wantstoenter==1 && favouredthread==2){
		
				printf("Process 1 is waiting for entering in Critical Section!\n");
				sleep(1);
			
			}
			printf("Now Process 1 is in Critical Section!\n");
			for(i=0;i<2;i++) printf("Child\n");
		
			printf("Finally Process 1 is out of Critical Section!\n");
			sleep(1);
			thread1wantstoenter=0;
	
		}
    		
    	}
        
        else{
        
  			while(1){
	
				favouredthread=1;
				printf("Process 2 is in Non Critical Section!\n");
				sleep(1);
				thread2wantstoenter=1;
				while(thread1wantstoenter==1 && favouredthread==1){
		
					printf("Process 2 is waiting for entering in Critical Section!\n");
					sleep(1);
			
				}
				
				printf("Now Process 2 is in Critical Section!\n");
				for(i=0;i<2;i++) printf("Process 2\n");
		
				printf("Finally Process 2 is out of Critical Section!\n");
				sleep(1);
				thread2wantstoenter=0;
	
			}
                
        }
        
        exit(0);
        
}

