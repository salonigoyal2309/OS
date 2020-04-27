#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdbool.h> 
#define _BSD_SOURCE 
#include <sys/time.h> 
#define BSIZE 8 // Buffer size 
#define PWT 2 // Producer wait time limit 
#define CWT 10 // Consumer wait time limit 
#define RT 10 // Program run-time in seconds 
  
int shmid1, shmid2, shmid3, shmid4; 
key_t k1 = 5491, k2 = 5812, k3 = 4327, k4 = 3213; 
bool* SHM1; 
int* SHM2; 
int* SHM3; 
int *lock;


int acquire_lock(int* lock){
        int val = 0;
        do{
                __asm__("xchg %1, %0" : "+q" (val), "+m" (*lock));
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
  
int main() 
{ 
    //shmid1 = shmget(k1, sizeof(bool) * 2, IPC_CREAT | 0660); // flag 
    //shmid2 = shmget(k2, sizeof(int) * 1, IPC_CREAT | 0660); // turn 
    shmid2 = (shmget(k2, sizeof(int) * 1, IPC_CREAT | 0660));
    shmid3 = shmget(k3, sizeof(int) * BSIZE, IPC_CREAT | 0660); // buffer 
    shmid4 = shmget(k4, sizeof(int) * 1, IPC_CREAT | 0660); // time stamp 
    
  
    if (shmid2<0||shmid3 < 0 || shmid4 < 0){ 
        perror("Main shmget error: "); 
        exit(1); 
    } 
    
    SHM3 = (int*)shmat(shmid3, NULL, 0); 
    int ix = 0; 
    while (ix < BSIZE) // Initializing buffer 
        SHM3[ix++] = 0;
       
    lock = (int *)shmat(shmid2, NULL,0);
    lock = 0; 
  
    struct timeval t; 
    time_t t1, t2; 
    gettimeofday(&t, NULL); 
    t1 = t.tv_sec; 
  
    int* state = (int*)shmat(shmid4, NULL, 0); 
    *state = 1; 
    int wait_time; 
  
    int i = 0; // Consumer 
    int j = 1; // Producer 
        
	lock = (int *)shmat(shmid2,NULL,0);
        SHM3 = (int*)shmat(shmid3, NULL, 0); 
        
        if (SHM3 == (int*)-1) { 
            perror("Producer shmat error: "); 
            exit(1); 
        } 
  
        //bool* flag = SHM1; 
        //int* turn = SHM2; 
        int* buf = SHM3; 
        int index = 0; 
  
        while (*state == 1) { 
            //flag[j] = true; 

            printf("Producer is ready now.\n\n");
            acquire_lock(lock); 
            //*turn = i; 
  
            // Critical Section Begin 
            index = 0; 
            while (index < BSIZE) { 
                if (buf[index] == 0) { 
                    int tempo = myrand(BSIZE * 3); 
                    printf("Job %d has been produced\n", tempo); 
                    buf[index] = tempo; 
                    break; 
                } 
                index++; 
            } 
            if (index == BSIZE) 
                printf("Buffer is full, nothing can be produced!!!\n"); 
            printf("Buffer: "); 
            index = 0; 
            while (index < BSIZE) 
                printf("%d ", buf[index++]); 
            printf("\n"); 
            // Critical Section End 
  
            //flag[j] = false; 
            if (*state == 0) 
                break; 
            wait_time = myrand(PWT); 
            printf("Producer will wait for %d seconds\n\n", wait_time); 
            sleep(wait_time); 
            
            release_lock(lock);
        
        } 
  
  
   // Parent process will now for RT seconds before causing child to terminate 
    while (1) { 
        gettimeofday(&t, NULL); 
        t2 = t.tv_sec; 
        if (t2 - t1 > RT) // Program will exit after RT seconds 
        { 
            *state = 0; 
            break; 
        } 
    } 
  
    printf("The clock ran out.\n"); 
    return 0; 
} 
