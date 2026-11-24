#include "../../includes/Lab2/utmatrix.h" 
#include <stdexcept>

//конструктор с параметрами
template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    //проверяем, что размер неотрицательный и не превышает максимум
    if (s < 0 || s > MAX_VECTOR_SIZE) {
        throw std::out_of_range("Nedopust size vector");
    }
    //проверяем, что начальный индекс в пределах размера
    if (si < 0 || si > s) {
        throw std::out_of_range("Nedopust start index");
    }

    Size = s;               
    StartIndex = si;        
    pVector = new ValType[Size]; 

    //обнуляем весь массив (ValType{} создаст 0 для чисел)
    for (int i = 0; i < Size; ++i) {
        pVector[i] = ValType{};
    }
}

//конструктор копирования
template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;               
    StartIndex = v.StartIndex;   
    pVector = new ValType[Size]; 

    for (int i = 0; i < Size; ++i) {
        pVector[i] = v.pVector[i];
    }
}

//деструктор
template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector; 
    pVector = nullptr; 
}

//оператор доступа
template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    //проверяем, что индекс не меньше StartIndex и не больше Size-1
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Index go out in gran vector");
    }
    return pVector[pos]; 
}

//оператор доступа 
template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Индекс выходит за границы вектора");
    }
    return pVector[pos];
}


template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
   
    if (this == &v) {
        return *this;
    }

   
    if (Size != v.Size) {
        delete[] pVector;
        Size = v.Size;
        pVector = new ValType[Size];
    }

  
    StartIndex = v.StartIndex;
    for (int i = 0; i < Size; ++i) {
        pVector[i] = v.pVector[i];
    }

    return *this;
}


template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    
    if (Size != v.Size || StartIndex != v.StartIndex) {
        return false;
    }
    
    for (int i = StartIndex; i < Size; ++i) {
        if (pVector[i] != v.pVector[i]) {
            return false;
        }
    }
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector<ValType> res(*this); 
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] + val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] - val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] * val;
    }
    return res;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("size not ravn");
    }
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] + v.pVector[i];
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("size not ravn");
    }
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] - v.pVector[i];
    }
    return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("size not ravn");
    }
    ValType result = ValType{}; 
    for (int i = StartIndex; i < Size; ++i) {
        result = result + (pVector[i] * v.pVector[i]);
    }
    return result;
}


template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0) {
    
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::out_of_range("size not ravn");
    }

    for (int i = 0; i < s; ++i) {
        this->pVector[i] = TVector<ValType>(s, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("size not ravn");
    }
    TMatrix<ValType> res(this->Size);
    for (int i = 0; i < this->Size; ++i) {
        res.pVector[i] = this->pVector[i] + mt.pVector[i];
    }

    return res;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("size not ravn");
    }

    TMatrix<ValType> res(this->Size);
    for (int i = 0; i < this->Size; ++i) {
        res.pVector[i] = this->pVector[i] - mt.pVector[i];
    }

    return res;
}