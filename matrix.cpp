class IntMatrix{
    int[][] matrix;
    public:
    IntMatrix(Dimensions dimensions);
    IntMatrix& IntMatrix::Identity(int size);
    IntMatrix& IntMatrix::Transpose();
    IntMatrix operator-() const;
    IntMatrix& IntMatrix::operator+=(int scalar);
    IntMatrix operator+(Int scalar);
    int& IntMatrix::operator()(int i,int j);

};

IntMatrix::IntMatrix(Dimensions dimensions,int val){
    this->matrix= new int[dimensions.getRow()][dimensions.getCol()];
    for(int i=0;i<dimensions.getRow();i++){
        for(int j=0;j<dimensions.getCol();j++){
            this->matrix[i][j]=val;
        }    
    }
}
IntMatrix& IntMatrix::Identity(int size){
    Dimensions dim(size,size);
    IntMatrix I(dim);
    for(int i=0;i<size;i++){
            this->matrix[i][i]=1;    
    }
    return I;
 }

IntMatrix& IntMatrix::Transpose(){
    Dimensions dim(*this.height(),*this.width());
    IntMatrix t(dim);
    for(int i=0;i<dim.getRow();i++){
        for(int j=0;j<dim.getCol();j++){
            t.matrix[i][j]=this->matrix[j][i]=val;
        }    
    }
    return t;
}
IntMatrix IntMatrix::operator-(){
    IntMatrix mat(*this);
    for(int i=0;i<*this.width();i++){
        for(int j=0;j<*this.height();j++){
            this->matrix[i][j]=-this->matrix[i][j];
        }    
    }
    return mat;
}
IntMatrix IntMatrix::operator+(int scalar){
    Dimensions dim(*this.width(),*this.height());
    IntMatrix mat(dim,scalar);
    mat= mat+*this;
    return mat;
}
IntMatrix& IntMatrix::operator+=(int scalar){
    Dimensions dim(*this.width(),*this.height());
    IntMatrix mat(dim,scalar);
    *this= mat+*this;
    return *this;
}
int& IntMatrix::operator()(int i,int j){
    return this->matrix[i][j];
}
int IntMatrix::operator()(int i,int j) const{
    return this->matrix[i][j];
}
bool IntMatrix::all(IntMatrix mat){
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
bool IntMatrix::any(IntMatrix mat){
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


