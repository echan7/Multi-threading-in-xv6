#include "types.h"
#include "stat.h"
#include "user.h"

 
struct spinlock lk;
int status = 0;

void f(void *arg)
{ 

  printf(1, "starting function fuck\n");
  spin_lock(&lk);

  int i;
  for(i = 0; i < 10; i++)
  {
      int tmp = status;
      //int j;
      sleep(1);
      //for(j=0; j<50; j++);
      status = tmp + 1;
  }

  spin_unlock(&lk);
  printf(1, "exiting fuk\n");
  exit();
}
 
int main()
{
  spin_init(&lk);
  int i; 
  for(i = 0; i < 20; i++)
  {
      if(thread_create(&f,(void*)i) < 0)
           printf(2, "clone failed");
  }

  for(i = 0; i < 21; i++)
  {
      if(thread_join() < 0){
	printf(2, "join failed");
	break;
	}
  }
 
  printf(1, "status = %d\n", status);


  exit();
}
