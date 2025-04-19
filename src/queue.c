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
         * Last process is put into first slot
         */
        for (int i=q->size; i>0; i--) {
                q->proc[i] = q->proc[i-1];
        }
        q->proc[0] = proc;
        q->size++;
        // what to do if there's no more space?
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose priority is the highest
         * in the queue [q] and remember to remove it from q
         */
        
        // First process is in last slot (to take out easier)
        q->size--;
        return q->proc[q->size+1];
}

