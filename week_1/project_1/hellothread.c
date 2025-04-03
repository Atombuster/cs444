#include <pthread.h>
#include <stdio.h>
#define THREAD_COUNT 2
#define ARRAY_COUNT 100000

struct thread_info {
    int id;
};

int global_array[ARRAY_COUNT];

void *run(void *arg) {
    struct thread_info *thread_info = (struct thread_info*) arg;
    for (int i = 0; i < 5; i++) {
        printf("thread %i: %i\n", thread_info->id, i);
    }
    return 0;
}

int main(void)
{
    struct thread_info thread_info[THREAD_COUNT];

    
    printf("Launching threads\n");
    pthread_t thread_id[THREAD_COUNT];

    
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_info[i].id = i + 1;
        pthread_create(&thread_id[i], NULL, run, &thread_info[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread_id[i], NULL);
    }

    printf("Threads complete!\n");

    return 0;
}

