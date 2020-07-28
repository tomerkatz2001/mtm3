#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include<iostream>
#include <stdlib.h>
#include "Auxiliaries.h"

namespace mtm{
class IntMatrix{

    private:
    int** matrix;
    mtm::Dimensions dim;

    public:
    explicit IntMatrix(const Dimensions& dimensions, int val=0);//
    IntMatrix(const IntMatrix& M);//copy constarctor
    IntMatrix&  operator =(const IntMatrix& M);//assignment operator
    ~IntMatrix();
    static IntMatrix Identity(int size);
    int height() const;
    int width() const;
    int size() const;
    IntMatrix transpose() const;
    IntMatrix& operator+=(const IntMatrix& M);//used for the + operator.
    IntMatrix operator-()const;
    IntMatrix operator-(const IntMatrix& matrix1)const;
    friend std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix); //print operator
    IntMatrix& operator+=(int scalar);
    int& operator()(int i,int j);
    int operator()(int i,int j) const;  
    IntMatrix operator<(int num);
    IntMatrix operator>(int num);
    IntMatrix operator >=(int num);
    IntMatrix operator <=(int num);
    IntMatrix operator ==(int num);
    IntMatrix operator !=(int num);
    class iterator;
    iterator begin();
    iterator end();
    class const_iterator;
    const_iterator begin()const;
    const_iterator end()const;
};
IntMatrix operator+(const IntMatrix& matrix, int scalar);
IntMatrix operator+( int scalar,const IntMatrix& matrix);
IntMatrix operator+(const IntMatrix& M1, const IntMatrix& M2);
bool all(const IntMatrix mat);
bool any(const IntMatrix mat);

class IntMatrix::iterator{
    
    private:
    IntMatrix* matrix;
    int index;
    
    public:
    friend class IntMatrix;
    iterator (IntMatrix* matrix_ptr ,int index);
    ~iterator()=default;//need to check if it free the pointer
    iterator& operator=(const iterator& i)=default;  
    int& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& i) const;
    bool operator!=(const iterator& i) const;
};

class IntMatrix::const_iterator
{
    
    private:
    const IntMatrix* matrix;
    int index;

    public:
    friend class IntMatrix;
    explicit const_iterator(const IntMatrix* matrix_ptr, int index);
    ~const_iterator()=default;
    const_iterator& operator=(const const_iterator& i)=default;
    int operator*()const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& i)const;
    bool operator!=(const const_iterator& i)const;

};
}
#endif
