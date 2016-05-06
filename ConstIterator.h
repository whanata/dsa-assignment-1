#ifndef _CONSTDLISTITERATOR_H_
#define _CONSTDLISTITERATOR_H_

#include "Node.h"

/***********************************************\
   template iterator class for doubly linked
   list class
\***********************************************/

template <typename dataType> class ConstIterator
{
   friend class List<dataType>;

   private:
      const List<dataType> *parent;
      const Node<dataType> *current;

   public:
      // constructor
      ConstIterator() : parent(NULL), current(NULL) 
      {
      }

      ConstIterator(const List<dataType> *myParent, const Node<dataType> *position) :
         parent(myParent), current(position) 
      {
      }

      /***********************************************\
         data access operators
      \***********************************************/

      // overloaded dereference operator
      const dataType& operator * () const 
      {
         if (current == NULL) 
         {
            throw std::invalid_argument("Attempting to dereference NULL in iterator");
         }
         return current->data;
      }

      // overloaded arrow operator
      const dataType* operator -> () const 
      {
         if (current == NULL) 
         {
            throw std::invalid_argument("Attempting to dereference NULL in iterator");
         }
         return &(current->data);
      }

      /***********************************************\
         increment operators
      \***********************************************/

      // overloaded prefix increment operator. E.g ++i;
      ConstIterator<dataType> operator ++ () 
      {
         if (current == NULL) 
         {
            throw std::invalid_argument("Attempting to advance past end in iterator");
         }
         current = current->next;
         return *this;
      }

      // overloaded postfix increment operator. E.g. i++;
      ConstIterator<dataType> operator ++ (int) 
      {
         ConstIterator<dataType> current_data = *this;
         ++(*this);
         return current_data;
      }

      /***********************************************\
         decrement operators
      \***********************************************/

      // overloaded prefix decrement operator. E.g. --i;
      ConstIterator<dataType> operator -- () 
      {
         if (current == NULL) 
         {
            throw std::invalid_argument("Attempting to advance before start in iterator");
         }
         current = current->prev;
         return *this;
      }

      // overloaded postfix decrement operator. E.g. i--;
      ConstIterator<dataType> operator -- (int) 
      {
         Iterator<dataType> current_data = *this;
         --(*this);
         return current_data;
      }

      /***********************************************\
         equality operators
      \***********************************************/

      // overloaded equality operator
      bool operator == (const ConstIterator &other) const
      {
         return current == other.current;
      }

      // overloaded inequality operator
      bool operator != (const ConstIterator &other) const
      {
         return current != other.current;
      }
};
#endif