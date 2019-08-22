#include <stdio.h>
#include <stdlib.h>
#include "structures.h"



int main(){
/*
	List a = NULL;
	listInsert(123,0,&a);
	listInsert(1997,0,&a);
	listInsert(5,2,&a);
	listInsert(200,1,&a);
	listInsert(7,1,&a);
	listInsert(64,1,&a);
	listInsert(5720,1,&a);
	listInsert(1995,1,&a);
	listPrint(a);
	listRemove(2,&a);
	listPrint(a);
	printf("size=%lld\n", listSize(a));
	printf("a[5] = %lld\n",listGet(5,a));
	printf("a[9] = %lld\n",listGet(9,a));
	listClear(&a);
	listPrint(a);
*/
/*
	dList a = NULL;
	dlistInsert(56,12,&a);//invalid index, shouldn't change anything
	dlistInsert(1995,0,&a);
	dlistInsert(1997,0,&a);
	dlistInsert(5,2,&a);
	dlistInsert(200,3,&a);
	dlistInsert(7,2,&a);
	dlistInsert(64,3,&a);
	dlistInsert(5720,5,&a);
	dlistInsert(314,6,&a);
	dlistPrint(a);
	dlistRemove(2,&a);
	dlistRemove(100,&a);//invalid index test
	dlistPrint(a);
	printf("size=%lld\n", dlistSize(a));
	printf("a[5] = %lld\n",dlistGet(5,a));
	printf("a[9] = %lld\n",dlistGet(9,a));
	dlistPrint(a);
	dlistClear(&a);
	dlistPrint(a);
*/
/*
	Stack st;
	initStack(&st);
	stackPush(12,&st);
	stackPush(8,&st);
	stackPush(20,&st);
	stackPush(22,&st);
	stackPush(90,&st);
	stackPush(100,&st);
	stackPrint(st);
	printf("pop(st) = %lld\n",stackPop(&st));
	stackPrint(st);
	printf("size of stack = %lld\n", stackSize(st));
	printf("peek(st) = %lld\n",stackPeek(st));
	stackPrint(st);
	stackClear(&st);
	stackPrint(st);
*/
/*
	Queue q;
	initQueue(&q);
	queuePush(1,&q);
	queuePush(2,&q);
	queuePush(3,&q);
	queuePush(4,&q);
	queuePush(5,&q);
	queuePush(6,&q);
	queuePrint(q);
	printf("pop(q) = %lld\n", queuePop(&q));
	queuePrint(q);
	printf("size of queue = %lld\n", queueSize(q));
	printf("peek(q) = %lld\n", queuePeek(q));
	queueClear(&q);
	queuePrint(q);
*/

	Tree t = NULL;
	bstInsert(12,&t);
	bstInsert(120,&t);
	bstInsert(10,&t);
	bstInsert(11,&t);
	bstInsert(16,&t);
	bstInsert(22,&t);
	bstInsert(20,&t);
	bstInsert(5,&t);
	bstInsert(1,&t);
	bstInsert(15,&t);
	printf("Tree size = %d\n", btSize(t));
	printf("Tree height = %d\n", btHeight(t));
	printf("Tree has %d leaves\n",btLeaves(t));
	List L;
	L = NULL;
	printf("\nlevel order:\n");
	levelOrder(t,&L);
	listPrint(L);
	listReverse(&L);
	listPrint(L);
	List M = NULL;
	printf("\npre order:\n");
	preOrder(t,&M);
	listPrint(M);
	listReverse(&M);
	listPrint(M);
	printf("\npost order:\n");
	List N = NULL;
	postOrder(t,&N);
	listPrint(N);
	listReverse(&N);
	listPrint(N);
	printf("\nin order:\n");
	List P = NULL;
	inOrder(t,&P);
	listPrint(P);
	listReverse(&P);
	listPrint(P);





	return 0;
}


//stack, queue static implementation
//prefix & postfix expressions evaluation, transformation

