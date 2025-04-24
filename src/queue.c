#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */

        /* A queue_t represents a ready queue
                * Processes in the same ready queue have the same priority.
                * First process is put into first slot
        */
        if (q->size >= MAX_QUEUE_SIZE) {
                perror("No queue slot available");
                return;
        }
        else {
                q->proc[q->size] = proc;
                q->size++;
        }
}
struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose priority is the highest
         * in the queue [q] and remember to remove it from q
         */
        // Bound check
        if (q->size == 0) {
                perror("No process in this queue");
                return NULL;
        }
        else {
        // take out the first proc in this queue
                struct pcb_t *result = q->proc[0];
                q->size--;
                for (int i=0; i<q->size; i++) {
                        q->proc[i] = q->proc[i+1];
                }
                return result;
        }
}