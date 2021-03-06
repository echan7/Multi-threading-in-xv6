#include "types.h"
#include "user.h"
#include "x86.h"


void mutex_init(struct mutex* mtx)
{
	mtx->locked = 0;
	
}



void mutex_lock(struct mutex* mtx)
{	

       /* if(mtx -> locked == 1)
            printf(1, "mtx calling lock when it has lock?\n");
      
	printf(1, "calling mutex_lock pid : %d\n", getpid());
	while(xchg(&mtx->locked, 1) != 0){
//	printf(1, "pid falling asleep %d\n", getpid());
        setpark();
	push(mtx);
	park();
	}*/
	while(xchg(&mtx->guard, 1) == 1)
	;
	printf(1, "calling mutex_lock pid : %d\n", getpid());
	if(mtx->locked == 0){
	    mtx->locked= 1;
	    mtx->guard = 0;
	}else{
	   printf(1, "pid falling asleep %d\n", getpid());
	   setpark();
	   push(mtx);
	  // mtx->isEmpty += 1;
	   mtx->guard =0;
           park();
	}	    
}

void mutex_unlock(struct mutex* mtx)
{	
        printf(1, "calling mutex_unlock\n");
/*	int nextOnList = pop(mtx);
	
	if(nextOnList == -1)
	{
	   // printf(1, "return\n");
	    mtx -> locked = 0;
	    return;
	}
	
	printf(1,"pid : %d used to call unpark\n", nextOnList);
	//int gg = 0;
	//gg = unpark(nextOnList);
	//if(gg<0){
	 //printf(1,"pid : %d used to call unpark FAILED\n", nextOnList);
	 //return;
	//}
	mtx->locked = 0;
	unpark(nextOnList);*/
	while(xchg(&mtx->guard, 1) == 1){
		;}
	printf(1, "before pop\n");
	int pid = pop(mtx);
	printf(1, "after pop\n");
	if(pid < 0){
	printf(1, "pop returned weird shit\n");
		mtx->locked = 0;
	}else{
	 	unpark(pid);
		//mtx->isEmpty -= 1;
	}
	mtx->guard = 0;
	
}


void push(struct mutex* addMutex){
	
    // Allocate memory for node
    struct threadPid* new_node = (struct threadPid*)malloc(sizeof(struct threadPid));
    new_node->pid  = getpid();
    new_node->next = addMutex->listHead;
    addMutex->listHead = new_node;
    printf(1,"pushed to list %d\n", new_node->pid);
}

int pop(struct mutex* popMutex)
{
	printf(1, "in pop\n");

    if(!(popMutex -> listHead))
    {
	
        return -1;
    }
    
    else if(!(popMutex->listHead->next))
    {
        printf(1, "if last in pop\n");
        int pid = (int)(popMutex->listHead->pid);
        free(popMutex->listHead);
        popMutex -> listHead = NULL;
        printf(1, "returning pid %d\n");
        return pid;
    }
    
    else
    {
        printf(1, "in pop else\n");
	// this is not null
        struct threadPid *temp = popMutex -> listHead;
        struct threadPid *tempNext = temp -> next;
        
        //go to end
        while(tempNext -> next)
        {
            temp = tempNext;
            tempNext = temp -> next;
        }
        
        int pid = (int)(tempNext -> pid);
        free(tempNext);
	printf(1, "after free\n");
        temp -> next = NULL;
        return pid;
    }
    //printf(1, "calling pop\n");
    //struct threadPid* traverse = popMutex->listHead;
    //struct threadPid* last;
    //int listlength = 1;
    //while (traverse != NULL)
    //{
      //  printf(1, "stuck in here this is the problem?\n");
        //traverse = traverse->next;
        //if(traverse!=NULL){
        //last = traverse;
        //listlength++;
    	//}
    //}
    
    //printf(1, "here?\n");

    // no nodes on queue
   //if(last == NULL){
     //return -1;
   //}
   //int pid = last -> pid;
   //free(last);
   //last = NULL;
   //printf(1,"listlength : %d\n", listlength);
   //return pid;     
    
}
