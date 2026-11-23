#pragma once
#include "utmatrix.h"
#include <stdexcept>



template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0 || si < 0 || si > s || s > MAX_VECTOR_SIZE)
        throw std::out_of_range("error size");

    Size = s;
    StartIndex = si;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i)
        pVector[i] = ValType{};
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos < 0 || pos >= Size)
        throw std::out_of_range("index out of range");
    return pVector[pos];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const
{
    if (pos < 0 || pos >= Size)
        throw std::out_of_range("index out of range");
    return pVector[pos];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex)
        return false;
    for (int i = 0; i < Size; ++i)
        if (pVector[i] != v.pVector[i])
            return false;
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const
{
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (this == &v)
        return *this;
    if (Size != v.Size)
    {
        delete[] pVector;
        Size = v.Size;
        pVector = new ValType[Size];
    }
    StartIndex = v.StartIndex;
    for (int i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];
    return *this;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const
{
    TVector res(*this);
    for (int i = 0; i < Size; ++i)
        res.pVector[i] += val;
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const
{
    TVector res(*this);
    for (int i = 0; i < Size; ++i)
        res.pVector[i] -= val;
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const
{
    TVector res(*this);
    for (int i = 0; i < Size; ++i)
        res.pVector[i] *= val;
    return res;
}


template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex)
        throw std::invalid_argument("error size");
    TVector res(*this);
    for (int i = 0; i < Size; ++i)
        res.pVector[i] += v.pVector[i];
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex)
        throw std::invalid_argument("error size");
    TVector res(*this);
    for (int i = 0; i < Size; ++i)
        res.pVector[i] -= v.pVector[i];
    return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex)
        throw std::invalid_argument("error size");
    ValType res = ValType{};
    for (int i = 0; i < Size; ++i)
        res += pVector[i] * v.pVector[i];
    return res;
}


template <class ValType>
TMatrix<ValType>::TMatrix(int s)
    : TVector<TVector<ValType>>(s)
{
    if (s < 0 || s > MAX_MATRIX_SIZE)
        throw std::out_of_range("TMatrix:invalid size");

    for (int i = 0; i < s; ++i)
    {
        (*this)[i] = TVector<ValType>(s, i);
    }
}



template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt)
    : TVector<TVector<ValType>>(mt)
{
}


template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt)
    : TVector<TVector<ValType>>(mt)
{
}



template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const
{
    return TVector<TVector<ValType>>::operator==(mt);
}


template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const
{
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt)
{
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}




template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const
{
    return TMatrix(TVector<TVector<ValType>>::operator+(mt));
}


template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const
{
    return TMatrix(TVector<TVector<ValType>>::operator-(mt));
}