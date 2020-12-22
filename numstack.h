/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/

#include<stdio.h>
#include "adtnum.h"

// Stack stores number list

typedef struct inode {
	number *a;
	struct inode *p;
}inode;


typedef inode *istack;
void iinit(istack *s);
void ipush(istack *s, number *a);
number *ipop(istack *s);
int iisempty(istack *s);

