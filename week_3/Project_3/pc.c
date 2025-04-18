#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "eventbuf.h"


struct eventbuf *eb;


sem_t *mutex;
sem_t *items;
sem_t *spaces;

int events_per_producer = 0;
int p_done = 0;

// Grab the sem_open_temp() function and drop it here!
sem_t *sem_open_temp(const char *name, unsigned int value)
{
    sem_t *sem;

    // Create the semaphore
    if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
        return SEM_FAILED;

    // Unlink it so it will go away after this process exits
    if (sem_unlink(name) == -1) {
        sem_close(sem);
        return SEM_FAILED;
    }

    return sem;
}

void *run_p(void *arg)
{ 
    int *id = arg;
    for (int i = 0; i < events_per_producer; i++) {
        int event = (*id) * 100 + i;
        sem_wait(spaces);
        sem_wait(mutex);

            eventbuf_add(eb, event);
            printf("P%d: adding event %d\n", *id, event);

        sem_post(mutex);
        sem_post(items);
    }

    sem_wait(mutex);
        printf("P%d: exiting\n", *id);
    sem_post(mutex);

    return NULL;
 
}

void *run_c(void *arg)
{
    int *id = arg;

    
    while (!(p_done && eventbuf_empty(eb))) {
        sem_wait(items);
        sem_wait(mutex);
            if (!eventbuf_empty(eb)) { 
                int event = eventbuf_get(eb);
                printf("C%d: got event %d\n", *id, event);
            }
        sem_post(mutex);
        sem_post(spaces);
    }

    printf("C%d: exiting\n", *id);
    sem_post(mutex);


    return NULL;

}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        printf("Error wrong amount of inputs\nshould be\n./pc (Num Producers) (Num Consumers) (Max Gen Event) (Max Unused Events)\n");
        return 1;
    }
    eb = eventbuf_create();
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    events_per_producer = atoi(argv[3]);
    int max_event_to_have = atoi(argv[4]);
    mutex = sem_open_temp("mutex", 1);
    items = sem_open_temp("items", 0);
    spaces = sem_open_temp("spaces", max_event_to_have);

    //printf("%d\n%d\n%d\n%d\n", producers, consumers, max_event_to_have, events_per_producer);
    
    pthread_t runners_p[producers];
    int runner_id_p[producers];
    pthread_t runners_c[consumers];
    int runner_id_c[consumers];

    for (int i = 0; i < producers; i++) {
        runner_id_p[i] = i;
        pthread_create(runners_p + i, NULL, run_p, runner_id_p + i); 
    }
    for (int i = 0; i < consumers; i++) {
        runner_id_c[i] = i;
        pthread_create(runners_c + i, NULL, run_c, runner_id_c + i); 
    }
    for (int i = 0; i < producers; i++)
        pthread_join(runners_p[i], NULL);
    
    
    p_done = 1;
    for (int i = 0; i < consumers; i++) {
        sem_post(items); 
    }
    
    
    for (int i = 0; i < consumers; i++)
        pthread_join(runners_c[i], NULL);    


    sem_close(mutex);
    sem_close(items);
    sem_close(spaces);
    eventbuf_free(eb);

}
