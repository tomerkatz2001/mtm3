
#include "mypart.h"
#include <stdlib.h>
#include <assert.h>

using namespace mtm;
enum operations {bigger,smaller,big_equal,small_equal,equal,not_equal};

    intMatrix::intMatrix(const intMatrix& M)//copy constarctor
    {   this->dim=M.dim;
        matrix=new int*[dim.getCol()];
        for(int j=0;j<dim.getCol();j++)
        {
            matrix[j]=new int[dim.getRow()];
            for(int i=0;i<dim.getRow();i++)
            {
                this->matrix[i][j]=M.matrix[i][j];//copy M(i,j) to the new matrix
            }
        }
    }    
    intMatrix::~intMatrix()
    {
     for(int j=0;j<dim.getCol();j++)
        {
            delete matrix[j];
        }
        delete matrix;
    }
    int intMatrix::size() const
    {
        return dim.getCol()*dim.getRow();
    }
        intMatrix&  intMatrix::operator =(const intMatrix& M)
        { 
        //using exceptions I can add beckup matrix before delete the matrix, incase the alloc fail.
        for(int j=0;j<dim.getCol();j++)
        {
            delete matrix[j];
        }
        delete matrix;
        dim=M.dim;
        matrix = new int*[dim.getCol()];
        for(int j=0;j<dim.getCol();j++)
        {
            matrix[j]=new int[dim.getRow()];
            for(int i=0;i<dim.getRow();i++)
            {
                this->matrix[i][j]=M.matrix[i][j];//copy M(i,j) to the new matrix
            }
        }
        return *this;
    } 
        int intMatrix::height() const
    {
            return this->dim.getRow();
    }
        int intMatrix::width() const
    {
        return dim.getCol();
    }
    intMatrix& intMatrix::operator+=(const intMatrix& M)//used for the + operator.
    {
        //assert(m==M.m&&n==M.n);
        for (int j=0;j<dim.getCol();j++)
        {
            for(int i=0;i<dim.getRow();i++)
            {
                matrix[i][j]+=M.matrix[i][j];
            }
        }
        return *this;
    }
    intMatrix operator+(const intMatrix& M1, const intMatrix& M2)
{
    intMatrix M3=M1;
    return M3+=M2;
}
    std::ostream& mtm::operator<<(std::ostream& os, const intMatrix& M)
{
    
    int* sliced_matrix=new int[M.size()];
    int pointer=0;
    for (int i=0;i<M.height();i++)
    {
        for (int j=0;j<M.width();j++)
        {       
            sliced_matrix[pointer++]=M(i,j);
        }
    }
    os<<printMatrix(sliced_matrix, M.dim);
    return os;
}    
    static intMatrix makeCompare(const intMatrix& M,enum operations what_to_do, int num)
{
    Dimensions new_dim(M.height(),M.width());
      intMatrix M1(new_dim);
        for(int j=0;j<M.width();j++)
        {
            for(int i=0;i<M.height();i++)
            {
               if(what_to_do==operations::bigger)//need to check if it works!!!
               {
                   if(M(i,j)>num)
                   {
                       M1(i,j)=1;
                   }
                   continue;
               }
               if(what_to_do==operations::smaller)
               {
                   if(M(i,j)<num)
                   {
                       M1(i,j)=1;
                   }
                   continue;
               }
               if(what_to_do==operations::big_equal)
               {
                   if(M(i,j)>=num)
                   {
                       M1(i,j)=1;
                   }
                   continue;
               }
               if(what_to_do==operations::small_equal)
               {
                   if(M(i,j)<=num)
                   {
                       M1(i,j)=1;
                   }
                   continue;
               }
               if(what_to_do==operations::equal)
               {
                   if(M(i,j)==num)
                   {
                       M1(i,j)=1;
                   }
                    continue;
               }
               if(what_to_do==operations::not_equal)
               {
                   if(M(i,j)!=num)
                   {
                       M1(i,j)=1;
                   }
               }
            }
        }
        return M1;
    } 
    intMatrix  intMatrix::operator<(int num)
    {
        return makeCompare(*this,operations::smaller,num);
    }
    intMatrix intMatrix::operator>(int num)
    {
        return makeCompare(*this,operations::bigger,num);
    }
    intMatrix intMatrix::operator >=(int num)
    {
        return makeCompare(*this, operations::big_equal,num);
    }
    intMatrix intMatrix::operator <=(int num)
    {
        return makeCompare(*this,operations::small_equal,num);
    }
    intMatrix intMatrix::operator ==(int num)
    {
        return makeCompare(*this,operations::equal, num);
    }
    intMatrix intMatrix::operator !=(int num)
    {
        return makeCompare(*this,operations::not_equal,num);
    }
    


intMatrix::iterator::iterator(intMatrix* matrix_ptr,int index)
{
    matrix=matrix_ptr;
    this->index=index;
}
bool intMatrix::iterator::operator==(const iterator&i) const
{
    assert (i.matrix==this->matrix);
    return (this->index==i.index);
}
bool intMatrix::iterator::operator!=(const iterator& i) const
{
    return !(*this==i);
}
intMatrix::iterator& intMatrix::iterator::operator++()
{
    ++index;
    return *this;
}
intMatrix::iterator intMatrix::iterator::operator++(int)
{
    intMatrix::iterator result=*this;
    ++*this;
    return result;
}
int& intMatrix::iterator::operator*()const 
{
    assert(index>=0 && index<=matrix->size());
    int row=0;
    int col=index;
    while(col>=matrix->width())
    {
        row++;
        col=col-matrix->width();
    }
    return (*matrix)(row,col);
}

intMatrix::iterator intMatrix::begin() 
    {
        return iterator(this,0);
    }
intMatrix::iterator intMatrix::end()
{
    return iterator(this,this->size());
}

intMatrix::const_iterator::const_iterator(const intMatrix* matrix_ptr, int index)
{
    matrix=matrix_ptr;
    this->index=index;
}
bool intMatrix::const_iterator::operator==(const const_iterator& i)const
{
    assert(i.matrix==this->matrix);
    return (this->index==i.index);
}
bool intMatrix::const_iterator::operator!=(const const_iterator& i)const
{
    return !(*this==i);
}
intMatrix::const_iterator& intMatrix::const_iterator::operator++()
{
    ++index;
    return *this;
}
intMatrix::const_iterator intMatrix::const_iterator::operator++(int)
{
    intMatrix::const_iterator result=*this;
    ++*this;
    return result; 
}
const int intMatrix::const_iterator::operator*()const
{
    assert(index>=0 && index<=matrix->size());
    int row=0;
    int col=index;
    while(col>=matrix->width())
    {
        row++;
        col=col-matrix->width();
    }
    return (*matrix)(row,col);
}

intMatrix::const_iterator intMatrix::begin()const
{
    return const_iterator(this,0);
}
intMatrix::const_iterator intMatrix::end()const
{
    return const_iterator(this,this->size());
}







int main()
{
 const intMatrix m;
intMatrix::const_iterator i= m.begin();
i++;


return 0;

}