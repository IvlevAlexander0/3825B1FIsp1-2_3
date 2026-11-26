#pragma once

#include "C:\users\yuket\source\repos\Lab1\3825B1FIsp1-2_3\includes\utmatrix.h"

#include <stdexcept>
#include <utility>

namespace utmatrix_detail {

    inline int checkedVectorLength(int size, int startIndex)
    {
        if (size < 0 || size > MAX_VECTOR_SIZE) {
            throw std::invalid_argument("Invalid vector size");
        }
        if (startIndex < 0 || startIndex > size) {
            throw std::invalid_argument("Invalid vector start index");
        }
        return size - startIndex;
    }

    inline int checkedMatrixSize(int size)
    {
        if (size < 0 || size > MAX_MATRIX_SIZE) {
            throw std::invalid_argument("Invalid matrix size");
        }
        return size;
    }

    template <class T>
    const TVector<TVector<T>>& checkedTriangularMatrix(
        const TVector<TVector<T>>& matrix)
    {
        const int n = matrix.GetSize();

        if (matrix.GetStartIndex() != 0) {
            throw std::invalid_argument("Matrix must start at index zero");
        }
        if (n < 0 || n > MAX_MATRIX_SIZE) {
            throw std::invalid_argument("Invalid matrix size");
        }

        for (int i = 0; i < n; ++i) {
            if (matrix[i].GetSize() != n || matrix[i].GetStartIndex() != i) {
                throw std::invalid_argument("Input does not have upper-triangular structure");
            }
        }
        return matrix;
    }

} // namespace utmatrix_detail

// -------------------- TVector --------------------

template <class ValType>
TVector<ValType>::TVector(int s, int si)
    : Size(s),
    StartIndex(si),
    pVector(new ValType[utmatrix_detail::checkedVectorLength(s, si)]{})
{
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v)
    : Size(v.Size),
    StartIndex(v.StartIndex),
    pVector(new ValType[Size - StartIndex]{})
{
    try {
        for (int i = 0; i < Size - StartIndex; ++i) {
            pVector[i] = v.pVector[i];
        }
    }
    catch (...) {
        delete[] pVector;
        throw;
    }
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
        throw std::out_of_range("Vector index is out of range");
    }
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const
{
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Vector index is out of range");
    }

    return pVector[pos - StartIndex];
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const
{
    TVector result(*this);
    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i] = pVector[i] * val;
    }
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Vectors must have equal size and start index");
    }

    TVector result(Size, StartIndex);
    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i] = pVector[i] + v.pVector[i];
    }
    return result;
}
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const
{
    TVector result(*this);

    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i] = pVector[i] - val;
    }

    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Vectors must have equal size and start index");
    }

    TVector result(Size, StartIndex);
    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i] = pVector[i] - v.pVector[i];
    }
    return result;
}
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const
{
    TVector result(*this);

    for (int i = 0; i < Size - StartIndex; ++i) {
        result.pVector[i] = pVector[i] + val;
    }

    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("Vectors must have equal size and start index");
    }

    ValType result{};
    for (int i = 0; i < Size - StartIndex; ++i) {
        result = result + pVector[i] * v.pVector[i];
    }
    return result;
}
template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex)
        return false;

    for (int i = 0; i < Size - StartIndex; ++i)
    {
        if (pVector[i] != v.pVector[i])
            return false;
    }

    return true;
}
template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (this == &v)
        return *this;

    ValType* newVector = new ValType[v.Size - v.StartIndex]{};

    try {
        for (int i = 0; i < v.Size - v.StartIndex; ++i) {
            newVector[i] = v.pVector[i];
        }
    }
    catch (...) {
        delete[] newVector;
        throw;
    }

    delete[] pVector;

    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = newVector;

    return *this;
}
template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const
{
    return !(*this == v);
}
// -------------------- TMatrix --------------------

template <class ValType>
TMatrix<ValType>::TMatrix(int s)
    : TVector<TVector<ValType>>(utmatrix_detail::checkedMatrixSize(s), 0)
{
    for (int i = 0; i < s; ++i) {
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
    : TVector<TVector<ValType>>(utmatrix_detail::checkedTriangularMatrix(mt))
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
    const TVector<TVector<ValType>>& left = *this;
    const TVector<TVector<ValType>>& right = mt;
    return TMatrix(left + right);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const
{
    const TVector<TVector<ValType>>& left = *this;
    const TVector<TVector<ValType>>& right = mt;
    return TMatrix(left - right);
}
