#include "types.h"
#include "user.h"
#include "x86.h"


void mutex_init(struct mutex* mtx)
{
	mtx->locked = 0;
	mtx->guard = 0;
	//mtx->listHead = (struct threadPid*)malloc(sizeof(struct threadPid)); 
	
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
	
	if(mtx->locked == 0){
	    mtx->locked= 1;
	    mtx->guard = 0;
	}else{
	  
	   setpark();
	   push(mtx);
	  // mtx->isEmpty += 1;
	   mtx->guard =0;
           park();
	}	    
}

void mutex_unlock(struct mutex* mtx)
{	
       
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
	
	int pid = pop(mtx);
	if(pid < 0){
	        
		mtx->locked = 0;
	}else{
	 	unpark(pid);
	}
	mtx->guard = 0;
	
}


void push(struct mutex* addMutex){

   
    // Allocate memory for node
    struct threadPid* new_node = (struct threadPid*)malloc(sizeof(struct threadPid));
    new_node->pid  = getpid();
    new_node->next = addMutex->listHead;
    addMutex->listHead = new_node;
   
}

int pop(struct mutex* popMutex)
{
	

    if((popMutex -> listHead)==NULL)
    {
        return -1;
    }
    
    else if((popMutex->listHead->next)==NULL)
    {
      
        int pid = (int)(popMutex->listHead->pid);
        free(popMutex->listHead);
        popMutex -> listHead = NULL;
     
        return pid;
    }
    
    else
    {
       

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
