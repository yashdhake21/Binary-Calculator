/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/

#ifndef adtnum
#define adtnum

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len,sign;
}number;



#endif

