#ifndef _DLISTITERATOR_H_
#define _DLISTITERATOR_H_

#include "Node.h"

/***********************************************\
   template iterator class for doubly linked
   list class
\***********************************************/

template <typename dataType> class Iterator
{
   private:
      List<dataType> *parent;
      Node<dataType> *current;

   public:
      // constructor
      Iterator() : parent(NULL), current(NULL)
      {
      }

      Iterator(List<dataType> *myParent, Node<dataType> *position) :
         parent(myParent), current(position)
      {
      }

      /***********************************************\
         data access operators
      \***********************************************/

      // overloaded dereference operator
      dataType& operator * () const
      {
         if (current == NULL)
         {
            throw std::invalid_argument("Attempting to dereference NULL in Iterator");
         }
         return current->data;
      }

      // overloaded arrow operator
      dataType* operator -> () const
      {
         if (current == NULL)
         {
            throw std::invalid_argument("Attempting to dereference NULL in Iterator");
         }
         return &(current->data);
      }

      /***********************************************\
         increment operators
      \***********************************************/

      // overloaded prefix increment operator. E.g ++i;
      Iterator<dataType> operator ++ ()
      {
         if (current == NULL)
         {
            throw std::invalid_argument("Attempting to advance past end in Iterator");
         }
         current = current->next;
         return *this;
      }

      // overloaded postfix increment operator. E.g. i++;
      Iterator<dataType> operator ++ (int)
      {
         Iterator<dataType> current_data = *this;
         ++(*this);
         return current_data;
      }

      /***********************************************\
         decrement operators
      \***********************************************/

      // overloaded prefix decrement operator. E.g. --i;
      Iterator<dataType> operator -- ()
      {
         if (current == NULL)
         {
            throw std::invalid_argument("Attempting to advance before start in Iterator");
         }
         current = current->prev;
         return *this;
      }

      // overloaded postfix decrement operator. E.g. i--;
      Iterator<dataType> operator -- (int)
      {
         Iterator<dataType> current_data = *this;
         --(*this);
         return current_data;
      }

      /***********************************************\
         equality operators
      \***********************************************/

      // overloaded equality operator
      bool operator == (const Iterator &other) const
      {
         return current == other.current;
      }

      // overloaded inequality operator
      bool operator != (const Iterator &other) const
      {
         return current != other.current;
      }
};
#endif