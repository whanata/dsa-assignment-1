#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdexcept>

namespace listspc
{
   // forward class declaration
   template <typename dataType> class List;

   #include "Node.h"
   #include "Iterator.h"
   #include "ConstIterator.h"

   /***********************************************\
      template class for doubly linked List
   \***********************************************/

   template <typename dataType> class List
   {
      private:
         Node<dataType> *head, *tail;
         int numItems;

      public:

         /*****************************************\
            Iterator friendship and functions
         \*****************************************/

         friend class Iterator<dataType>;
         friend class ConstIterator<dataType>;

         Iterator<dataType> begin() 
         {
            return Iterator<dataType>(this, head);
         }

         ConstIterator<dataType> begin() const 
         {
            return ConstIterator<dataType> (this, head);
         }

         Iterator<dataType> end() 
         {
            return Iterator<dataType>(this, NULL);
         }           

         ConstIterator<dataType> end() const
         {
            return ConstIterator<dataType>(this, NULL);
         }           

         /*****************************************\
            constructor and destructor functions
         \*****************************************/

         // default constructor
         List() : head(NULL), tail(NULL), numItems(0) 
         {
         }

         // copy constructor
         List(const List<dataType> &other) : 
            head(NULL), tail(NULL), numItems(0) 
         {
            for (ConstIterator<dataType> itr = other.begin(); itr != other.end(); itr++) 
            {
               pushBack(*itr);
            }
         }

         // destructor
         ~List() 
         {
            clear();
         }

         /*****************************************\
            size and swap functions
         \*****************************************/

         void clear()
         {
            Node<dataType> *current = NULL;
            
            while(head != NULL) 
            {
               // delete every Node in List
               current = head;
               head = head->next;
               delete current;
            }
            numItems = 0;
            tail = NULL;
         }

         void swap(List<dataType> &other) 
         {
            std::swap(numItems, other.numItems);
            std::swap(head, other.head);
            std::swap(tail, other.tail);
         }

         bool empty() 
         {
            return (numItems == 0);
         }

         int size() 
         {
            return numItems;
         }

         /*****************************************\
            push and insertion functions
         \*****************************************/

         void pushFront(const dataType &item) 
         {
            // insert item into front of List
            
            head = new Node<dataType>(item, NULL, head);
            numItems++;
            if (numItems == 1)
            {
               // As only one item in List, this will be the tail as well as the head.
               tail = head;
            }
         }

         void pushBack(const dataType &item) 
         {
            // insert item into back of List
            
            if (empty()) 
            {
               pushFront(item);
            } 
            else 
            {
               tail = new Node<dataType>(item, tail, NULL);
               numItems++;
            }
         }

         Iterator<dataType>insert(const Iterator<dataType> iter, const dataType &item) 
         {
            // insert item into List before the Node iter is pointing to. 
            // return Iterator pointing to the new Node 

            if (iter.current == head) 
            {
               // iter is pointing to the first Node in the List 
               pushFront(item);
               return begin();
            } 
            else if (iter.current == NULL) 
            {
               // iter is pointing to beyond end of List 
               pushBack(item);
               return Iterator<dataType>(this, tail);
            } 
            else 
            {
               // inserting Node between head and tail Nodes
               Node<dataType> *newNode = new Node<dataType>(item, 
                  iter.current->prev, 
                  iter.current);

               numItems++;
               return Iterator<dataType> (this, newNode);
            }
         }

         void replace(const Iterator<dataType> iter, const dataType &item)
         {
            Node<dataType> *replaceNode = iter.current;
            replaceNode->data = item;
         }

         /*****************************************\
            pop and erase functions
         \*****************************************/

         void popFront() 
         {
            // remove first item from List

            if (numItems == 1)
            {
               // removing last Node in List
               delete head;
               head = tail = NULL;
            }
            else
            {
               if (empty()) 
               {
                  throw std::invalid_argument("Attempting to pop front of empty List");
               }

               // make next Node in List the new head
               head = head->next;

               // delete the front Node
               delete head->prev;
            }
            numItems--;
         }

         void popBack() 
         {
            // remove last item from List

            if (numItems == 1) 
            {
               // removing last Node in List
               delete tail;
               head = tail = NULL;
            }
            else
            {
               if (empty()) 
               {
                  throw std::invalid_argument("Attempting to pop back of empty List");
               }

               // make prev Node in List the new tail
               tail = tail->prev;

               // delete the final Node
               delete tail->next;
            }
            numItems--;
         }

         Iterator<dataType> erase(Iterator<dataType> &iter) 
         {
            // delete the Node iter is pointing to.
            // update iter to point to next Node and then return it

            // keep track of Node to be deleted
            Node<dataType> *removeNode = iter.current;

            // advance iter to next Node
            iter++;

            if (removeNode == head) 
            {
               popFront();
            } 
            else if (removeNode == tail) 
            {
               popBack();
            } 
            else 
            {  
               // removeNode is between head and tail Nodes
               delete removeNode;
               numItems--;
            }

            return iter;
         }

         /*****************************************\
            find
         \*****************************************/

         Iterator<dataType> find(const dataType &searchData)
         {
            // look for searchData in List.
            // return Iterator to where found
            // if not found return end Iterator

            Node<dataType> *findNode = head;

            while (findNode != NULL && findNode->data != searchData)
            {
               findNode = findNode->next;
            }

            return Iterator<dataType> (this, findNode);
         }

         /*****************************************\
            overloaded operators
         \*****************************************/

         // assignment operator
         List<dataType>& operator = (const List<dataType> &other) 
         {
            List<dataType> tempCopy(other);

            swap(tempCopy);
            return *this;
         }
   };
}
#endif