#ifndef MYPART_H
#define MYPART_H
#include<iostream>
#include <stdlib.h>
#include "Auxiliaries.h"
namespace mtm{
class intMatrix{

    private:
    int** matrix;
    mtm::Dimensions dim;

    public:
    intMatrix(const intMatrix& M);//copy constarctor
    intMatrix&  operator =(const intMatrix& M);//assignment operator
    ~intMatrix();
    int height() const;
    int width() const;
    int size() const;
    intMatrix& operator+=(const intMatrix& M);//used for the + operator.
    friend std::ostream& operator<<(std::ostream& os, const intMatrix& M);    
    intMatrix operator<(int num);
    intMatrix operator>(int num);
    intMatrix operator >=(int num);
    intMatrix operator <=(int num);
    intMatrix operator ==(int num);
    intMatrix operator !=(int num);
    class iterator;
    iterator begin();
    iterator end();
    class const_iterator;
    const_iterator begin()const;
    const_iterator end()const;
};


class intMatrix::iterator{
    
    private:
    intMatrix* matrix;
    int index;
    
    public:
    friend class intMatrix;
    iterator (intMatrix* matrix_ptr ,int index);
    ~iterator()=default;//need to check if it free the pointer
    iterator& operator=(const iterator& i)=default;  
    int& operator*() const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& i) const;
    bool operator!=(const iterator& i) const;
};

class intMatrix::const_iterator
{
    
    private:
    const intMatrix* matrix;
    int index;

    public:
    friend class intMatrix;
    const_iterator(const intMatrix* matrix_ptr, int index);
    ~const_iterator()=default;
    const_iterator& operator=(const const_iterator& i)=default;
    const int operator*()const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& i)const;
    bool operator!=(const const_iterator& i)const;

};
}
#endif
