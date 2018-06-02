
#include "types.h"
#include "user.h"

void sem_init(struct semaphore* sem, int initval)
{
	sem->value = initval;
	cv_init(&sem->cv);
	mutex_init(&sem->mtx);

}

void sem_wait(struct semaphore* sem)
{


	mutex_lock(&sem->mtx);
	if(sem->value <= 0){
           cv_wait(&sem->cv, &sem->mtx);
	}
	sem->value--;
	mutex_unlock(&sem->mtx);
	
}

void sem_post(struct semaphore* sem)
{
	
	 // if there are more than one thread waiting, wake one uu
	 mutex_lock(&sem->mtx);
	 sem->value++;
	 cv_signal(&sem->cv);
	 mutex_unlock(&sem->mtx);
	
}

