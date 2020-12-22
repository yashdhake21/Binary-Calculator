/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/

#include<stdlib.h>
#include"numstack.h"

// Stack implementation to store number list.

void iinit(istack *s) { /*Initialising istack pointer to null */
	*s = NULL;
}
void ipush (istack *s, number *t) { /*Pushes elements into stack*/
	istack temp;
	temp = (inode *)malloc(sizeof(inode));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}
number *ipop(istack *s) {   /*Pops element from stack*/
	number *t;
	istack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}
int iisempty (istack *s) {  /*Condition check to check if stack is empty*/
	return *s == NULL;
}
