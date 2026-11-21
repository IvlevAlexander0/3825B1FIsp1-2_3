#pragma once
#include "utmatrix.h"
#include <stdexcept>

template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s < 0 || s > MAX_VECTOR_SIZE) {
        throw std::out_of_range("out of range");
    }
    if (si < 0 || (s > 0 && si >= s) || (s == 0 && si > 0)) {
        throw std::out_of_range("out of range");
    }
    Size = s;
    StartIndex = si;
    int count = Size - StartIndex;
    if (count > 0) {
        pVector = new ValType[count]();
    }
    else {
        pVector = nullptr;
    }
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    int count = Size - StartIndex;
    if (count > 0) {
        pVector = new ValType[count];
        for (int i = 0; i < count; i++) {
            pVector[i] = v.pVector[i];
        }
    }
    else {
        pVector = nullptr;
    }
}

template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= Size) {
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
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
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
    int oldCount = Size - StartIndex;
    int newCount = v.Size - v.StartIndex;
    if (oldCount != newCount) {
        ValType* temp = (newCount > 0) ? new ValType[newCount] : nullptr;
        delete[] pVector;
        pVector = temp;
    }
    Size = v.Size;
    StartIndex = v.StartIndex;
    for (int i = 0; i < newCount; i++) {
        pVector[i] = v.pVector[i];
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector<ValType> res(*this);
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
        res.pVector[i] += val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector<ValType> res(*this);
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
        res.pVector[i] -= val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector<ValType> res(*this);
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
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
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
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
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
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
    int count = Size - StartIndex;
    for (int i = 0; i < count; i++) {
        res += pVector[i] * v.pVector[i];
    }
    return res;
}

inline int check_matrix_size(int s) {
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::out_of_range("out of range");
    }
    return s;
}

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(check_matrix_size(s)) {
    for (int i = 0; i < s; i++) {
        this->pVector[i] = TVector<ValType>(s, i);
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
