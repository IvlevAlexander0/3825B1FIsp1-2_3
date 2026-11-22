#include "\Users\lapte\Desktop\Blok1\3825B1FIsp1-2_3\includes\Lab2\utmatrix.h"
#include <stdexcept>

// TVector
template <class ValType>
TVector<ValType>::TVector(int s, int si) {
    if (s < 0 || si < 0 || si > s) {
        throw std::invalid_argument("Invalid size or index");
    }
    Size = s;
    StartIndex = si;
    pVector = new ValType[Size]();
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i) {
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
        throw std::out_of_range("Vector index out of range");
    }
    return pVector[pos];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("Vector index out of range");
    }
    return pVector[pos];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        return false;
    }
    for (int i = 0; i < Size; ++i) {
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
    if (this != &v) {
        if (Size != v.Size) {
            delete[] pVector;
            Size = v.Size;
            pVector = new ValType[Size];
        }
        StartIndex = v.StartIndex;
        for (int i = 0; i < Size; ++i) {
            pVector[i] = v.pVector[i];
        }
    }
    return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector res(*this);
    for (int i = 0; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] + val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector res(*this);
    for (int i = 0; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] - val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector res(*this);
    for (int i = 0; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] * val;
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("mismatch");
    }
    TVector res(*this);
    for (int i = 0; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] + v.pVector[i];
    }
    return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("mismatch");
    }
    TVector res(*this);
    for (int i = 0; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] - v.pVector[i];
    }
    return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("mismatch");
    }
    ValType res = ValType();
    for (int i = 0; i < Size; ++i) {
        res = res + (pVector[i] * v.pVector[i]);
    }
    return res;
}

// Реализация TMatrix
template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s) {
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::invalid_argument("Invalid matrix size");
    }
    for (int i = 0; i < s; ++i) {
        this->pVector[i] = TVector<ValType>(s, i);
    }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {
    int size = this->Size;
    for (int i = 0; i < size; ++i) {
        if (this->pVector[i].GetStartIndex() != i) {
            throw std::invalid_argument("Invalid structure");
        }
    }
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
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    TVector<TVector<ValType>>::operator=(mt);
    return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("size mismatch");
    }
    TMatrix res(*this);
    for (int i = 0; i < this->Size; ++i) {
        res.pVector[i] = this->pVector[i] + mt.pVector[i];
    }
    return res;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
    if (this->Size != mt.Size) {
        throw std::invalid_argument("size mismatch");
    }
    TMatrix res(*this);
    for (int i = 0; i < this->Size; ++i) {
        res.pVector[i] = this->pVector[i] - mt.pVector[i];
    }
    return res;
}


template class TVector<int>;
template class TVector<double>;
template class TMatrix<int>;
template class TMatrix<double>;
template class TVector<TVector<int>>;
template class TVector<TVector<double>>;