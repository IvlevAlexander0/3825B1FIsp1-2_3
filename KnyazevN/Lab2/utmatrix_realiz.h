#pragma once
#include "utmatrix.h"
#include <stdexcept>

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s < 0 || s > MAX_VECTOR_SIZE)
        throw std::out_of_range("out of range");
    if (si < 0 || si > MAX_VECTOR_SIZE)
        throw std::out_of_range("out of range");
    Size = s;
    StartIndex = si;
    if (Size > 0)
        pVector = new ValType[Size]();
    else
        pVector = nullptr;
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    if (Size > 0)
        pVector = new ValType[Size];
    else
        pVector = nullptr;
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < StartIndex || pos >= StartIndex + Size) {
        throw std::out_of_range("out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= StartIndex + Size) {
        throw std::out_of_range("out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (this == &v) {
        return true;
    }
    if (Size != v.Size || StartIndex != v.StartIndex) {
        return false;
    }
    for (int i = 0; i < Size; i++) {
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
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (this == &v) {
        return *this;
    }
    if (Size != v.Size) {
        ValType* temp;
        if (v.Size > 0) {
            temp = new ValType[v.Size];
        }
        else {
            temp = nullptr;
        }
        delete[] pVector; 
        pVector = temp;  
        Size = v.Size;
    }
    StartIndex = v.StartIndex;
    for (int i = 0; i < Size; i++) {
        pVector[i] = v.pVector[i];
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = 0; i < Size; i++)
        res.pVector[i] += val;
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = 0; i < Size; i++) {
        res.pVector[i] -= val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = 0; i < Size; i++) {
        res.pVector[i] *= val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("invalid size");
    }
    TVector<ValType> res(*this);
    for (int i = 0; i < Size; i++) {
        res.pVector[i] = res.pVector[i] + v.pVector[i];
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("invalid size");
    }
    TVector<ValType> res(*this);
    for (int i = 0; i < Size; i++) {
        res.pVector[i] = res.pVector[i] - v.pVector[i];
    }
    return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("invalid size");
    }
    ValType res = ValType(); 
    for (int i = 0; i < Size; i++) {
        res += pVector[i] * v.pVector[i];
    }
    return res;
}





template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s) {
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::out_of_range("out of range");
    }
    for (int i = 0; i < s; i++) {
        this->pVector[i] = TVector<ValType>(s - i, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const {
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const {
    return TVector<TVector<ValType>>::operator!=(mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt) {
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt) const {
    return TVector<TVector<ValType>>::operator+(mt);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt) const {
    return TVector<TVector<ValType>>::operator-(mt);
}