#pragma once
#include "../../../includes/Lab2/utmatrix.h"
#include <stdexcept>

namespace utmatrix_detail {
    inline int CheckMatrixSize(int s) {
        if (s <= 0)
            throw std::invalid_argument("Размер матрицы не может быть отрицательным");
        if (s > MAX_MATRIX_SIZE)
            throw std::invalid_argument("Размер матрицы превышает MAX_MATRIX_SIZE");
        return s;
    }
}
template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s <= 0)
        throw std::invalid_argument("Размер вектора не может быть отрицательным");
    if (s > MAX_VECTOR_SIZE)
        throw std::invalid_argument("Размер вектора превышает MAX_VECTOR_SIZE");
    if (si < 0 || si > s)
        throw std::invalid_argument("Начальный индекс должен быть в диапазоне [0, Size]");
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
    pVector = nullptr;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < StartIndex || pos >= Size)
        throw std::out_of_range("Индекс выходит за границы вектора");
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= Size)
        throw std::out_of_range("Индекс выходит за границы вектора");
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (this == &v)
        return true;
    if (Size != v.Size || StartIndex != v.StartIndex)
        return false;

    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
    {
        if (!(pVector[i] == v.pVector[i]))
            return false;
    }
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (this == &v)
        return *this;

    if (Size == v.Size && StartIndex == v.StartIndex)
    {
        const int n = Size - StartIndex;
        for (int i = 0; i < n; ++i)
            pVector[i] = v.pVector[i];
    }
    else
    {
        TVector tmp(v);
        std::swap(Size, tmp.Size);
        std::swap(StartIndex, tmp.StartIndex);
        std::swap(pVector, tmp.pVector);
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector res(*this);
    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
        res.pVector[i] = pVector[i] + val;
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector res(*this);
    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
        res.pVector[i] = pVector[i] - val;
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector res(*this);
    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
        res.pVector[i] = pVector[i] * val;
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size)
        throw std::invalid_argument("Векторы имеют разные размеры");
    if (StartIndex != v.StartIndex)
        throw std::invalid_argument("Векторы имеют разные начальные индексы");
    TVector res(*this);
    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
        res.pVector[i] = pVector[i] + v.pVector[i];
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size)
        throw std::invalid_argument("Векторы имеют разные размеры");
    if (StartIndex != v.StartIndex)
        throw std::invalid_argument("Векторы имеют разные начальные индексы");
    TVector res(*this);
    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
        res.pVector[i] = pVector[i] - v.pVector[i];
    return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size)
        throw std::invalid_argument("Векторы имеют разные размеры");
    if (StartIndex != v.StartIndex)
        throw std::invalid_argument("Векторы имеют разные начальные индексы");
    ValType res = ValType();
    const int n = Size - StartIndex;
    for (int i = 0; i < n; ++i)
        res = res + pVector[i] * v.pVector[i];
    return res;
}

template <class ValType>
TMatrix<ValType>::TMatrix(int s)
    : TVector<TVector<ValType>>(utmatrix_detail::CheckMatrixSize(s), 0)
{
    for (int i = 0; i < s; ++i)
        this->pVector[i] = TVector<ValType>(s, i);
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType>>(mt) {}

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
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt)
{
    if (this != &mt)
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