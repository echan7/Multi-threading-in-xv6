
#include "types.h"
#include "user.h"



void spin_init(struct spinlock* lk)
{
	lk->flag = 0;
}

void spin_lock(struct spinlock* lk){
	while(xchg(&lk->flag, 1) != 0);
}

void spin_unlock(struct spinlock* lk){
	lk->flag = 0;
}

