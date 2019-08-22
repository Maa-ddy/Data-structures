#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "structures.h"


long long max(long long a, long long b){ return a>b?a:b; }


//Linked Lists functions:
//_______________________________________________________________________________

void listInsert(long long element, long long position, List* L){
	if (position == 0){
		Node* elt = (Node*)malloc(sizeof(Node));
		elt->data = element;
		elt->next = *L;
		*L = elt;
		return;
	}
	if (emptyList(*L)){ return; }
	Node* temp = *L;
	for (long long k = 0; k<position-1; k++){
		temp = temp->next;
		if (temp == NULL){ return; } //invalid position
	}
	Node* elt = (Node*)malloc(sizeof(Node));
	elt->data = element;
	elt->next = temp->next;
	temp->next = elt;
}

void listRemove(long long position, List* L){
	if (*L == NULL){ return; } //empty List
	Node* temp = *L;
	if (position == 0){
		*L = temp->next;
		free(temp);
		temp = NULL;
		return;
	}
	for (long long k = 0; k<position-1; k++){
		temp = temp->next;
		if (temp->next == NULL){ return; }//invalid position
	}
	Node* temp2 = temp->next;
	temp->next = temp2->next;
	free(temp2);
	temp2 = NULL;
}

long long listSize(List L){
	long long rez = 0;
	while(L != NULL){
		L = L->next;
		rez++;
	}
	return rez;
}

void listClear(List* L){
	while(!emptyList(*L)){
		listRemove(0,L);
	}
}

long long  listGet(long long position, List L){
	if (emptyList(L)){
		printf("empty List, returned -1\n");
		return -1;
	}
	for (long long k = 0; k<position; k++){
		L = L->next;
		if (L == NULL){
			printf("invalid index, returned -1\n");
			return -1;
		}
	}
	return L->data;
}

void listPrint(List L){
	printf("[");
	while (L != NULL){
		if (L->next == NULL){ printf("%lld",L->data); }
		else { printf("%lld, ",L->data); }
		L = L->next;
	}
	printf("]\n");
}

long long emptyList(List L){
	return L == NULL;
}

Node* listReverseUtil(List head){
	if (head == NULL){ return NULL; }
	if (head->next == NULL){ return head; }
	Node* tail = listReverseUtil(head->next);
	head->next->next = head;
	head->next = NULL;
	return tail;
}
void listReverse(List* L){
	*L = listReverseUtil(*L);
}





//doubly Linked Lists functions:
//_______________________________________________________________________________

void dlistInsert(long long element, long long position, dList* L){
	if (position == 0){
		dNode* elt = (dNode*)malloc(sizeof(dNode));
		elt->data = element;
		elt->next = *L;
		elt->previous = NULL;
		*L = elt;
		return;
	}
	if (emptydList(*L)){ return; }
	dNode* temp = *L;
	for (long long k = 0; k<position-1; k++){
		temp = temp->next;
		if (temp == NULL){ return; }//invalid index
	}
	dNode* elt = (dNode*)malloc(sizeof(dNode));
	elt->data = element;
	elt->next = temp->next;
	elt->previous = temp;
	if(elt->next != NULL){ (elt->next)->previous = elt; }
	temp->next = elt;
}


void dlistRemove(long long position, dList* L){
	if (emptydList(*L)){ return; }
	dNode* temp = *L;
	if (position == 0){
		*L = temp->next;
		if (*L != NULL){ (*L)->previous = NULL; }
		free(temp);
		temp = NULL;
		return;
	}
	for (long long k = 0; k<position; k++){
		temp = temp->next;
		if (temp == NULL){ return; }//invalid index
	}
	(temp->previous)->next = temp->next;
	if (temp->next != NULL){ (temp->next)->previous = temp->previous; }
	free(temp);
	temp = NULL;
}


long long  dlistSize(dList L){
	long long rez = 0;
	while (L!=NULL){
		rez++;
		L = L->next;
	}
	return rez;
}


void dlistClear(dList* L){
	while (!emptydList(*L)){
		dlistRemove(0,L);
	}
}


long long  dlistGet(long long position, dList L){
	if (emptydList(L)){ 
		printf("empty List, returned -1\n");
		return -1;
	}
	for (long long k = 0; k<position; k++){
		L = L->next;
		if (L == NULL){
			printf("invalid index, returned -1\n");
			return -1;
		}
	}
	return L->data;
}

void dlistPrint(dList L){
	printf("[");
	while (L != NULL){
		if (L->next == NULL){ printf("%lld",L->data); }
		else { printf("%lld, ",L->data); }
		L = L->next;
	}
	printf("]\n");
}

long long emptydList(dList L){
	return L == NULL;
}


//Stack functions:
//_______________________________________________________________________________


void stackPush(long long element, Stack* St){
	//could've been simply:
	//listInsert(element,0,&(St->head));
	Node* elt = (Node*)malloc(sizeof(Node));
	elt->data = element;
	elt->next = St->head;
	St->head = elt;
}

long long  stackPop(Stack* St){
/*
	long long rez = listGet(0,St->head);
	listRemove(0,&(St->head));
	return rez;
*/
	if (St->head == NULL){
		printf("empty stack, returned -1\n");
		return -1;
	}
	Node* temp = St->head;
	St->head = temp->next;
	long long rez = temp->data;
	free(temp);
	temp = NULL;
	return rez;
	
}

long long  stackSize(Stack St){
	return listSize(St.head);
}

void stackClear(Stack* St){
	listClear(&(St->head));
}

void stackPrint(Stack St){
	listPrint(St.head);
}

long long  stackPeek(Stack St){
	//return listGet(0,St.head);
	if (emptyStack(St)){
		printf("empty stack, returned -1\n");
		return -1;
	}
	return St.head->data;
}

long long  emptyStack(Stack St){
	return St.head == NULL;
}

void initStack(Stack* St){
	St->head = NULL;
}


//Queue functions:
//_______________________________________________________________________________


void queuePush(long long element, Queue* Qu){
	Node* elt = (Node*)malloc(sizeof(Node));
	elt->data = element;
	elt->next = NULL;
	if (emptyQueue(*Qu)){
		Qu->head = Qu->tail = elt;
		return;
	}
	(Qu->tail)->next = elt;
	Qu->tail = elt;
}

long long  queuePop(Queue* Qu){
	if (emptyQueue(*Qu)){
		printf("empty queue, returned -1\n");
		return -1;
	}
	Node* temp = Qu->head;
	Qu->head = (Qu->head)->next;
	if (Qu->head == NULL){ Qu->tail = NULL; }
	long long rez = temp->data;
	free(temp);
	temp = NULL;
	return rez;
}

long long  queueSize(Queue Qu){
	return listSize(Qu.head);
}

void queueClear(Queue* Qu){
	listClear(&(Qu->head));
	Qu->tail = NULL;
}

void queuePrint(Queue Qu){
	listPrint(Qu.head);
}

long long  queuePeek(Queue Qu){
	if (emptyQueue(Qu)){
		printf("empty queue, returned -1\n");
		return -1;
	}
	return Qu.head->data;
}

long long  emptyQueue(Queue Qu){
	return Qu.head == NULL;
}

void initQueue(Queue* Qu){
	Qu->head = Qu->tail = NULL;
}



//Tree functions:
//_______________________________________________________________________________

void bstInsert(long long element, Tree* root){
	if (*root == NULL){
		tNode* elt = (tNode*)malloc(sizeof(tNode));
		elt->data = element;
		elt->left = elt->right = NULL;
		*root = elt;
		return;
	}
	if (element <= (*root)->data){
		bstInsert(element,&(*root)->left);
	}
	else{
		bstInsert(element,&(*root)->right);
	}
}

int bstContains(long long element, Tree root){
// O(log(n))
	if (root == NULL){
		return 0;
	}
	if (root->data == element){
		return 1;
	}
	if (element < root->data){
		return bstContains(element, root->left);
	}
	else{
		return bstContains(element, root->right);
	}
}
	
long long isBSTutil(Tree root, long long l, long long r){ //*w*
// O(n)
	if (root == NULL){
		return 1;
	}
	if (root->data < l || root->data > r){
		return 0;
	}
	return isBSTutil(root->left, l,root->data) && isBSTutil(root->right, root->data, r);
}

	
int isBST(Tree root){
// O(n)
	return isBSTutil(root, INT_MIN,INT_MAX);
}

long long bstMin(Tree root){
// O(log(n)) if balanced
	if (root->left == NULL){ return root->data; }
	return bstMin(root->left);
}

long long bstMax(Tree root){
// O(log(n)) if balanced
	if (root->right == NULL){ return root->data; }
	return bstMax(root->right);
}

int btHeight(Tree root){
// O(n)
	if(root == NULL){ return -1; }
	return 1 + max(btHeight(root->left),btHeight(root->right));
}

int btSize(Tree root){
// O(n)
	if (root == NULL){ return 0; }
	return 1 + btSize(root->left) + btSize(root->right);
}

void levelOrder(Tree root, List* L){ //**
// O(n)
	if (root == NULL){ return; }
	Queue q;
	initQueue(&q);
	queuePush((long long)root, &q); //push the root @ to the queue
	tNode* tempPtr;
	while (!emptyQueue(q)){
		tempPtr = (tNode*)queuePop(&q); //current tree node @
		printf("%lld\t",tempPtr->data); //print current tree node data
		listInsert(tempPtr->data,0,L); //insert data in the list that will contain the traversal, (in reversed order for effinciency)
		if (tempPtr->left != NULL){ queuePush((long long)(tempPtr->left),&q); }
		if (tempPtr->right != NULL){ queuePush((long long)(tempPtr->right),&q); }
	}
	printf("\n");
}

void preOrder(Tree root,List* L){
// O(n)
	if (root == NULL){ return; }
	printf("%lld\t",root->data);
	listInsert(root->data,0,L);
	preOrder(root->left,L);
	preOrder(root->right,L);
}

void postOrder(Tree root, List* L){
// O(n)
	if (root == NULL){ return; }
	postOrder(root->left,L);
	postOrder(root->right,L);
	printf("%lld\t",root->data);
	listInsert(root->data,0,L);
}

void inOrder(Tree root, List* L){
// O(n)
// sorted order
	if (root == NULL){ return; }
	inOrder(root->left,L);
	printf("%lld\t",root->data);
	listInsert(root->data,0,L);
	inOrder(root->right,L);
}

int btLeaves(Tree root){
	if (root == NULL){ return 0; }
	if (root->right == NULL && root->left == NULL){ return 1; }
	return btLeaves(root->left) + btLeaves(root->right);
}





