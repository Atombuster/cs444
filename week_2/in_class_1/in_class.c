#include <pthread.h>
#include <stdio.h>
#define THREAD_COUNT 10
#define ARRAY_COUNT 100000

struct thread_info {
    char *hello;
    char *goodbye;
    int id;
};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

int global_array[ARRAY_COUNT];

void *run(void *arg) {
    struct thread_info *thread_info = (struct thread_info*) arg;
    printf("child[%i]: %s\n", thread_info->id, thread_info->hello);
    int thread_offset = thread_info->id;
    pthread_mutex_lock(&lock);
    for (int j = 0; j < 10; j++) {
        thread_offset += j;
        thread_offset %= 10;
        for (int i = 0; i < 10000; i++) {
            int offset = i * 10;
            int array_place = offset + thread_offset;
            //pthread_mutex_lock(&lock2);
            global_array[array_place] += 1;
            //pthread_mutex_unlock(&lock2);

        }
    }
    pthread_mutex_unlock(&lock);
    printf("child[%i]: %s\n", thread_info->id,  thread_info->goodbye);
    return 0;
}

int main(void)
{
    struct thread_info thread_info[THREAD_COUNT];

    
    printf("parent: hello!\n");
    pthread_t thread_id[THREAD_COUNT];

    
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_info[i].goodbye = "Have a nice day.";
        thread_info[i].hello = "Hello there!";
        thread_info[i].id = i;
        pthread_create(&thread_id[i], NULL, run, &thread_info[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread_id[i], NULL);
    }

    for (int i = 0; i < ARRAY_COUNT; i++) {
        if (global_array[i] != 10) {
           printf("global_array[%i] = %i, should be 10\n", i, global_array[i]); 
        }
    }

    printf("parent: goodbye\n");

    return 0;
}

