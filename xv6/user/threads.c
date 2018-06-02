
#include "types.h"
#include "user.h"
#include "fs.h"
#define PGSIZE 4096



int thread_create(void (*thfunc)(void*), void* arg)
{
	
	void *stack;
	stack = malloc(PGSIZE);
	
	/*if((uint)stack % PGSIZE)
		stack = stack + (PGSIZE - (uint)stack % PGSIZE);
*/
	int result = clone(thfunc,arg,stack);
	
	return result;	
}

int thread_join(void)
{
	void *stack;
	int result = join(&stack);	
	if(result<0){
		return -1;
	}
	free(stack);

	return result;	
}
