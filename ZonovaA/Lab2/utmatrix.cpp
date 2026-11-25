#include "../../includes/Lab2/utmatrix.h" 
#include <stdexcept>

template <class ValType>
//конструктор с параметрами
TVector<ValType>::TVector(int s, int si) {
    if (s < 0 || s > MAX_VECTOR_SIZE) {
        throw std::out_of_range("size vector ne podhodit");
    }
    if (si < 0 || si > s) {
        throw std::out_of_range("index ne dopustim");
    }
    Size = s;
    StartIndex = si;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i) {
        pVector[i] = ValType{}; // ValType{} создает значение по умолчанию (0 для чисел)
    }
}

//конструктор копирования (принимает константную ссылку на другой вектор)
template <class ValType>
TVector<ValType>::TVector(const TVector& v) {
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i) {
        pVector[i] = v.pVector[i];
    }
}

//деструктор 
template <class ValType>
TVector<ValType>::~TVector() {
    delete[] pVector;
    pVector = nullptr;
}

//оператор доступа []
template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("index go out in vector");
    }
    return pVector[pos];
}

//оператор доступа [] только для чтения 
template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
    if (pos < StartIndex || pos >= Size) {
        throw std::out_of_range("index go out in vector");
    }
    return pVector[pos];
}

//оператор сравнения на равенство ==
template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
    if (this == &v) return true; //если сравниваем объект сам с собой, сразу возвращаем true
    if (Size != v.Size || StartIndex != v.StartIndex) {
        return false;
    }
    for (int i = StartIndex; i < Size; ++i) {
        if (pVector[i] != v.pVector[i]) {
            return false;
        }
    }
    return true;
}

//оператор сравнения на неравенство !=
template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*this == v);
}

//оператор присваивания =
template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    if (this == &v) {
        return *this;
    }
    if (Size != v.Size) {
        delete[] pVector;
        Size = v.Size;
        pVector = new ValType[Size];
    }
    StartIndex = v.StartIndex;
    for (int i = 0; i < Size; ++i) {
        pVector[i] = v.pVector[i];
    }
    return *this;
}

//скалярное сложение (вектор + число)
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
    TVector<ValType> res(*this); //не меняем оригинал
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] + val;
    }
    return res;
}

//скалярного вычитание (вектор - число)
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] - val;
    }
    return res;
}

//скалярное умножение (вектор * число)
template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] * val;
    }
    return res;
}

//векторное сложение (вектор + вектор)
template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("size razn or index"); //складывать можно только векторы одинакового размера и с одинаковым нач индексом
    }
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] + v.pVector[i];
    }
    return res;
}

//векторное вычитание (вектор - вектор)
template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("size razn or index");
    }
    TVector<ValType> res(*this);
    for (int i = StartIndex; i < Size; ++i) {
        res.pVector[i] = res.pVector[i] - v.pVector[i];
    }
    return res;
}

//скалярное произведение (вектор * вектор)
template <class ValType>
ValType TVector<ValType>::operator*(const TVector& v) const {
    if (Size != v.Size || StartIndex != v.StartIndex) {
        throw std::invalid_argument("size razn or index");
    }
    ValType result = ValType{};
    for (int i = StartIndex; i < Size; ++i) {
        result = result + (pVector[i] * v.pVector[i]);
    }
    return result; //возвращаем скаляр
}

//конструктор матрицы
template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0) {
    if (s < 0 || s > MAX_MATRIX_SIZE) {
        throw std::out_of_range("size matrix ne dopustim");
    }
    for (int i = 0; i < s; ++i) {
        this->pVector[i] = TVector<ValType>(s, i); // this-> обязателен, так как pVector унаследован от шаблонного базового класса.
    }
}

//конструктор копирования матрицы
template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}

//конструктор преобразования типа (из обычного вектора векторов в матрицу)
template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt) {}

//оператор присваивания матрицы
template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
    if (this != &mt) {     //проверяем на самоприсваивание
        TVector<TVector<ValType>>::operator=(mt);
    }
    return *this;
}

//оператор сравнения матриц на равенство ==
template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
    return TVector<TVector<ValType>>::operator==(mt);
}

//оператор сравнения матриц на неравенство !=
template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
    return !(*this == mt);
}

//оператор сложения матриц
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
    return TVector<TVector<ValType>>::operator+(mt);
}

//оператор вычитания матриц
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
    return TVector<TVector<ValType>>::operator-(mt);
}