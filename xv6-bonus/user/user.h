#ifndef _USER_H_
#define _USER_H_
#include "mutex.h"
#include "condvar.h"
#include "semaphore.h"
#include "spinlock.h"
#include "threads.h"
#include "x86.h"


struct stat;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int clone(void *ustack);
int join(void **ustack);
void park(void);
int setpark(void);
int unpark(int pid);

// user library functions (ulib.c)
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int thread_create(void (*fn)(void*), void* arg);
int thread_join(void);
void spin_init(struct spinlock* lk);
void spin_lock(struct spinlock* lk);
void spin_unlock(struct spinlock* lk);

#endif // _USER_H_

