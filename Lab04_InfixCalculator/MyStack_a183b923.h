#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <iostream>
#include <algorithm>

#include "MyVector.h"

template <typename DataType>
class MyStack : private MyVector<DataType>
{
  public:

    // default constructor
    explicit MyStack(size_t initSize = 0)
    {
        // code begins

        // code ends
    }

    // copy constructor
    MyStack(const MyStack & rhs)
    {
        // code begins
        //DataType *data = new DataType[capacity()];
        this->resize(rhs.size());
        this->reserve(rhs.capacity());
        for (int i = 0; i < size(); i++) {
          (*this)[i] = (rhs)[i];
        }

        // code ends
    }

    // move constructor
    MyStack(MyStack && rhs)
    {
        // code begins
        //rhs.MyVector<DataType>::data()= nullptr;
        this->resize(rhs.size());
        this->reserve(rhs.capacity());
        //DataType *data = new DataType[capacity()];
        for (int i = 0; i < size(); i++) {
          (*this)[i] = std::move((rhs)[i]);
        }
        rhs.MyVector<DataType>::resize(0);
        rhs.MyVector<DataType>::reserve(0);
        // code ends
    }

    // destructor
    ~MyStack()
    {

    }

    // copy assignment
    MyStack & operator= (const MyStack & rhs)
    {
        // code begins
        MyStack copy = rhs;
        std::swap(*this, copy);
        return *this;
        // code ends
    }

    // move assignment
    MyStack & operator= (MyStack && rhs)
    {
        // code begins
        std::swap(MyVector<DataType>::size(), rhs.MyVector<DataType>::size());
        std::swap(MyVector<DataType>::capacity(), rhs.MyVector<DataType>::capacity());
        std::swap(MyVector<DataType>::data(), rhs.MyVector<DataType>::data());

        return *this;
        // code ends
    }

    // insert x to the stack
    void push(const DataType & x)
    {
        // code begins
        //myStack.push_back(x);
        MyVector<DataType>::push_back(x);
        // code ends
    }

    // insert x to the stack
    void push(DataType && x)
    {
        // code begins
        MyVector<DataType>::push_back(x);
        // code ends
    }

    // remove the last element from the stack
    void pop(void)
    {
        // code begins
        MyVector<DataType>::pop_back();
        // code ends
    }

    // access the last element of the stack
    const DataType & top(void) const
    {
        // code begins
        return(MyVector<DataType>::back());
        // code ends
    }

    // check if the stack is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        // code begins
        return(MyVector<DataType>::empty());
        // code ends
    }

    // access the size of the stack
    size_t size() const
    {
        // code begins
        return(MyVector<DataType>::size());
        // code ends
    }

    // access the capacity of the stack
    size_t capacity(void) const
    {
        // code begins
        return(MyVector<DataType>::capacity());
        // code ends
    }

};


#endif // __MYSTACK_H__
