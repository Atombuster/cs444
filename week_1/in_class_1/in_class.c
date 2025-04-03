#include <pthread.h>
#include <stdio.h>

void *run(void *arg) {
    printf("child: hello!\n");
    (void)arg;
    printf("child: goodbye\n");
    return 0;
}

int main(void)
{
    printf("parent: hello!\n");
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, run, NULL);

    pthread_join(thread_id, NULL);

    printf("parent: goodbye\n");

    return 0;
}

