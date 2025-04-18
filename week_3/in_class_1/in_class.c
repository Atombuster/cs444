#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
int global = 0;


void *run_1(void *arg) {
    (void)arg;
    pthread_mutex_lock(&lock);    
    while (global != 3) {
        pthread_cond_wait(&condvar, &lock);
    }
    printf("Half way there!\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *run_2(void *arg) {
    (void)arg;
    pthread_mutex_lock(&lock);    
    while (global != 0) {
        pthread_cond_wait(&condvar, &lock);
    }
    printf("Liftoff!\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

    int main(void)
{

    global = 6;
    pthread_t thread_id_1;

    pthread_t thread_id_2;

    pthread_create(&thread_id_1, NULL, run_1, NULL);

    pthread_create(&thread_id_2, NULL, run_2, NULL);
    while(global != 0) {
        global--;  
        printf("%i\n", global);
        pthread_cond_broadcast(&condvar);
        sleep(1);
        
    }

    
    
    pthread_join(thread_id_1, NULL);

    pthread_join(thread_id_2, NULL);


}