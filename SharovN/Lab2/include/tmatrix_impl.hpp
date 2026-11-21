#pragma once

#include <algorithm>
#include <stdexcept>
#include <utility>

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
    if (s <= 0 || s > MAX_VECTOR_SIZE) {
        throw std::invalid_argument("Invalid vector size");
    }
    if (si < 0 || si >= s) {
        throw std::invalid_argument("Invalid vector start index");
    }

    pVector = new ValType[Size - StartIndex]{};
}

template <class ValType>
TVector<ValType>::TVector(const TVector &v) : TVector(v.Size, v.StartIndex)
{
    std::copy_n(v.pVector, Size - StartIndex, pVector);
}

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Vector index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const
{
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Vector index out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector &v) const
{
    return Size == v.Size && StartIndex == v.StartIndex &&
           std::equal(pVector, pVector + (Size - StartIndex), v.pVector);
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this != &v) {
        TVector copy(v);
        std::swap(Size, copy.Size);
        std::swap(StartIndex, copy.StartIndex);
        std::swap(pVector, copy.pVector);
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType &val) const
{
    TVector result(Size, StartIndex);
    for (int i = StartIndex; i < Size; ++i) {
        result[i] = (*this)[i] + val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType &val) const
{
    TVector result(Size, StartIndex);
    for (int i = StartIndex; i < Size; ++i) {
        result[i] = (*this)[i] - val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType &val) const
{
    TVector result(Size, StartIndex);
    for (int i = StartIndex; i < Size; ++i) {
        result[i] = (*this)[i] * val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector &v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Incompatible vectors");
    }
    TVector result(Size, StartIndex);
    for (int i = StartIndex; i < Size; ++i) {
        result[i] = (*this)[i] + v[i];
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector &v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Incompatible vectors");
    }
    TVector result(Size, StartIndex);
    for (int i = StartIndex; i < Size; ++i) {
        result[i] = (*this)[i] - v[i];
    }
    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector &v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Incompatible vectors");
    }
    ValType result{};
    for (int i = StartIndex; i < Size; ++i) {
        result = result + (*this)[i] * v[i];
    }
    return result;
}

template <class ValType>
TMatrix<ValType>::TMatrix(int s)
    : TVector<TVector<ValType>>(
          s > MAX_MATRIX_SIZE ? throw std::invalid_argument("Invalid matrix size") : s)
{
    for (int i = 0; i < s; ++i) {
        this->pVector[i] = TVector<ValType>(s, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix &mt) : TVector<TVector<ValType>>(mt)
{
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>> &mt)
    : TVector<TVector<ValType>>(mt)
{
    const int size = this->Size;
    if (size > MAX_MATRIX_SIZE || this->StartIndex != 0) {
        throw std::invalid_argument("Invalid matrix dimensions");
    }
    for (int i = 0; i < size; ++i) {
        const auto& row = this->pVector[i];
        if (row.GetSize() != size || row.GetStartIndex() != i) {
            throw std::invalid_argument("Invalid triangular matrix row");
        }
    }
}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix &mt) const
{
    return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix &mt) const
{
    return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix &mt)
{
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix &mt) const
{
    return TMatrix(TVector<TVector<ValType>>::operator+(mt));
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix &mt) const
{
    return TMatrix(TVector<TVector<ValType>>::operator-(mt));
}
