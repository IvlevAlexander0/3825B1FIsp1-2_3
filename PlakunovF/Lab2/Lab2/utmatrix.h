#pragma once

#include <iostream>
#include <stdexcept>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
	ValType* pVector;
public:
	TVector(int s = 10, int si = 0) : Size(s), StartIndex(si) {
		if (0 > Size || Size > MAX_VECTOR_SIZE)
			throw std::invalid_argument("Недопустимый размер вектора");
		if (StartIndex < 0 || StartIndex > Size)
			throw std::invalid_argument("Начальный индекс не может быть больше размера");
		pVector = new ValType[Size]();
	}

	TVector(const TVector& v) : Size(v.Size), StartIndex(v.StartIndex) { // конструктор копирования
		pVector = new ValType[Size]();
		for (int i = 0; i < Size; ++i)
			pVector[i] = v.pVector[i];
	}

	~TVector() { delete[] pVector; }

	int GetSize() const { return Size; }             // размер вектора
	int GetStartIndex() const { return StartIndex; } // индекс первого элемента

	ValType& operator[](int pos) {           // доступ
		if (pos < 0 || pos >= Size)
			throw std::out_of_range("Не верная позиция вектора");
		return pVector[pos];
	}

	const ValType& operator[](int pos) const { // доступ
		if (pos < 0 || pos >= Size)
			throw std::out_of_range("Не верная позиция вектора");
		return pVector[pos];
	}

	bool operator==(const TVector& v) const { // сравнение
		if (Size != v.Size || StartIndex != v.StartIndex) return 0;
		for (int i = StartIndex; i < Size; ++i) {
			if (pVector[i] != v.pVector[i]) return 0;
		}
		return 1;
	}

	bool operator!=(const TVector& v) const { return !(*this == v); }	// сравнение

	TVector& operator=(const TVector& v) {        // присваивание
		if (this != &v) {
			Size = v.Size;
			StartIndex = v.StartIndex;
			delete[] pVector;
			pVector = new ValType[Size]();
			for (int i = 0; i < Size; ++i)
				pVector[i] = v.pVector[i];
		}
		return *this;
	}

	// скалярные операции
	TVector  operator+(const ValType& val) const {   // прибавить скаляр
		TVector v(*this);
		for (int i = StartIndex; i < Size; ++i)
			v.pVector[i] += val;
		return v;
	}

	TVector  operator-(const ValType& val) const {   // вычесть скаляр
		TVector v(*this);
		for (int i = StartIndex; i < Size; ++i)
			v.pVector[i] -= val;
		return v;
	}

	TVector  operator*(const ValType& val) const {   // умножить на скаляр
		TVector v(*this);
		for (int i = StartIndex; i < Size; ++i)
			v.pVector[i] *= val;
		return v;
	}

	// векторные операции
	TVector  operator+(const TVector& v) const {     // сложение
		if (Size != v.Size || StartIndex != v.StartIndex)
			throw std::invalid_argument("Размеры или индексы не совпадают");
		TVector result(Size, StartIndex);
		for (int i = 0; i < Size; ++i)
			result.pVector[i] = pVector[i] + v.pVector[i];
		return result;

	}

	TVector  operator-(const TVector& v) const {     // вычитание
		if (Size != v.Size || StartIndex != v.StartIndex)
			throw std::invalid_argument("Размеры или индексы не совпадают");
		TVector result(Size, StartIndex);
		for (int i = 0; i < Size; ++i)
			result.pVector[i] = pVector[i] - v.pVector[i];
		return result;
	}

	ValType  operator*(const TVector& v) const {     // скалярное произведение
		if (Size != v.Size || StartIndex != v.StartIndex)
			throw std::invalid_argument("Размеры или индексы не совпадают");
		ValType result = 0;
		for (int i = 0; i < Size; ++i)
			result += pVector[i] * v.pVector[i];
		return result;
	}

	// ввод-вывод

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


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
	TMatrix(int s = 10) : TVector<TVector<ValType>>(s) {
		if (s <= 0 || s > MAX_MATRIX_SIZE)
			throw std::invalid_argument("Недопустимый размер матрицы.");
		for (int i = 0; i < s; ++i)
			this->pVector[i] = TVector<ValType>(s, i);
	}

	TMatrix(const TMatrix& mt) : TVector<TVector<ValType>>(mt) {}                    // копирование

	TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt.GetSize()) {  // преобразование типа
		if (mt.GetSize() > MAX_MATRIX_SIZE)
			throw std::invalid_argument("Недопустимый размер матрицы.");
		for (int i = 0; i < mt.GetSize(); ++i) {
			this->pVector[i] = TVector<ValType>(mt.GetSize(), i);
			for (int j = 0; j < mt.GetSize(); ++j) {
				this->pVector[i].pVector[j] = mt.pVector[i].pVector[j];
			}
		}

	}

	bool operator==(const TMatrix& mt) const {      // сравнение
		return TVector<TVector<ValType>>::operator==(mt);
	}

	bool operator!=(const TMatrix& mt) const {
		return !(*this == mt);
	}

	TMatrix& operator= (const TMatrix& mt) {        // присваивание
		if (this != &mt) {
			TVector<TVector<ValType>>::operator=(mt);
		}
		return *this;
	}

	TMatrix  operator+ (const TMatrix& mt) const {        // сложение
		if (this->Size != mt.Size)
			throw std::invalid_argument("Размеры");
		TMatrix result(*this);
		for (int i = 0; i < Size; ++i)
			result.pVector[i] = pVector[i] + mt.pVector[i];
		return result;
	}
	TMatrix  operator- (const TMatrix& mt) const {        // вычитание
		if (this->Size != mt.Size)
			throw std::invalid_argument("Размеры");
		TMatrix result(*this);
		for (int i = 0; i < Size; ++i)
			result.pVector[i] = pVector[i] - mt.pVector[i];
		return result;
	}

	// ввод / вывод
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
