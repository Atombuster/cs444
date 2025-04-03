#include <pthread.h>
#include <stdio.h>
#define THREAD_COUNT 3

struct thread_info {
    char *hello;
    char *goodbye;
    int id;
};


void *run(void *arg) {
    struct thread_info *thread_info = (struct thread_info*) arg;
    printf("child[%i]: %s\n", thread_info->id, thread_info->hello);
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
        thread_info[i].id = i + 1;
        pthread_create(&thread_id[i], NULL, run, &thread_info[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread_id[i], NULL);
    }


    printf("parent: goodbye\n");

    return 0;
}

