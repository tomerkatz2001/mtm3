
#include "IntMatrix.h"
#include <stdlib.h>
#include <assert.h>

using namespace mtm;

enum operations {bigger,smaller,big_equal,small_equal,equal,not_equal};
static IntMatrix makeCompare(const IntMatrix& M,enum operations what_to_do, int num)
{
    Dimensions new_dim(M.height(),M.width());
      IntMatrix M1(new_dim);
        for(int i=0;i<M.height();i++)
        {
            for(int j=0;j<M.width();j++)
            {
               if(what_to_do==operations::bigger)
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
 
//______________________________________member functions:_________________________________________________________
IntMatrix::IntMatrix(const Dimensions& dimensions,int val):\
dim(dimensions.getRow(),dimensions.getCol()),matrix(new int*[dimensions.getRow()])
{
    for(int i=0;i<dimensions.getRow();i++){
        matrix[i]=new int[dimensions.getCol()];
        for(int j=0;j<dimensions.getCol();j++){
            this->matrix[i][j]=val;
        }    
    }
}
IntMatrix::IntMatrix(const IntMatrix& M):dim(M.height(),M.width())//copy constarctor
    {   
        matrix=new int*[dim.getRow()];
        for(int i=0;i<dim.getRow();i++)
        {
            matrix[i]=new int[dim.getCol()];
            for(int j=0;j<dim.getCol();j++)
            {
                this->matrix[i][j]=M(i,j);//copy M(i,j) to the new matrix
            }
        }
    }    
IntMatrix::~IntMatrix()
    {
     for(int i=0;i<dim.getRow();i++)
        {
            delete matrix[i];
        }
        delete matrix;
    }
int IntMatrix::size() const
    {
        return dim.getCol()*dim.getRow();
    }
IntMatrix IntMatrix::Identity(int size)
    {
    Dimensions dim(size,size);
    IntMatrix I(dim);
    for(int i=0;i<size;i++){
            I(i,i)=1;    
    }
    return I;
    }
IntMatrix&  IntMatrix::operator =(const IntMatrix& M)
        { 
        if(this==&M)//if i get the smae matrix
        {
            return *this;
        }
        for(int i=0;i<dim.getRow();i++)
        {
            delete matrix[i];
        }
        delete matrix;
        dim=M.dim;
        matrix = new int*[dim.getRow()];
        for(int i=0;i<dim.getRow();i++)
        {
            matrix[i]=new int[dim.getCol()];
            for(int j=0;j<dim.getCol();j++)
            {
                this->matrix[i][j]=M.matrix[i][j];//copy M(i,j) to the new matrix
            }
        }
        return *this;
    } 
int IntMatrix::height() const
    {
            return this->dim.getRow();
    }
int IntMatrix::width() const
    {
        return dim.getCol();
    }
IntMatrix IntMatrix::transpose()const
   {
    Dimensions dim((*this).height(),(*this).width());
    IntMatrix t(dim);
    for(int i=0;i<dim.getRow();i++){
        for(int j=0;j<dim.getCol();j++){
            t.matrix[i][j]=this->matrix[j][i];
        }    
    }
    return t;
}
IntMatrix& IntMatrix::operator+=(const IntMatrix& M)//used for the + operator.
    {
        assert(this->height()==M.height()&&this->width()==M.width());
        for (int i=0;i<dim.getRow();i++)
        {
            for(int j=0;j<dim.getCol();j++)
            {
                matrix[i][j]+=M(i,j);
            }
        }
        return *this;
    }   
IntMatrix IntMatrix::operator-() const{
    IntMatrix matrix(*this);
    for(int i=0;i<this->height();i++){
        for(int j=0;j<this->width();j++){
            matrix(i,j)=-this->matrix[i][j];
        }    
    }
    return matrix;
}
IntMatrix IntMatrix::operator-(const IntMatrix& matrix1)const
    {
        IntMatrix temp=-matrix1;
        return (*this)+(temp);
    }
int& IntMatrix::operator()(int i,int j){
    return this->matrix[i][j];
}
IntMatrix IntMatrix::operator+(int scalar)const
{
    Dimensions dim((*this).width(),(*this).height());
    IntMatrix mat(dim,scalar);
    mat= mat+(*this);
    return mat;
}
IntMatrix& IntMatrix::operator+=(int scalar){
    Dimensions dim((*this).width(),(*this).height());
    IntMatrix mat(dim,scalar);
    *this= mat+(*this);
    return *this;
}
int IntMatrix::operator()(int i,int j) const{
    return this->matrix[i][j];
}
IntMatrix  IntMatrix::operator<(int num)
    {
        return makeCompare(*this,operations::smaller,num);
    }
IntMatrix IntMatrix::operator>(int num)
    {
        return makeCompare(*this,operations::bigger,num);
    }
IntMatrix IntMatrix::operator >=(int num)
    {
        return makeCompare(*this, operations::big_equal,num);
    }
IntMatrix IntMatrix::operator <=(int num)
    {
        return makeCompare(*this,operations::small_equal,num);
    }
IntMatrix IntMatrix::operator ==(int num)
    {
        return makeCompare(*this,operations::equal, num);
    }
IntMatrix IntMatrix::operator !=(int num)
    {
        return makeCompare(*this,operations::not_equal,num);
    }


//_____________________________friend_and_symmetric_functions:____________________________________________________
IntMatrix mtm::operator+(const IntMatrix& M1, const IntMatrix& M2)
{
    IntMatrix M3=M1;
    return M3+=M2;
} 
std::ostream& mtm::operator<<(std::ostream& os, const IntMatrix& matrix)
{
    
    int* sliced_matrix=new int[matrix.size()];
    int pointer=0;
    for (int i=0;i<matrix.height();i++)
    {
        for (int j=0;j<matrix.width();j++)
        {       
            sliced_matrix[pointer++]=matrix(i,j);
        }
    }
    os<<mtm::printMatrix(sliced_matrix, matrix.dim);
    return os;
}    
bool all(const IntMatrix mat){
    bool flag=true;
    for(int i=0;i<mat.width();i++){
        for(int j=0;j<mat.height();j++){
            if(mat(i,j)==0){
                flag=false;
            }
        }    
    }
    return flag;
}
bool any( const IntMatrix mat){
    bool flag=false;
    for(int i=0;i<mat.width();i++){
        for(int j=0;j<mat.height();j++){
            if(mat(i,j)!=0){
                flag=true;
            }
        }    
    }
    return flag;
}


//_______________________________iterator_functions:_____________________________________________________________
IntMatrix::iterator::iterator(IntMatrix* matrix_ptr,int index)
{
    matrix=matrix_ptr;
    this->index=index;
}
bool IntMatrix::iterator::operator==(const iterator&i) const
{
    assert (i.matrix==this->matrix);
    return (this->index==i.index);
}
bool IntMatrix::iterator::operator!=(const iterator& i) const
{
    return !(*this==i);
}
IntMatrix::iterator& IntMatrix::iterator::operator++()
{
    ++index;
    return *this;
}
IntMatrix::iterator IntMatrix::iterator::operator++(int)
{
    IntMatrix::iterator result=*this;
    ++*this;
    return result;
}
int& IntMatrix::iterator::operator*()const 
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

IntMatrix::iterator IntMatrix::begin() 
    {
        return iterator(this,0);
    }
IntMatrix::iterator IntMatrix::end()
{
    return iterator(this,this->size());
}

IntMatrix::const_iterator::const_iterator(const IntMatrix* matrix_ptr, int index)
{
    matrix=matrix_ptr;
    this->index=index;
}
bool IntMatrix::const_iterator::operator==(const const_iterator& i)const
{
    assert(i.matrix==this->matrix);
    return (this->index==i.index);
}
bool IntMatrix::const_iterator::operator!=(const const_iterator& i)const
{
    return !(*this==i);
}
IntMatrix::const_iterator& IntMatrix::const_iterator::operator++()
{
    ++index;
    return *this;
}
IntMatrix::const_iterator IntMatrix::const_iterator::operator++(int)
{
    IntMatrix::const_iterator result=*this;
    ++*this;
    return result; 
}
int IntMatrix::const_iterator::operator*()const
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

IntMatrix::const_iterator IntMatrix::begin()const
{
    return const_iterator(this,0);
}
IntMatrix::const_iterator IntMatrix::end()const
{
    return const_iterator(this,this->size());
}




