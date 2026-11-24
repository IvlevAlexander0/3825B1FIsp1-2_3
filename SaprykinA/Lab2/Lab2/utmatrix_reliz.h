#pragma once

#include <iostream>
#include <stdexcept> 

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
    int Size;      
    int StartIndex; 
    ValType* pVector;
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);          
    ~TVector();
    int GetSize() const { return Size; }
    int GetStartIndex() const { return StartIndex; }
    ValType& operator[](int pos);
    const ValType& operator[](int pos) const;
    bool operator==(const TVector& v) const;
    bool operator!=(const TVector& v) const;
    TVector& operator=(const TVector& v);

    TVector operator+(const ValType& val) const;
    TVector operator-(const ValType& val) const;
    TVector operator*(const ValType& val) const;

    TVector operator+(const TVector& v) const;
    TVector operator-(const TVector& v) const;
    ValType operator*(const TVector& v) const;

    friend std::istream& operator>>(std::istream& in, TVector& v) {
        int size = v.GetSize();
        int startIndex = v.GetStartIndex();
        TVector tmp(size, startIndex);
        for (int i = startIndex; i < size; ++i) {
            in >> tmp[i];
        }
        if (!in.fail()) {
            v = tmp;
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const TVector& v) {
        for (int i = 0; i < v.GetSize(); ++i) {
            if (i > 0) out << ' ';
            if (i < v.GetStartIndex()) out << ValType{};
            else out << v[i];
        }
        return out;
    }
};

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    
    TMatrix(const TVector<TVector<ValType>>& mt);  
    bool operator==(const TMatrix& mt) const;
    bool operator!=(const TMatrix& mt) const;
    TMatrix& operator= (const TMatrix& mt);
    TMatrix operator+ (const TMatrix& mt) const;
    TMatrix operator- (const TMatrix& mt) const;

    friend std::istream& operator>>(std::istream& in, TMatrix& mt) {
        int size = mt.GetSize();
        TMatrix tmp(size);
        for (int i = 0; i < size; ++i) {
            in >> tmp[i];
        }
        if (!in.fail()) {
            mt = tmp;
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt) {
        for (int i = 0; i < mt.GetSize(); ++i) {
            if (i > 0) out << '\n';
            out << mt[i];
        }
        return out;
    }
};

// TVector

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s < 0 || si < 0 || si > s || s > MAX_VECTOR_SIZE) {
        throw std::invalid_argument("Invalid vector size or start index");
    }
    Size = s;
    StartIndex = si;
    pVector = new ValType[Size - StartIndex](); 
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size - StartIndex];
    for (int i = 0; i < Size - StartIndex; ++i) {
        pVector[i] = v.pVector[i];
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) return false;
    for (int i = 0; i < Size - StartIndex; ++i) {
        if (pVector[i] != v.pVector[i]) return false;
    }
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (this == &v) return *this; 
    delete[] pVector;
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size - StartIndex];
    for (int i = 0; i < Size - StartIndex; ++i) {
        pVector[i] = v.pVector[i];
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector res(*this);
    for (int i = 0; i < Size - StartIndex; ++i) {
        res.pVector[i] += val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector res(*this);
    for (int i = 0; i < Size - StartIndex; ++i) {
        res.pVector[i] -= val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector res(*this);
    for (int i = 0; i < Size - StartIndex; ++i) {
        res.pVector[i] *= val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Vectors sizes or start indices do not match");
    }
    TVector res(*this);
    for (int i = 0; i < Size - StartIndex; ++i) {
        res.pVector[i] += v.pVector[i];
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Vectors sizes or start indices do not match");
    }
    TVector res(*this);
    for (int i = 0; i < Size - StartIndex; ++i) {
        res.pVector[i] -= v.pVector[i];
    }
    return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Vectors sizes or start indices do not match");
    }
    ValType res = 0;
    for (int i = 0; i < Size - StartIndex; ++i) {
        res += pVector[i] * v.pVector[i];
    }
    return res;
}

// TMatrix

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0) {
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::invalid_argument("Invalid matrix size");
    }
    for (int i = 0; i < s; ++i) {
        (*this)[i] = TVector<ValType>(s, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("Matrix sizes do not match");
    }
    TMatrix res(*this);
    for (int i = 0; i < this->Size; ++i) {
        res[i] = (*this)[i] + mt[i];
    }
    return res;
}
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("Matrix sizes do not match");
    }
    TMatrix res(*this);
    for (int i = 0; i < this->Size; ++i) {
        res[i] = (*this)[i] - mt[i];
    }
    return res;
}