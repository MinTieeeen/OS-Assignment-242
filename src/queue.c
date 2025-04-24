#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <ctype.h>

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}


void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
        if (!proc || !q || q->size >= MAX_QUEUE_SIZE) return;

        #ifdef MLQ_SCHED
        proc->priority = proc->prio;
        #endif
        
        q->proc[q->size] = proc;
        q->size++;
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */

        // Bound check
        if (!q || empty(q)) return NULL;

        // Take highest proc out
        struct pcb_t * result;
        uint32_t min_prio = q->proc[0]->priority;
        int min_idx = 0;
        for(int i = 1; i < q->size; i++){
                if(q->proc[i]->priority < min_prio){
                        min_prio = q->proc[i]->priority;
                        min_idx = i;
                        break;
                }
        }
        result  = q->proc[min_idx];

        // Push all procs behind it forward
        q->size--;      
        for(int i = min_idx; i < q->size; i++){
                q->proc[i] = q->proc[i+1];
        }
        
        return result;
}