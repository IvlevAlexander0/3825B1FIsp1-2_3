#include <utmatrix.h>
#include <stdexcept>
#include <algorithm>

//TVector
template <class ValType>
TVector<ValType>::TVector(int s, int si) {
	if (s < 0) {
		throw std::invalid_argument("Vector length cannot be negative");
	}
	if (si < 0) {
		throw std::invalid_argument("Vector start index cannot be negative");
	}
	if (s > MAX_VECTOR_SIZE) {
		throw std::invalid_argument("The vector length exceeds max_vector_size");
	}
	Size = s;
	StartIndex = si;
	pVector = new ValType[Size]();
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v) : Size(v.Size), StartIndex(v.StartIndex) {
	pVector = new ValType[Size];
	for (size_t i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
}

template <class ValType>
TVector<ValType>::~TVector() {
	delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos) {
	if (pos < StartIndex || pos >= StartIndex + Size) {
		throw std::out_of_range("Index is out of range");
	}
	return pVector[pos - StartIndex];
}

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
	if (pos < StartIndex || pos >= StartIndex + Size) {
		throw std::out_of_range("Index is out of range");
	}
	return pVector[pos - StartIndex];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const {
	if (this == &v) return true;

	if (Size != v.Size || StartIndex != v.StartIndex) {
		return false;
	}
	for (size_t i = 0; i < Size; i++) {
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
	if (this == &v) return *this;

	if (Size != v.Size) {
		ValType* tmp = new ValType[v.Size];
		delete[] pVector;
		pVector = tmp;
		Size = v.Size;
	}
	StartIndex = v.StartIndex;
	for (size_t i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const {
	TVector<ValType> res(*this);
	for (size_t i = 0; i < Size; i++) {
		res.pVector[i] = res.pVector[i] + val;
	}
	return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const {
	TVector<ValType> res(*this);
	for (size_t i = 0; i < Size; i++) {
		res.pVector[i] = res.pVector[i] - val;
	}
	return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const {
	TVector<ValType> res(*this);
	for (size_t i = 0; i < Size; i++) {
		res.pVector[i] = res.pVector[i] * val;
	}
	return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v) const {
	if (Size != v.Size) {
		throw std::invalid_argument("Vectors size is not equal");
	}
	if (StartIndex != v.StartIndex) {
		throw std::invalid_argument("Vector start index is not equal");
	}
	
	TVector<ValType> res(Size, StartIndex);
	for (size_t i = 0; i < Size; i++) {
		res.pVector[i] = pVector[i] + v.pVector[i];
	}
	return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v) const {
	if (Size != v.Size) {
		throw std::invalid_argument("Vectors size is not equal");
	}
	if (StartIndex != v.StartIndex) {
		throw std::invalid_argument("Vector start index is not equal");
	}

	TVector<ValType> res(Size, StartIndex);
	for (size_t i = 0; i < Size; i++) {
		res.pVector[i] = pVector[i] - v.pVector[i];
	}
	return res;
}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& v) const {
	if (Size != v.Size) {
		throw std::invalid_argument("Vectors size is not equal");
	}
	if (StartIndex != v.StartIndex) {
		throw std::invalid_argument("Vector start index is not equal");
	}

	ValType res{};
	for (size_t i = 0; i < Size; i++) {
		res = res + (pVector[i] * v.pVector[i]);
	}
	return res;
}

template <class ValType>
std::istream& operator>>(std::istream& in, TVector<ValType>& v) {
	for (size_t i = 0; i < v.Size; i++) {
		in >> v.pVector[i];
	}
	return in;
}

template <class ValType>
std::ostream& operator<<(std::ostream& out, const TVector<ValType>& v) {
	for (size_t i = 0; i < v.Size; i++) {
		out << v.pVector[i] << ' ';
	}
	return out;
}

//TMatrix
template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s, 0) {
	if (s > MAX_MATRIX_SIZE) {
		throw std::invalid_argument("The matrix size exceeds max_matrix_size");
	}
	for (size_t i = 0; i < s; i++) {
		(*this)[i] = TVector<ValType>(s - i, i);
	}
}

template<class ValType>
TMatrix<ValType>::TMatrix(const TMatrix &mt) : TVector<TVector<ValType>>(mt){}

template<class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt) : TVector<TVector<ValType>>(mt){}

template<class ValType>
bool TMatrix<ValType>::operator==(const TMatrix& mt) const {
	return TVector<TVector<ValType>>::operator==(mt);
}

template<class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix& mt) const {
	return TVector<TVector<ValType>>::operator!=(mt);
}

template<class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix& mt) {
	TVector<TVector<ValType>>::operator=(mt);
	return *this;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt) const {
	return TVector<TVector<ValType>>::operator+(mt);
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt) const {
	return TVector<TVector<ValType>>::operator-(mt);
}

template<class ValType>
std::istream& operator>>(std::istream& in, TMatrix<ValType>& mt) {
	for (size_t i = 0; i < mt.Size; i++) {
		in >> mt.pVector[i];
	}
	return in;
}

template<class ValType>
std::ostream& operator<<(std::ostream& out, const TMatrix<ValType>& mt) {
	for (size_t i = 0; i < mt.Size; i++) {
		out << mt.pVector[i] << std::endl;
	}
	return out;
}
