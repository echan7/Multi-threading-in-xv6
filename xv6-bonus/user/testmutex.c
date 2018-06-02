#include "types.h"
#include "stat.h"
#include "user.h"

int status = 0;
struct mutex lk;
void f(void *arg){
        printf(1,"thread created with pid : %d\n", getpid());
	mutex_lock(&lk);
	printf(1,"woke up\n");
	int i;
	for(i =0; i < 20; i++){
		int tmp =status;
		sleep(1);
		status = tmp +1;
	}	
	sleep(10);
	printf(1, "waking up from sleep to unlock\n");
	mutex_unlock(&lk);
	exit();
}

int main(){
	mutex_init(&lk);
	int i ;
	for(i= 0; i<20; i++){
	if( thread_create(&f,(void*)i) < 0){
		printf(2, "unable to clone\n");
	}
	}
	printf(1,"sleeping\n");
	//sleep(1000000);
	printf(1,"woke from sleep in MAIN!!!!!!!!!\n");
	
	// join
	 for(i= 0; i< 20; i++){
         //printf(1, "joining\n");
	 thread_join();
        }

	printf(1,"status = %d\n",status);
	exit();
}

