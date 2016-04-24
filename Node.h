#ifndef _DNODE_H
#define _DNODE_H

/***********************************************\
   template Node class for doubly linked list
\***********************************************/

template <typename dataType> struct Node
{
   dataType data;
   Node *prev, *next;
   
   // constructors
   Node() : prev(NULL), next(NULL) {}

   Node(const dataType& dataItem, Node *prevPtr, Node *nextPtr) : 
       data(dataItem), prev(prevPtr), next(nextPtr) 
   {   
      // we are now pointing to Nodes on either side
      // get them pointing to this Node
      if (prev != NULL) prev->next = this;
      if (next != NULL) next->prev = this;
   }
   
   // destructor
   ~Node()
   {
      // cut Node out of list before deleting
      if (prev != NULL) prev->next = next;
      if (next != NULL) next->prev = prev;
   }
};
#endif
