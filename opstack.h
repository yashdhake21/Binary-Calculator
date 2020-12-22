/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/


#include<stdio.h>
#include "adtnum.h"


// Stack stores operator list

typedef struct cnode {
	char a;
	struct cnode *p;
}cnode;
typedef cnode *cstack;


void cinit(cstack *s);
void cpush(cstack *s, char t);
char cpop(cstack *s);
int cisempty(cstack *s);
