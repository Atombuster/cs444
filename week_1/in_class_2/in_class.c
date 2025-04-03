#include <pthread.h>
#include <stdio.h>

void *run(void *arg) {
    char **greet = arg;
    printf("child: %s\n", greet[0]);
    printf("child: %s\n",  greet[1]);
    return 0;
}

int main(void)
{
    printf("parent: hello!\n");
    pthread_t thread_id;
    char hello[] = "Hello there!";
    char goodbye[] = "Have a nice day.";

    char *mygreatings[] = {hello, goodbye};

    pthread_create(&thread_id, NULL, run, (void *)mygreatings);

    pthread_join(thread_id, NULL);

    printf("parent: goodbye\n");

    return 0;
}

