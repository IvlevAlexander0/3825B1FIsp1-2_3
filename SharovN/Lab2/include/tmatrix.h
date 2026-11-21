#pragma once

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;


template <class ValType>
class TVector
{
protected:
    int Size;
    int StartIndex;
    ValType* pVector;
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector &v);
    ~TVector();
    int GetSize() const { return Size; }
    int GetStartIndex() const { return StartIndex; }
    ValType& operator[](int pos);
    const ValType& operator[](int pos) const;
    bool operator==(const TVector &v) const;
    bool operator!=(const TVector &v) const;
    TVector& operator=(const TVector &v);

    //скаляр операции
    TVector operator+(const ValType &val) const;
    TVector operator-(const ValType &val) const;
    TVector operator*(const ValType &val) const;

    //векторные
    TVector operator+(const TVector &v) const;
    TVector operator-(const TVector &v) const;
    ValType operator*(const TVector &v) const;


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
            if (i > 0) {
                out << ' ';
            }
            if (i < v.GetStartIndex()) {
                out << ValType{};
            }
            else {
                out << v[i];
            }
        }
        return out;
    }
};

//верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix &mt);
    TMatrix(const TVector<TVector<ValType>> &mt);
    bool operator==(const TMatrix &mt) const;
    bool operator!=(const TMatrix &mt) const;
    TMatrix& operator=(const TMatrix &mt);
    TMatrix operator+(const TMatrix &mt) const;
    TMatrix operator-(const TMatrix &mt) const;


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
            if (i > 0) {
                out << '\n';
            }
            out << mt[i];
        }
        return out;
    }
};

#include "tmatrix_impl.hpp"
