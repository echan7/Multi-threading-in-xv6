
#include "types.h"
#include "user.h"

void cv_init(struct condvar* cv)
{
}

void cv_wait(struct condvar* cv, struct mutex* mtx)
{
        printf(1, "calling cv_wait pid : %d\n", getpid());
	if(mtx->locked == 0){
         return; 
	}
       
	pushCv(cv);
	setpark();
	printf(1, "trying to unlock\n");
	if(mtx->locked != 0 && cv->listHead != NULL) {
		mutex_unlock(mtx);
	}
	printf(1, "gave up lock\n");
	park();
	mutex_lock(mtx);
}

void cv_signal(struct condvar* cv)
{
	 printf(1, "calling cv_signal pid : %d\n", getpid());

	int nextOnList = popCv(cv);
	if(nextOnList == -1)
	{

	    return;
	}
	printf(1, "next on list is : %d\n", nextOnList);
	unpark(nextOnList);
}

void cv_broadcast(struct condvar* cv)
{
        printf(1, "calling cv_broadcast pid : %d\n", getpid());
	int i;
	while(i>=0){
	i = popCv(cv);
         if(i>=0){
		unpark(i);
	  }else{
	  	  printf(1, "pop returned weird... pid : %d\n", getpid());
	  }
	  
	}
}

void pushCv(struct condvar* addCv){
	
    // Allocate memory for node
    struct cvNode* new_node = (struct cvNode*)malloc(sizeof(struct cvNode));
    new_node->pid  = getpid();
    new_node->next = addCv->listHead;
    addCv->listHead = new_node;
    printf(1,"pushed cv to list %d\n", new_node->pid);
}

int popCv(struct condvar* popCv)
{
    if(!(popCv -> listHead))
    {
        return -1;
    }
    
    else if(!(popCv->listHead->next))
    {
       printf(1, "if stmt in pop\n");
        int pid = (int)(popCv->listHead->pid);
        free(popCv->listHead);
        popCv -> listHead = NULL;
        printf(1, "returning pid %d\n");
        return pid;
    }
    
    else
    {
       printf(1, "in pop else\n");
        struct cvNode *temp = popCv -> listHead;
        struct cvNode *tempNext = temp -> next;
        
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
