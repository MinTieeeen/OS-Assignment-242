/*
 * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Sierra release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

#include "common.h"
#include "syscall.h"
#include "stdio.h"
#include "libmem.h"

int __sys_killall(struct pcb_t *caller, struct sc_regs* regs)
{
    char proc_name[100];
    uint32_t data;

    //hardcode for demo only
    uint32_t memrg = regs->a1;
    
    /* TODO: Get name of the target proc */
    //proc_name = libread..
    int i = 0;
    data = 0;
    while(data != -1){
        libread(caller, memrg, i, &data);
        proc_name[i]= data;
        if(data == -1) proc_name[i]='\0';
        i++;
    }
    printf("The procname retrieved from memregionid %d is \"%s\"\n", memrg, proc_name);

    /* TODO: Traverse proclist to terminate the proc
     *       stcmp to check the process match proc_name
     */
    //caller->running_list
    //caller->mlq_ready_queu
    int running_size = caller->running_list->size;
    struct pcb_t *cur_proc, *swap_temp;
    for (int j=0; j<running_size; j++) {
        cur_proc = caller->running_list->proc[j];
        if (strcmp(cur_proc->path, proc_name) == 0) {
            // free this proc, then push all later proc forward
            
            // free this proc's memory
            for (int k=0; k<PAGING_MAX_SYMTBL_SZ; k++) {
                while (cur_proc->mm->symrgtbl[k].rg_next != NULL) {
                    libfree(caller, k);
                }
            }
            // now shift all procs forward
            for (int k=j; k<running_size-1; k++) {
                caller->running_list->proc[k] = caller->running_list->proc[k+1];
            }
            // and pop the redundant proc out
            --caller->running_list->size;
        }
    }
    /* TODO Maching and terminating 
     *       all processes with given
     *        name in var proc_name
     */

    return 0; 
}
