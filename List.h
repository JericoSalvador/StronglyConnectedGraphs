//Jerico Factor
//PA1
//ID: 1674120

//List.h

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List; 

typedef struct NodeObj* Node; 

//Constructor - Destructor
List newList(void); 
void freeList(List* pL);

//access functions
int length(List L); // returns the number of nodes in the list

int frontValue(List L); //returns the integer in front node
						//Precondition: L has at least one Node in it

int backValue(List L); //returns the integer in the back Node
					   //precondition: L has at least one Node in it

int getValue(Node N); //returns the integer in Node N
					  //precondition: N is not NULL

int equals(List A, List B); //returns 1 if list A and list B are the
							//same integer sequence, otherwise returns 0


//Manipulation procedures
void clear(List L); //resets the list to the empty state

Node getFront(List L);
//if List is non-empty return the front Node without
//changing the list. Otherwise, do nothing

Node getBack(List L); 
//if List is non-empty return the back Node without
//changing the list. Otherwise, do nothing

Node getPrevNode(Node N);
//without changing the list that N is on, returns the Node that is previous 
//to Node N on its List. If there is no previous Node, returns NULL. 

Node getNextNode(Node N); 
//without changing the list that N is on, returns the Node that is next after
//Node N on its list. if there is no next node, returns Null

void prepend(List L, int data);
//inserts a new Node into List L before the front Node that has data as
//its value. If list is empty, makes a new Node the only Node on the list. 

void append(List L, int data); 
//Inserts a new Node into List L after the back Node that has data as its value
//If List is empty, makes that new Node the only Node on the list. 

void insertBefore(List L, Node N, int data); 
//Insert a new Node into Node N’s list before Node N that has data as its value.
//Assume that Node N is on List L. Precondition:  Node N is not NULL

void insertAfter(List L, Node N, int data); 
// Insert a new Node into Node N’s list after Node N that has data as its value.
// Assume that Node N is on List L. Precondition:  Node N is not NULL

void deleteFront(List L); 
// Deletes the front Node in List L.
// Precondition:  L has at least one Node on it.

void deleteBack(List L); 
// Deletes the back Node in List L.
// Precondition:  L has at least one Node on it.

void detachNode(List L, Node N); 
// Removes N from List L by making the Node before // Node N link to the Node that’s after Node N as its
// next Node, and making the Node after Node N link to // the Node that’s before Node N as its previous Node. //
// After detachNode, Node N should have NULL as both its
// next and previous Nodes.
//
// Special cases:
//
// If Node N is the front the List L, then the Node after // Node N becomes the front of List L, which should have // a NULL previous Node.
//
// If Node N is the back of List L, then the Node before // Node N becomes the back of List L, which should have // a NULL next Node.
//
// Precondition: N is a Node that’s on List L.

void attachNodeBetween(List L, Node N, Node N1, Node N2);

void attachNodeBefore(List L, Node N, Node N1);
// attatch Node N before N1

void attachNodeAfter(List L, Node N, Node N1); 
void deleteNode(Node N); 

int inList(List L, int i);
// returns 1 if i in list
// else returns 0; 

int insertSorted(List L, int i); 

//other operations 
void printList(FILE* out, List L);
// Prints the values in List L from front to back
// to the file pointed to by out, formatted as a
// space-separated string.

#endif