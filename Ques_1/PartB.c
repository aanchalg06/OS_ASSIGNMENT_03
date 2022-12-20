#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<unistd.h>

sem_t forks[5];
pthread_t philo[5];

void pick_fork(int nn){
    sem_wait(&forks[nn]);
    sem_wait(&forks[(nn+1)%5]); 
}
//lecture- process synchronization slide 11 in sec-B
//lecture- process synchronizatio slide 46 in sec-B



void rest_fork(int nn){
    sem_post(&forks[nn]);
    sem_post(&forks[(nn+1)%5]);
}

void * eatphilospher(void *n)
 {
    int nn= *(int *)n;
    pick_fork(nn);
    
      
    printf("Philosopher %d begins to eat\n",nn);
    sleep(3);
    printf("Philosopher %d has finished eating\n",nn);
    
    rest_fork(nn);
 }

int main(){         
    for(int i=0;i<5;i++){
        sem_init(&forks[i],0,1);
        sem_init(&forks[i],0,1);
    }
      
        
    
    
    for(int i=0;i<5;i++){

        pthread_create( &philo[i], NULL, eatphilospher, (void *) &i);
        
    }

    for(int i=0;i<5;i++){

        pthread_join( philo[i], NULL);
    }
 }
