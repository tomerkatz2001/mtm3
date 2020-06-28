
struct AccessIllegalElement : public std::exception
{
	const char * what () const throw ()
    {
    	return "Mtm matrix error: An attempt to access an illegal element ";
    }
}

struct IllegalInitialization : public std::exception
{
	const char * what () const throw ()
    {
    	return "Mtm matrix error: Illegal initialization values";
    }
}

struct DimensionMismatch : public std::exception
{
    int mat1_height;
    int mat1_width;
    int mat2_height;
    int mat2_width;
    DimensionMismatch(int h1,int w1,int h2, int w2){
        mat1_height=h1;
        mat1_width=w1;
        mat2_height=h2;
        mat2_width=w2;
    }
	const char * what () const throw ()
    {
    	return "Mtm matrix error: Dimension mismatch:
        (<"+mat1_height+">,<"+mat1_width">) (<"+mat2_height">,<"+mat2_width+">)";
    }
}

template<class T>
class Matrix{
    T[][] matrix;
    public:
    IntMatrix(Dimensions dimensions,T val);
    IntMatrix& IntMatrix::Identity(int size);
    IntMatrix& IntMatrix::Transpose();
    IntMatrix operator-() const;
    IntMatrix& IntMatrix::operator+=(int scalar);
    IntMatrix operator+(int scalar);
    int& IntMatrix::operator()(int i,int j);

};
template<class T>
Matrix::Matrix(Dimensions dimensions,T val){
    if(dimensions.getRow()<0 || dimensions.getCol()<0){
        throw Matrix::IllegalInitialization();
    }
    this->matrix= new int[dimensions.getRow()][dimensions.getCol()];
    for(int i=0;i<dimensions.getRow();i++){
        for(int j=0;j<dimensions.getCol();j++){
            this->matrix[i][j]=val;
        }    
    }
}

template<class T>
Matrix& Matrix::Identity(T size){
    if(dimensions.getRow()<0 || dimensions.getCol()<0){
        throw Matrix::IllegalInitialization();
    }
    Dimensions dim(size,size);
    IntMatrix I(dim,0);
    for(int i=0;i<size;i++){
            this->matrix[i][i]=1;    
    }
    return I;
 }

template<class T>
Matrix& Matrix::Transpose(){
    Dimensions dim(*this.height(),*this.width());
    IntMatrix t(dim);
    for(int i=0;i<dim.getRow();i++){
        for(int j=0;j<dim.getCol();j++){
            t.matrix[i][j]=this->matrix[j][i]=val;
        }    
    }
    return t;
}
Matrix Matrix::operator-(){
    IntMatrix mat(*this);
    for(int i=0;i<*this.width();i++){
        for(int j=0;j<*this.height();j++){
            this->matrix[i][j]=-this->matrix[i][j];
        }    
    }
    return mat;
}

template<class T>
Matrix Matrix::operator+(T scalar){
    Dimensions dim(*this.width(),*this.height());
    Matrix mat(dim,scalar);
    mat= mat+*this;
    return mat;
}
template<class T>
Matrix& Matrix::operator+=(T scalar){
    Dimensions dim(*this.width(),*this.height());
    Matrix mat(dim,scalar);
    *this= mat+*this;
    return *this;
}

template<class T>
T& Matrix::operator()(int i,int j){
    if(i<0 || j<0||i>=*this.width()||j>=*this.height()){
        throw Matrix::AccessIllegalElement();
    }
    return this->matrix[i][j];
}

template<class T>
T Matrix::operator()(int i,int j) const{
    if(i<0 || j<0||i>=*this.width()||j>=*this.height()){
        throw Matrix::AccessIllegalElement();
    }
    return this->matrix[i][j];
}

template<class T>
bool Matrix::all(Matrix mat){
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
bool Matrix::any(Matrix mat){
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


