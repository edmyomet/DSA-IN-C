#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
typedef int elementType;
typedef int __bool;
typedef struct stackList* stackPtr;
typedef struct stackList* returnStack;
typedef struct stackList** stackDoublePtr;
typedef struct listNode* list;
typedef struct listNode** listDoublePtr;
typedef struct listNode* returnList;
typedef int __STACK_DATA_;
typedef struct Queue* queuePtr;
typedef struct Queue* returnQ;
typedef struct Queue** queueDoublePtr;
typedef struct queuePtrs* frontAndBack;
typedef int __Q_DATA;
typedef int QData;
typedef enum{
    T_STACK,
    T_QUEUE,
    T_LIST,
    T_ARR
}MY_TYPE;


#define __MEM_ERR_ "Memory Allocation Error"
#define __INIT_ERR_ "Initialisation Error"
#define __STACK_UNDERFLOW__ "Stack is Empty, cannot remove items"
#define __STACK_OVERFLOW__ "Stack is Full, cannot add items"
#define __MAKE_EMPTY_ERROR_ "Cannot delete an empty stack"
#define __NONE__ 0
#define __STACK_CAPACITY__  50

#define __LIST_EMPTY__ "The list is empty"
#define __NOT_FOUND__ "Element not found"
#define __ISNULL_ERR__ "Cannot delete an already empty list"
#define __DATATYPE_NONEXIST_ "User defined data type not a part of any struct definitions"
#define __NULL_CONST_ "NULL"

#define __QUEUE_E_ "Queue is Empty"
#define __QUEUE_EERR_ "Queue Null Error"
#define __QUEUE_CAPACITY_ 45
#define __QUEUE_F_  "Queue is Full"
#define __QUEUE_FR_ "Unknown Dequeue Error"

/* ALL FUNCTION PROTOTYPES*/

__bool isNull(list);
__bool _allocError(stackPtr, list,queuePtr, MY_TYPE);
__bool _initError(stackPtr, list,queuePtr,MY_TYPE);
__bool _memAllocError(stackPtr, list,queuePtr, MY_TYPE);
void throwErrr(char*);
__bool isEmpty(stackPtr);
__bool isEmptyQInternal(queuePtr);

void newLine(){
    printf("\n");
}

void throwErr(char* errorName){
    printf("%s",errorName);
    newLine();
    return;
}

__Q_DATA checkRear(QData value){
    if(++value >= __QUEUE_CAPACITY_)
        value = 0;
    return value;
}
__bool checkFrontAndRear(QData Front, QData Rear){
    if(Front>Rear){
        throwErr(__QUEUE_FR_);
        return 1;
    }
    return 0;
}
__bool _allocError(stackPtr Stack, list List, queuePtr queue, MY_TYPE T){
    switch(T){
        case T_LIST:
            if(isNull(List)){
                return 1;
            }
            return 0;
        case T_STACK:
            if(isEmpty(Stack)){
                return 1;
            }
            return 0;
        case T_QUEUE: 
            if(isEmptyQInternal(queue)){
                return 1;
            }
            return 0;
        default: throwErr(__DATATYPE_NONEXIST_);break;
    }
}
__bool _initError(stackPtr Stack, list List, queuePtr queue, MY_TYPE T){
    switch(T){
        case T_LIST: if(!_allocError(Stack,List,queue,T)){
            throwErr(__LIST_EMPTY__);
            return 1;
        }
        return 0;
        case T_STACK: if(!_allocError(Stack, List,queue,T)){
            throwErr(__INIT_ERR_);
            return 1;
        }
        return 0;
        case T_QUEUE: if(!_allocError(Stack,List,queue,T)){
            throwErr(__INIT_ERR_);
            return 1;
        }
        return 0;

        default: throwErr(__DATATYPE_NONEXIST_); break;

    }
    return 1;
}
__bool _memAllocError(stackPtr Stack,list List, queuePtr queue, MY_TYPE T){
    switch(T){
        case T_LIST: if(_allocError(Stack,List,queue,T)){
            throwErr(__LIST_EMPTY__);
            return 1;
        }
        return 0;
        case T_STACK: if(_allocError(Stack, List,queue,T)){
            throwErr(__INIT_ERR_);
            return 1;
        }
        return 0;

        case T_QUEUE: if(_allocError(Stack,List,queue,T)){
            throwErr(__MEM_ERR_);
            return 1;
        }
        return 0;

        default: throwErr(__DATATYPE_NONEXIST_); break;

    }
}


#ifndef __STACK__ADT_
#define __STACK__ADT_

struct stackList{
    MY_TYPE T;
    elementType val;
    struct stackList* next;
    int top;
};


//initialising an empty stack 
returnStack createEmptyStack(){
    struct stackList* newStack = NULL;
    newStack = (returnStack)malloc(sizeof(struct stackList));
    newStack->T = T_STACK;
    _memAllocError(newStack,NULL,NULL,newStack->T);
    newStack->next = NULL;
    newStack->top = __NONE__;
    return newStack;
}

//initialising a non empty stack
returnStack createStackData(elementType K){
    struct stackList* newStack = NULL;
    newStack = (returnStack)malloc(sizeof(struct stackList));
    newStack->T = T_STACK;
    _memAllocError(newStack,NULL,NULL,newStack->T);
    newStack->next = NULL;
    newStack->val= K;
    newStack->top++;
    return newStack;
}

__bool isEmpty(stackPtr Stack){
    return !Stack;
}
__bool isFull(stackPtr Stack){
    return Stack->top == __STACK_CAPACITY__;
}
returnStack push(stackPtr Stack, elementType K){
    struct stackList* tempNode = createStackData(K);
    if(isEmpty(Stack)){
        Stack = tempNode;
        return Stack;
    }
    else if(!isFull(Stack)){
        tempNode->top = ++Stack->top;
        tempNode->next = Stack;
        Stack = tempNode;
    }
    else{
        throwErr(__STACK_OVERFLOW__);
    }
    return Stack;
}

__STACK_DATA_ viewTop(stackPtr Stack){
    return Stack->val;
}
returnStack pop(stackPtr Stack){
    if(isEmpty(Stack)){
        throwErr(__STACK_UNDERFLOW__);
        return Stack;
    }
        
    else{
        struct stackList* tempNode = Stack;
        Stack = Stack->next;
        free(tempNode);
        return Stack;
    }
}
__STACK_DATA_ viewTopAndPop(stackPtr Stack){
    if(isEmpty(Stack))
        throwErr(__STACK_UNDERFLOW__);
    else{
        struct stackList* tempNode = Stack;
        Stack = Stack->next;
        return tempNode->val;
    }
}

returnStack makeEmpty(stackPtr Stack){
    if(isEmpty(Stack))
        throwErr(__MAKE_EMPTY_ERROR_);
    else{
        free(Stack);
        return NULL;
    }
}
#endif

#ifndef __LIST_ADT_
#define __LIST_ADT_

struct listNode{
    MY_TYPE T;
    elementType val;
    struct listNode* next;
};
__bool isNull(list List){
    return List==NULL;
}

list createEmptyList(){
    struct listNode* tempNode = NULL;
    tempNode = (returnList)malloc(sizeof(struct listNode));
    tempNode->T = T_LIST;
    _memAllocError(NULL,tempNode,NULL,tempNode->T);
    tempNode->next = NULL;
    return tempNode;
}

list putData(list List, elementType K){
    List->val = K;
    return List;
}
list createNode(elementType K){
    struct listNode* temp = NULL;
    temp = (returnList)malloc(sizeof(struct listNode));
    temp->T = T_LIST;
    _memAllocError(NULL,temp,NULL,temp->T);
    temp->val = K;
    temp->next = NULL;
    return temp;
}

void insertNode(list List, elementType K){
    List->next = createNode(K);
    return;
}
list insertNodeFront(list List, elementType K){
    struct listNode* tNode = createNode(K);
    tNode->next = List;
    List = tNode;
    return List;
}
void printList(list List){
    while(List){
        printf("%d\t",List->val);
        List = List->next;
    }
    throwErr(__NULL_CONST_);
    newLine();
}

void insertNodePos(list List, elementType pos,elementType data){
    int count=1;
    while(List&&count<pos){
        List=List->next;
        count++;
    }
    struct listNode* temp = createNode(data);
    temp->next = List->next;
    List->next = temp;
    return;
}
list findPrevious(list List,elementType K){
    if(isNull(List) || isNull(List->next))
        return List;
    else{
        while(List && List->next->val!=K)
            List=List->next;
        struct listNode* tNode = List;
        tNode->next = NULL;
        return tNode;
    }
}
void deleteLast(list List){
    if(isNull(List)){
        throwErr(__ISNULL_ERR__);
        return;
    }
    else{
        while(List->next->next)
            List=List->next;
        List->next=NULL;
        
    }
    return;
}
list deleteFirst(list List){
    if(isNull(List))
        throwErr(__ISNULL_ERR__);
    else{
        List=List->next;
        return List;

    }
}
list deleteWhole(list List){
    if(isNull(List))
        throwErr(__ISNULL_ERR__);
    else{
        free(List);
        return NULL;
    }
}


#endif

#ifndef __QUEUE_ADT_
#define __QUEUE_ADT_


struct Queue{
    MY_TYPE T;
    QData front;
    QData rear;
    elementType* Arr;
    QData AMTC;
};
__bool isEmptyQInternal(queuePtr queue){
    return !queue;
}
__bool isEmptyQ(queuePtr queue){
    if(isEmptyQInternal(queue)){
        throwErr(__QUEUE_E_);
        return 1;
    }
    return 0;
        
}


__bool isNoData(queuePtr queue){
    return queue->AMTC == __NONE__;
}

__bool isFullQ(queuePtr queue){
    return queue->AMTC == __QUEUE_CAPACITY_-1;
}

returnQ createEmptyQueue(){
    struct Queue* newQueue = NULL;
    newQueue = (returnQ)malloc(sizeof(struct Queue));
    newQueue->T = T_QUEUE;
    _memAllocError(NULL,NULL,newQueue,newQueue->T);
    newQueue->front = newQueue->rear = __NONE__;
    newQueue->Arr = (QData*)malloc(__QUEUE_CAPACITY_*sizeof(int));
    return newQueue;
}
returnQ putDataQueue(queuePtr queue,elementType K){
    queue->Arr[queue->rear++] = K;
    queue->AMTC++;
    return queue;
}
returnQ createDataQueue(elementType K){
    struct Queue* newQueue = NULL;
    newQueue = (returnQ)malloc(sizeof(struct Queue));
    newQueue->T = T_QUEUE;
    _memAllocError(NULL,NULL,newQueue,newQueue->T);
    newQueue->front = __NONE__;
    newQueue->rear = __NONE__;
    newQueue->Arr=(QData*)malloc(__QUEUE_CAPACITY_*sizeof(int));
    newQueue->Arr[newQueue->rear++] = K;
    newQueue->AMTC++;
    return newQueue;
}

__Q_DATA returnFront(queuePtr queue){
    return queue->Arr[queue->front];
}

returnQ Enqueue(queuePtr queue, elementType K){
    if(queue->AMTC>__QUEUE_CAPACITY_){
        throwErr(__QUEUE_F_);
        return queue;
    }
    queue->Arr[++queue->rear] = K;
    queue->AMTC++;
    return queue;
}
returnQ Dequeue(queuePtr queue){
    if(isNoData(queue)){
        throwErr(__QUEUE_EERR_);
        newLine();
        return queue;
    }
    queue->AMTC--;
    ++queue->front;
    return queue;
}

returnQ reverseQ(queuePtr queue){
    struct Queue* revQueue = NULL;
    revQueue = createEmptyQueue();
    revQueue = putDataQueue(revQueue, queue->Arr[queue->rear]);
    __Q_DATA temp = queue->rear;
    while(temp-->=0){
        revQueue->Arr[revQueue->rear++] = queue->Arr[temp];
    }
    return revQueue;
}


#endif