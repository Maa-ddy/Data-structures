#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node* List;
typedef struct dNode dNode;//doubly linked list node
typedef struct dNode* dList;//doubly linked list
typedef struct Stack Stack;
typedef struct Queue Queue;
typedef struct tNode tNode;//tree node
typedef struct tNode* Tree;




struct Node {
	long long data;
	struct Node* next;
};

struct dNode {
	long long data;
	struct dNode* next;
	struct dNode* previous;
};

struct Stack{
	List head;
};

struct Queue{
	List head;
	List tail;
};

struct tNode {
	long long data;
	struct tNode* left;
	struct tNode* right;
};

//Linked Lists functions:
void listInsert(long long element, long long position, List* L);
void listRemove(long long position, List* L);
long long  listSize(List L);
void listClear(List* L);
long long  listGet(long long position, List L);
void listPrint(List L);
long long  emptyList(List L);
void listReverse(List* L);


//doubly Linked Lists functions:
void dlistInsert(long long element, long long position, dList* L);
void dlistRemove(long long position, dList* L);
long long  dlistSize(dList L);
void dlistClear(dList* L);
long long  dlistGet(long long position, dList L);
void dlistPrint(dList L);
long long  emptydList(dList L);
//
void dlistReverse(dList* L);


//Stacks functions:
void stackPush(long long element, Stack* St);
long long  stackPop(Stack* St);
long long  stackSize(Stack St);
void stackClear(Stack* St);
void stackPrint(Stack St);
long long  stackPeek(Stack St);
long long  emptyStack(Stack St);
void initStack(Stack* St);


//Queue functions
void queuePush(long long element, Queue* Qu);
long long  queuePop(Queue* Qu);
long long  queueSize(Queue Qu);
void queueClear(Queue* Qu);
void queuePrint(Queue Qu);
long long  queuePeek(Queue Qu);
long long  emptyQueue(Queue Qu);
void initQueue(Queue* Qu);




//Tree functions
void bstInsert(long long element, Tree* root);
int  bstContains(long long element, Tree root);
int  isBST(Tree root);
long long  bstMin(Tree root);
long long  bstMax(Tree root);
int  btHeight(Tree root);
int  btSize(Tree root);
int  btLeaves(Tree root);
void levelOrder(Tree root, List* L);
void preOrder(Tree root, List* L);
void postOrder(Tree root, List* L);
void inOrder(Tree root, List* L);
//
void bstRemove(Tree* root, long long element);







