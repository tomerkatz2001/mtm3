#ifndef MATRIX_H
#define MATRIX_H
#include "Auxiliaries.h"
#include <assert.h>
#include <exception>

namespace mtm{

enum operations {bigger,smaller,big_equal,small_equal,equal,not_equal};



template<class T>
class Matrix
{
    private:
    T** matrix;
    mtm::Dimensions dim; 
    public:
    
    class Exception : public std::exception{};
    class AccessIllegalElement:public Exception 
    {
        public:
	    const char* what() const throw ()
        {
    	return "Mtm matrix error: An attempt to access an illegal element ";
        }
    };
    class IllegalInitialization : public Exception
    {
        public:
	    const char * what () const throw ()
    {
    	return "Mtm matrix error: Illegal initialization values";
    }
    };
    class DimensionMismatch : public Exception
    {
    Dimensions dim_left;
    Dimensions dim_right;
    public:
    DimensionMismatch(Dimensions dim1,Dimensions dim2):dim_left(dim1),dim_right(dim2){}
	const char * what () const throw ()
    {
        std::string left_str=dim_left.Dimensions::toString();
        std::string right_str=dim_right.Dimensions::toString();
        std::string result="Mtm matrix error: Dimension mismatch: ";
        result.std::string::append(left_str);
        result.std::string::append(" ");
        result.std::string::append(right_str);
    	return result.c_str();
    }
    };
    explicit Matrix(const Dimensions& dimensions,const T& val=T());
    ~Matrix();
    Matrix(const Matrix& matrix1);//copy constractor
    Matrix& operator=(const Matrix& matrix1);//assignment operator
    static Matrix Diagonal(const int dimension,const T& val);
    int height() const;
    int width()const;
    int size()const;
    Matrix& operator +=(const Matrix& matrix1);//used for the + operator(for two matrix)
    Matrix operator+(const T& scalar)const;
    Matrix& operator+=(const T& scalar);
    //friend std::ostream& operator<<(std::ostream& os ,const Matrix& matrix);
    Matrix transpose();
    Matrix operator-() const;
    T operator()(const int i,const int j)const;
    T& operator()(const int i,const int j);
    
    Matrix<bool> operator<(const T& parameter)const;
    Matrix<bool> operator>(const T& parameter)const;
    Matrix<bool> operator>=(const T& parameter)const;
    Matrix<bool> operator<=(const T& parameter)const;
    Matrix<bool> operator==(const T& parameter)const;
    Matrix<bool> operator!=(const T& parameter)const;
    template<class F>
    Matrix<T> apply(F function)const;

    class iterator;
    iterator begin();
    iterator end();

    class const_iterator;
    const_iterator begin()const;
    const_iterator end()const;

};


//______________________________________________declarations:________________________________________________
template<class T>
Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

template<class T>
Matrix<T> operator+(const Matrix<T>& matrix1,const Matrix<T>& matrix2);

template<class T>
static  Matrix<bool> makeCompare(const Matrix<T>& M,enum operations what_to_do, T parameter);

template<class T>
bool all(const Matrix<T> mat);

template<class T>
bool any(const Matrix<T> mat);



//__________________________________________member_functions:____________________________________________


template<class T>
Matrix<T>::Matrix(const Dimensions& dimensions,const T& val):dim(dimensions.getRow(),dimensions.getCol())
{
    if(dimensions.getRow()<0 || dimensions.getCol()<0)
    {
        throw Matrix::IllegalInitialization();
    }
    matrix=new T*[dimensions.getRow()];
    for(int i=0;i<dimensions.getRow();i++)
    {
        matrix[i]=new T[dimensions.getCol()];
        for(int j=0;j<dimensions.getCol();j++)
        {
            this->matrix[i][j]=val;
        }    
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    for (int i=0;i<this->dim.getRow();i++)
    {
        delete matrix[i];
        matrix[i]=NULL;
    }
    delete matrix;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& matrix1):dim(matrix1.height(),matrix1.width())
{   
    matrix=new T*[matrix1.height()];
    for (int i=0;i<matrix1.height();i++)
    {
        matrix[i]=new T[matrix1.width()];
        for (int j=0; j<matrix1.width();j++)
        {
            matrix[i][j]=matrix1(i,j);
        }
    }
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix1)
{
    if(this==&matrix1)//If i get the same matrix
    {
        return *this;
    }
    for(int i=0;i<matrix1.height();i++)
    {
        delete matrix[i];
    }
    delete matrix;
    dim=matrix1.dim;
    for(int i=0;i<matrix1.height();i++)
    {
        matrix[i]=new T[matrix1.width()];
        for(int j=0;j<matrix1.width();j++)
        {
            matrix[i][j]=matrix1(i,j);
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::Diagonal(const int dimention, const T& val)
{
    if(dimention<=0)
    {
        throw(Matrix::IllegalInitialization());
    }
    Dimensions dim(dimention,dimention);
    Matrix<T> diagonal(dim);
    for(int i=0; i<dimention;i++)
    {
        diagonal(i,i)=val;
    }
    return diagonal;
}

template<class T>
int Matrix<T>::height()const
{
    return dim.getRow();
}

template<class T>
int Matrix<T>::width()const
{
    return dim.getCol();
}

template<class T>
int Matrix<T>::size()const
{
    return dim.getCol()*dim.getRow();
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix1)
{
if(dim.getCol()!=matrix1.width()||dim.getRow()!=matrix1.height())
{
    throw (Matrix<T>::DimensionMismatch(this->dim,matrix1.dim));
}

    for(int i=0;i<dim.getRow();i++)
    {   
        for(int j=0;j<dim.getCol();j++)
        {
            matrix[i][j]+=matrix1(i,j);
        }
    }
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::transpose()
{
    Dimensions dim(this->height(),this->width());
    Matrix<T> trans(dim);
    for(int i=0;i<dim.getRow();i++){
        for(int j=0;j<dim.getCol();j++){
            trans.matrix[i][j]=this->matrix[j][i];
        }    
    }
    return trans;
}

template<class T>
Matrix<T> Matrix<T>::operator-()const
{
    Matrix<T> mat(*this);//copy the matrix
    for(int i=0;i<this->height();i++){
        for(int j=0;j<this->width();j++){
            this->matrix[i][j]=-this->matrix[i][j];
        }    
    }
    return mat;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const T& scalar) const
{
    Dimensions dim(*this.width(),*this.height());
    Matrix mat(dim,scalar);
    mat= mat+*this;
    return mat;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const T& scalar){
    Dimensions dim(this->width(),this->height());
    Matrix mat(dim,scalar);
    *this= mat+*this;
    return *this;
}

template<class T>
T Matrix<T>::operator()(const int i, const int j)const
{
    if(i<0 || j<0||j>=(*this).width()||i>=(*this).height()){
        throw Matrix::AccessIllegalElement();
    }
    return this->matrix[i][j];
}

template<class T>
T& Matrix<T>::operator()(const int i,const int j){
    if(i<0 || j<0||j>=(*this).width()||i>=(*this).height()){
        throw Matrix::AccessIllegalElement();
    }
    return this->matrix[i][j];
}

template<class T>
Matrix<bool> Matrix<T>::operator<(const T& parameter)const
{
    return makeCompare(*this,operations::smaller,parameter);
}

template <class T>
Matrix<bool> Matrix<T>::operator>(const T& parameter)const
{
    return makeCompare(*this,operations::bigger,parameter);
}

template<class T>
Matrix<bool> Matrix<T>::operator>=(const T& parameter)const
{
    return makeCompare(*this,operations::big_equal,parameter);
}

template<class T>
Matrix<bool> Matrix<T>::operator<=(const T& parameter)const
{
    return makeCompare(*this,operations::small_equal,parameter);
}

template<class T>
Matrix<bool> Matrix<T>::operator==(const T& parameter)const
{
    return makeCompare(*this,operations::equal,parameter);
}

template<class T>
Matrix<bool> Matrix<T>::operator!=(const T& parameter)const
{
    return makeCompare(*this,operations::not_equal,parameter);
}

template<class T>
template<class F>
Matrix<T> Matrix<T>::apply(F function)const
{
    Matrix<T> result(*this);
    for(int i=0;i<result.height();i++)
    {
        for(int j=0;j<result.width();j++)
        {
            result(i,j)=function(result(i,j));
        }
    }
    return result;
}
//_______________________________________not_member_and_symmetric_functions:__________________________________

template<class T>
Matrix<T> operator+(const Matrix<T>& matrix1,const Matrix<T>& matrix2)
{
    if(matrix2.width()!=matrix1.width()||matrix2.height()!=matrix1.height())
{
    Dimensions dim1(matrix1.height(),matrix1.width());
    Dimensions dim2 (matrix2.height(),matrix2.width());
    throw (typename Matrix<T>::DimensionMismatch (dim1,dim2));
}
    Matrix<T> matrix3=matrix1;
    return matrix3+=matrix2;
}

template<class T>
Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
{
    Matrix<T> temp=-matrix2;
    return matrix1+temp;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
   return printMatrix(os,matrix.begin() ,matrix.end() ,matrix.width());
}

template<class T>
bool all(const Matrix<T> mat){
    bool flag=true;
    for(int i=0;i<mat.width();i++){
        for(int j=0;j<mat.height();j++){
            if(!bool(mat(i,j))){
                flag=false;
            }
        }    
    }
    return flag;
}

template<class T>
bool any(const Matrix<T> mat)
{
    bool flag=false;
    for(int i=0;i<mat.width();i++){
        for(int j=0;j<mat.height();j++){
            if(bool(mat(i,j))){
                flag=true;
            }
        }    
    }
    return flag;
}

//______________________________________________iterators_functions_______________________________________________



//*ordenery_iterator:
template<class T>
class Matrix<T>::iterator
{
    Matrix<T>* matrix_ptr;
    int index;
    public:
    friend Matrix<T>;
    iterator(Matrix<T>* matrix1_ptr,const int index);
    ~iterator()=default;
    iterator& operator=(const iterator& i)=default;
    T& operator*()const;
    iterator& operator++();
    iterator operator++(int);
    bool operator==(const iterator& i) const;
    bool operator!=(const iterator& i) const;
};

template<class T>
Matrix<T>::iterator::iterator(Matrix<T>* matrix1_ptr,const int index)
{
    matrix_ptr=matrix1_ptr;
    this->index=index;
}

template<class T>
T& Matrix<T>::iterator::operator*()const
{
    if(this->index<0||this->index>=(this->matrix_ptr->size()))//if you try to access unvalid index
    {
        throw Matrix<T>::AccessIllegalElement();
    }
    int row=0;
    int col=index;
    while(col>=matrix_ptr->width())
    {
        row++;
        col=col-matrix_ptr->width();
    }
    return (*matrix_ptr)(row,col);
}

template<class T>
typename Matrix<T>::iterator& Matrix<T>::iterator::operator++()
{
    ++index;
    return *this;
}

template<class T>
typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int)
{
    Matrix<T>::iterator temp_iterator(*this);//make a copy of the iterator
    ++index;
    return temp_iterator;
}

template<class T>
bool Matrix<T>::iterator::operator==(const Matrix<T>::iterator& i)const
{
    assert(i.matrix_ptr==this->matrix_ptr);//both iterator point the same matrix
    return (this->index==i.index);   
}

template<class T>
bool Matrix<T>::iterator::operator!=(const Matrix<T>::iterator& i)const
{
     return !(*this==i);
}

template<class T>
typename Matrix<T>::iterator Matrix<T>::begin()
{
    return Matrix<T>::iterator (this,0);
}

template<class T>
typename Matrix<T>::iterator Matrix<T>::end()
{
    return Matrix<T>::iterator (this,this->size());
}

//const_iterator:_________
template<class T>
class Matrix<T>::const_iterator
{
    const Matrix<T>* matrix_ptr;
    int index; 
    public:
    friend class Matrix<T>;
    const_iterator(const Matrix<T>* matrix1_ptr, const int index);
    ~const_iterator()=default;
    const_iterator& operator=(const const_iterator& i)=default;
    T operator*()const;
    const_iterator& operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator& i)const;
    bool operator!=(const const_iterator& i)const;  
};

template<class T>
Matrix<T>::const_iterator::const_iterator(const Matrix<T>* matrix1_ptr, const int index)
{
    matrix_ptr=matrix1_ptr;
    this->index=index;
}

template<class T>
T Matrix<T>::const_iterator::operator*()const
{
    if(this->index<0||this->index>=this->matrix_ptr->size())//if you try to access unvalid index
    {
        throw Matrix<T>::AccessIllegalElement();
    }
    int row=0;
    int col=index;
    while(col>=matrix_ptr->width())
    {
        row++;
        col=col-matrix_ptr->width();
    }
    return (*matrix_ptr)(row,col);
}

template<class T>
typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++()
{
    ++index;
    return *this;
} 

template<class T>
typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int)
{
    Matrix<T>::const_iterator temp(*this);//make a copy of the iterator
    ++index;
    return temp;
}

template<class T>
bool Matrix<T>::const_iterator::operator==(const Matrix<T>::const_iterator& i)const
{
    assert(i.matrix_ptr==this->matrix_ptr);//both iterator point the same matrix
    return (this->index==i.index);   
}

template<class T>
bool Matrix<T>::const_iterator::operator!=(const Matrix<T>::const_iterator& i)const
{
return !(*this==i);
}

template<class T>
typename Matrix<T>::const_iterator Matrix<T>::begin()const
{
    return Matrix<T>::const_iterator(this,0);
}

template<class T>
typename Matrix<T>::const_iterator Matrix<T>::end()const
{
    return Matrix<T>::const_iterator(this,this->size());
}

//_________________________________________________help_functions____________________________________________
template<class T>
 static Matrix<bool>  makeCompare(const Matrix<T>& matrix,enum operations what_to_do, T parameter)
{
     Dimensions new_dim(matrix.height(),matrix.width());
      Matrix<bool> matrix1(new_dim,false);
        for(int i=0;i<matrix.height();i++)
        {
            for(int j=0;j<matrix.width();j++)
            {
               if(what_to_do==operations::bigger)
               {
                   if(matrix(i,j)>parameter)
                   {
                       matrix1(i,j)=true;
                   }
                   continue;
               }
               if(what_to_do==operations::smaller)
               {
                   if(matrix(i,j)<parameter)
                   {
                       matrix1(i,j)=true;
                   }
                   continue;
               }
               if(what_to_do==operations::big_equal)
               {
                   if(matrix(i,j)>=parameter)
                   {
                       matrix1(i,j)=true;
                   }
                   continue;
               }
               if(what_to_do==operations::small_equal)
               {
                   if(matrix(i,j)<=parameter)
                   {
                       matrix1(i,j)=true;
                   }
                   continue;
               }
               if(what_to_do==operations::equal)
               {
                   if(matrix(i,j)==parameter)
                   {
                       matrix1(i,j)=true;
                   }
                    continue;
               }
               if(what_to_do==operations::not_equal)
               {
                   if(matrix(i,j)!=parameter)
                   {
                       matrix1(i,j)=true;
                   }
               }
            }
        }
        return matrix1;
}

}
#endif
