
#ifndef CONDVAR_H
#define CONDVAR_H

struct condvar {
  struct cvNode* listHead; 
  //struct mutex* mtx;
};

struct cvNode {
  int pid;
  struct cvNode * next;
};

void cv_init(struct condvar* cv);
void cv_wait(struct condvar* cv, struct mutex* mtx);
void cv_signal(struct condvar* cv);
void cv_broadcast(struct condvar* cv);
void pushCv(struct condvar* cv);
int popCv(struct condvar* cv);


#endif
