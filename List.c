//Jerico Factor 
//PA1
//ID: 1674120

//List.c

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj
{
	int data; 
	struct NodeObj* next; 
	struct NodeObj* prev; 
} NodeObj;

typedef struct ListObj
{
	Node head; 
	Node tail; 
	int length;  
} ListObj;

List newList(void)
{
	List L; 
	L = malloc(sizeof(ListObj));
	L->length = 0; 
	L->head = malloc(sizeof(NodeObj));  
	L->tail = malloc(sizeof(NodeObj));
	L->head->next = L->tail; 
	L->head->prev = NULL; 
	L->tail->prev = L->head;  
	L->tail->next = NULL; 
	return L; 
}

void freeList(List* pL)
{
	if(pL == NULL)
		return; 

	List L = *pL; 
	Node nodePtr = L->head; 
	while (nodePtr != NULL)
	{
		Node cur = nodePtr->next; 
		free(nodePtr); 
		nodePtr = cur; 
	}
	free(L); 
	pL = NULL; 
}

int length(List L)
{
	return L->length; 
}

int frontValue(List L)
{
	if(L->length == 0)
	{
		printf("ListError: calling frontValue on empty List"); 
		exit(1); 
	}
	return L->head->next->data; 
}

int backValue(List L)
{
	if(L->length == 0)
	{
		printf("ListError: calling backValue on empty List"); 
		exit(1); 
	}
	return L->tail->prev->data; 
}

int getValue(Node N)
{
	if(N != NULL)
		return N->data;
	else
	{
		printf("NodeError: calling getValue on empty node"); 
		exit(1);
	}
	  
}

int equals(List A, List B)
{
	if (A->length != B->length)
		return 0; 
	
	Node ptrA = A->head; 
	Node ptrB = B->head; 

	while(ptrA != A->tail && ptrB != B->tail)
	{
		if(ptrA->data == ptrB->data)
		{
			ptrA = ptrA->next; 
			ptrB = ptrB->next; 
		}
		else
			return 0;
	}

	return 1; 

}

void clear(List L)
{
	// if(L == NULL)
	// {
	// 	L = newList();
	// 	return;
	// }
	// freeList(&L);
	// L = newList();
	while(length(L) != 0)
	{
		deleteFront(L);
	}
}

Node getFront(List L)
{
	if(L->length != 0)
		return L->head->next;
	else 
		return NULL;
}
Node getBack(List L)
{
	if(L->length != 0)
		return L->tail->prev;
	else 
		return NULL;
}

Node getPrevNode(Node N)
{
	if(N->prev->prev != NULL)
		return N->prev;
	else
		return NULL; 
}

Node getNextNode(Node N)
{
	if(N->next->next != NULL)
		return N->next; 
	else 
		return NULL; 
}

void prepend(List L, int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data; 

	Node next = L->head->next; 
	L->head->next = N;
	next->prev = N; 
	N->prev = L->head; 
	N->next = next; 
	L->length ++; 
}

void append(List L, int data)
{
	Node N = malloc(sizeof(NodeObj)); 
	N -> data = data; 

	Node prev = L->tail->prev; 
	L->tail->prev = N; 
	prev->next = N; 
	N->prev = prev; 
	N->next = L->tail; 

	L->length ++; 
}

void insertBefore(List L, Node N, int data)
{
	Node insertData = malloc(sizeof(NodeObj));
	insertData->data = data; 

	Node prev = N->prev;
	prev->next = insertData; 
	N->prev = insertData; 
	insertData->next = N; 
	insertData->prev = prev; 
	L->length ++; 

}

void insertAfter(List L, Node N, int data)
{
	Node insertData = malloc(sizeof(NodeObj));
	insertData->data = data; 

	Node next = N->next;
	next->prev = insertData; 
	N->next = insertData; 
	insertData->next = next; 
	insertData->prev = N; 
	L->length ++; 

}

void deleteFront(List L)
{
	Node front = L->head->next; 
	Node newFront = front->next; 

	L->head->next = newFront; 
	newFront->prev = L->head; 
	free(front); 
	L->length --; 
}

void deleteBack(List L)
{
	Node back = L->tail->prev; 
	Node newBack = back->prev;

	L->tail->prev = newBack; 
	newBack->next = L->tail; 
	free(back); 
	L->length --; 

}

void detachNode(List L, Node N)
{
	Node next = N->next; 
	Node prev = N->prev; 

	N->next = NULL; 
	N->prev = NULL; 

	prev->next = next; 
	next->prev = prev; 
	L->length --; 
}

void attachNodeBetween(List L, Node N, Node N1, Node N2)
{
	if(N1->next != N2 || N2->prev != N1)
	{
		printf("Nodes not next to each other\n"); 
		exit(1); 
	}
	N1->next = N; 
	N2->prev = N; 
	N->next = N2; 
	N->prev = N1; 
	L->length ++; 
} 
void attachNodeBefore(List L, Node N, Node N1)
{
	Node temp = N1->prev; 
	attachNodeBetween(L, N, temp, N1); 
}

void attachNodeAfter(List L, Node N, Node N1) 
{
	Node temp = N1->next; 
	attachNodeBetween(L, N, N1, temp); 
}

void deleteNode(Node N) 
{
	if(N->next != NULL || N->prev != NULL)
	{
		printf("error: trying to delete a node that is still attatched\n"); 
		exit(1); 
	}
	else 
		free(N); 
}

int inList(List L, int i)
{
	Node N = getFront(L); 
	while (N != NULL)
	{
		if(getValue(N) == i)
		{
			return 1; 
		}
		N = getNextNode(N); 
	}
	return 0; 
}

int insertSorted(List L, int i)
{
	if(length(L) == 0)
	{
		append(L,i); 
		return 1; 
	}

	Node N = getFront(L); 
	while(N != NULL)
	{ 
		if(i <= N->data)
			break; 
		if(i > N->data)
		{
			N = getNextNode(N);
		}
	}
	if (N == NULL)
	{
		append(L,i);
		return 1; 
	}
	insertBefore(L, N, i); 
	return 1; 
}

void printList(FILE* out, List L)
{
	if(L == NULL)
	{
		fprintf(out, "list does not exist");
		return;
	}
	else if(L->length == 0)
	{
		fprintf(out, "List is empty"); 
		return;
	}
	Node ptr = L->head; 
	while(ptr->next != L->tail)
	{	
		ptr = ptr->next;
		fprintf(out,"%d ", ptr->data); 
	}
	return; 
}

