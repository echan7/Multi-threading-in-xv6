
#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct spinlock{
	uint flag;
}spinlock;


void spin_init(struct spinlock* lk);
void spin_lock(struct spinlock *lk);
void spin_unlock(struct spinlock *lk);

#endif
