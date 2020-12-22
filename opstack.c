/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/

#include<stdlib.h>
#include"opstack.h"
//  Stack implementation to store character Operators.
void cinit(cstack *s) { //Initialising the stack to null
	*s = NULL;
}
void cpush (cstack *s, char t) { //Pushes elements into stack
	cstack temp;
	temp = (cnode *)malloc(sizeof(cnode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}
char cpop(cstack *s) {  //Pops element from stack
	char t;
	cstack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}
int cisempty (cstack *s) { //Condition check to check if stack is empty
	return *s == NULL;
}

char ctop(cstack *s) {  //Pops top value from stack and returns it
	char ch;
	ch = cpop(s);
	cpush(s, ch);
	return ch;
}


