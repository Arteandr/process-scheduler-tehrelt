#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/tools.h"
#include <stdio.h>
#include <stdlib.h>

int processes_count = 0;

scheduler_t *init_scheduler() {
  // printf("Allocating memory for scheduler_t\n");
  scheduler_t *sch = (scheduler_t *)malloc(sizeof(scheduler_t));

  // printf("Initializing queue in schedulers\n");
  sch->queues_q = init_queue();
  sch->processes_q = init_queue();
  return sch;
}

int total_burst(scheduler_t *s) {
  node_t *p = s->processes_q->head;
  int total = 0;

  while (p != 0) {
    total += ((process_t *)p->item)->burst;
    p = p->next;
  }

  return total;
}

void generate_processes(scheduler_t *s, int count) {
  for (int i = 0; i < count; ++i) {
    process_t *proc = process_create(processes_count++);
    proc->burst = rand_int(1, 10);
    printf("generated process: %d\tburst: %d\n", proc->pid, proc->burst);
    proc->priority = 0;
    proc->status = READY;
    enqueue(s->processes_q, (void **)&proc);
  }
}
