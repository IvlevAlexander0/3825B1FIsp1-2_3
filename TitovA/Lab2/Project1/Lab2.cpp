#include "utmatrix.h"
#include <stdexcept>

// Класс TVector хранит элементы с индексами от StartIndex до Size - 1.
template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si), pVector(nullptr)
{
    if (s < 0 || s > MAX_VECTOR_SIZE || si < 0 || si > s)
        throw std::invalid_argument("Некорректные границы вектора");
    if (Size > StartIndex)
        pVector = new ValType[Size - StartIndex]();
}

template <class ValType>
TVector<ValType>::TVector(const TVector<ValType>& v)
    : Size(v.Size), StartIndex(v.StartIndex), pVector(nullptr)
{
    int count = Size - StartIndex;
    if (count > 0) {
        pVector = new ValType[count];
        try {
            for (int i = 0; i < count; ++i) pVector[i] = v.pVector[i];
        }
        catch (...) { delete[] pVector; throw; }
    }
}

template <class ValType>
TVector<ValType>::~TVector() { delete[] pVector; }

template <class ValType>
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos < StartIndex || pos >= Size) throw std::out_of_range("Индекс выходит за допустимые границы вектора");
    return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const
{
    if (pos < StartIndex || pos >= Size) throw std::out_of_range("Индекс выходит за допустимые границы вектора");
    return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) return false;
    for (int i = StartIndex; i < Size; ++i) if ((*this)[i] != v[i]) return false;
    return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const { return !(*this == v); }

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (this == &v) return *this;
    int count = v.Size - v.StartIndex;
    ValType* data = count ? new ValType[count] : nullptr;
    try { for (int i = 0; i < count; ++i) data[i] = v.pVector[i]; }
    catch (...) { delete[] data; throw; }
    delete[] pVector;
    pVector = data; Size = v.Size; StartIndex = v.StartIndex;
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& x) const
{
    TVector result(*this);
    for (int i = StartIndex; i < Size; ++i) result[i] = (*this)[i] + x;
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& x) const
{
    TVector result(*this);
    for (int i = StartIndex; i < Size; ++i) result[i] = (*this)[i] - x;
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& x) const
{
    TVector result(*this);
    for (int i = StartIndex; i < Size; ++i) result[i] = (*this)[i] * x;
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) throw std::invalid_argument("Границы векторов не совпадают");
    TVector result(*this);
    for (int i = StartIndex; i < Size; ++i) result[i] = (*this)[i] + v[i];
    return result;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) throw std::invalid_argument("Границы векторов не совпадают");
    TVector result(*this);
    for (int i = StartIndex; i < Size; ++i) result[i] = (*this)[i] - v[i];
    return result;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const
{
    if (Size != v.Size || StartIndex != v.StartIndex) throw std::invalid_argument("Границы векторов не совпадают");
    ValType sum{};
    for (int i = StartIndex; i < Size; ++i) sum += (*this)[i] * v[i];
    return sum;
}

// Строка матрицы с номером i хранит только элементы, начиная с диагонали.
template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0)
{
    if (s < 0 || s > MAX_MATRIX_SIZE) throw std::invalid_argument("Некорректный размер матрицы");
    for (int i = 0; i < s; ++i) (*this)[i] = TVector<ValType>(s, i);
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt)
    : TVector<TVector<ValType>>(mt.GetSize(), 0)
{
    int n = mt.GetSize();
    if (n > MAX_MATRIX_SIZE) throw std::invalid_argument("Размер матрицы превышает допустимый предел");
    for (int i = 0; i < n; ++i) {
        const TVector<ValType>& row = mt[i];
        if (row.GetSize() != n || row.GetStartIndex() > i)
            throw std::invalid_argument("Некорректная строка матрицы");
        (*this)[i] = TVector<ValType>(n, i);
        for (int j = i; j < n; ++j) (*this)[i][j] = row[j];
    }
}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const
{
    if (this->GetSize() != mt.GetSize()) return false;
    for (int i = 0; i < this->GetSize(); ++i) if ((*this)[i] != mt[i]) return false;
    return true;
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const { return !(*this == mt); }

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt)
{
    if (this != &mt) TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const
{
    if (this->GetSize() != mt.GetSize()) throw std::invalid_argument("Размеры матриц не совпадают");
    TMatrix result(this->GetSize());
    for (int i = 0; i < this->GetSize(); ++i) result[i] = (*this)[i] + mt[i];
    return result;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const
{
    if (this->GetSize() != mt.GetSize()) throw std::invalid_argument("Размеры матриц не совпадают");
    TMatrix result(this->GetSize());
    for (int i = 0; i < this->GetSize(); ++i) result[i] = (*this)[i] - mt[i];
    return result;
}

//шаблоны типов данных.
template class TVector<int>;
template class TVector<double>;
template class TVector<float>;
template class TMatrix<int>;
template class TMatrix<double>;
template class TMatrix<float>;
