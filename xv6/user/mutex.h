
#ifndef MUTEX_H
#define MUTEX_H

struct mutex {

  uint locked;
  uint guard;  
  struct threadPid* listHead; 
 
};

struct threadPid {
  int pid;
  uint head; 
  struct threadPid * next;
};

void mutex_init(struct mutex* mtx);
void mutex_lock(struct mutex* mtx);
void mutex_unlock(struct mutex* mtx);
void push(struct mutex* mtx);
int pop(struct mutex* mtx);


#endif
