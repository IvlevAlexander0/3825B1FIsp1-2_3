#pragma once
#include "utmatrix.h"
#include <stdexcept> //throw catch 

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s <= 0 || s > MAX_VECTOR_SIZE) {
        throw std::invalid_argument("TVector: invalid size");
    }
    if (si < 0) {
        throw std::invalid_argument("TVector: negative start index");
    }

    Size = s;
    StartIndex = si;
    pVector = new ValType[Size]();
}

template <class ValType>
TVector<ValType>::TVector(const TVector<ValType>& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
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
        throw std::out_of_range("TVector: index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= StartIndex + Size) {
        throw std::out_of_range("TVector: index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType>& v) {
    if (this != &v) {
        if (Size != v.Size) {
            delete[] pVector;
            pVector = new ValType[v.Size];
            Size = v.Size;
        }
        StartIndex = v.StartIndex;
        for (int i = 0; i < Size; i++) {
            pVector[i] = v.pVector[i];
        }
    }
    return *this;
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& v) const {
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
bool TVector<ValType>::operator!=(const TVector<ValType>& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector<ValType> result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] + val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector<ValType> result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] - val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector<ValType> result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] * val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("TVector: vectors have different size or start index");
    }
    TVector<ValType> result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] + v.pVector[i];
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("TVector: vectors have different size or start index");
    }
    TVector<ValType> result(Size, StartIndex);
    for (int i = 0; i < Size; i++) {
        result.pVector[i] = pVector[i] - v.pVector[i];
    }
    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("TVector: vectors have different size or start index");
    }
    ValType result = ValType();
    for (int i = 0; i < Size; i++) {
        result += pVector[i] * v.pVector[i];
    }
    return result;
}


//TMatrix

inline int check_matrix_size(int size) { //вспомогательная функция для проверки размера матрицы
    if (size <= 0 || size > MAX_MATRIX_SIZE) {
        throw std::invalid_argument("TMatrix: invalid size");
    }
    return size;
}

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(check_matrix_size(s)) {
    for (int i = 0; i < this->Size; i++) {
        this->pVector[i] = TVector<ValType>(this->Size - i, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType>>(mt) {
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {
}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const {
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const {
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt) {
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("TMatrix: matrices have different size");
    }
    return TMatrix<ValType>(TVector<TVector<ValType>>::operator+(mt));
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("TMatrix: matrices have different size");
    }
    return TMatrix<ValType>(TVector<TVector<ValType>>::operator-(mt));
}