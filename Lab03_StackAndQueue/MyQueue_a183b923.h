#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <iostream>
#include <algorithm>

#include "MyVector_a183b923.h"

template <typename DataType>
class MyQueue : private MyVector<DataType>
{
  private:
    size_t dataStart, dataEnd;

    // changes the size of the array to newSize
    void resize(size_t newSize)
    {
        // code begins

        if(newSize > capacity()) {
          reserve(newSize*2);
        }
        MyVector<DataType>::resize(newSize);
        // code ends
    }

    // requests for newCapacity amount of space
    void reserve(size_t newCapacity)
    {
        // code begins

      if(capacity() < size()) {
        return;
      }

      MyVector<DataType>::reserve(newCapacity);


        // code ends
    }

  public:

    // default constructor
    explicit MyQueue(size_t initSize = 0)
    {
        // code begins
        dataStart = 0;
        dataEnd = 0;
        // code ends
    }

    // copy constructor
    MyQueue(const MyQueue & rhs)
    {
        // code begins
        this->resize(rhs.size());
        this->reserve(rhs.capacity());
        for (int i = 0; i < size(); i++) {
          (*this)[i] = (rhs)[i];
        }
        // code ends
    }

    // move constructor
    MyQueue(MyQueue && rhs)
    {
        // code begins
        // dataStart = rhs.dataStart;
        // dataEnd = rhs.dataEnd;
        this->resize(rhs.size());
        this->reserve(rhs.capacity());
        int j = rhs.dataStart;
        // //DataType *data = new DataType[capacity()];
        for (int i = 0; i < size(); i++) {
          (*this)[i] = std::move((rhs)[j]);
          j = (j+1)%capacity();

        //  (*this)[i] = std::move((rhs)[i]);
        }
        rhs.MyVector<DataType>::resize(0);
        rhs.MyVector<DataType>::reserve(0);
        // code ends
    }

    // destructor
    ~MyQueue()
    {
        // code begins

        // code ends
    }

    // copy assignment
    MyQueue & operator= (const MyQueue & rhs)
    {
        // code begins
        MyQueue copy = rhs;
        std::swap(*this, copy);
        return *this;
        // code ends
    }

    // move assignment
    MyQueue & operator= (MyQueue && rhs)
    {
        // code begins
        std::swap(size(), rhs.size());
        std::swap(capacity(), rhs.capacity());
        std::swap(MyVector<DataType>::data(), rhs.data());

        return *this;
        // code ends
    }

    // insert x into the queue
    void enqueue(const DataType & x)
    {
        // code begins
        resize(size()+1);
        (*this)[dataEnd] = x;
        dataEnd = (dataEnd+1)%capacity();
        //(*this)[dataEnd] = x;
        // code ends
    }

    // insert x into the queue
    void enqueue(DataType && x)
    {
        // code begins
        resize(size()+1);
        (*this)[dataEnd] = std::move(x);
        dataEnd = (dataEnd+1)%capacity();
        //(*this)[dataEnd] = std::move(x);
        // code ends
    }

    // remove the first element from the queue
    void dequeue(void)
    {
        // code begins
        //MyVector<DataType>::push_back(x)
        if(empty() != true) {
          dataStart = (dataStart+1)%capacity();
          resize(size()-1);
        }
        // code ends
    }

    // access the first element of the queue
    const DataType & front(void) const
    {
        // // code begins
        // if(MyVector<DataType>::empty() != true) {
        return (*this)[dataStart];
        // }


        // code ends
    }

    // check if the queue is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        // code begins
        return(MyVector<DataType>::size() == 0);
        // code ends
    }

    // access the size of the queue
    size_t size() const
    {
        // code begins
        return(MyVector<DataType>::size());
        // code ends
    }

    // access the capacity of the queue
    size_t capacity(void) const
    {
        // code begins
        return(MyVector<DataType>::capacity());
        // code ends
    }

};


#endif // __MYQUEUE_H__
