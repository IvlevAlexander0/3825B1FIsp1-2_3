#include "../../includes/Lab1/tbitfield.h"
#include <stdexcept>
#include <string>

//нужно получить индекс n-го элемента, для этого нужно n нацело поделить на размер типа данных битового поля в битах, например, n = 70, тогда этот элемент находится в 2 байте, считая от 0
int TBitField::GetMemIndex(const int n) const {
	return n / (sizeof(TELEM) * 8);
}
//нужно вывести битовую маску элемента
TELEM TBitField::GetMemMask(const int n) const {
	return (TELEM)1 << (n % (sizeof(TELEM) * 8)); //создается 1 32-битная типа TELEM, а затем сдвигается, возвращается число, полученное сдвигом
}
//конструктор инициализирующий 0
TBitField::TBitField(int len) {
	BitLen = len;
	MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8); //добавляем sizeof(telem)*8 - 1, чтобы было место для остатка и деление выполнялось корректно
	pMem = new TELEM[MemLen];//создаём массив из MemLen элементов типа TELEM
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}

}
//конструктор копирования
TBitField::TBitField(const TBitField& bf) {
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}
//деструктор
TBitField::~TBitField() {
	delete[] pMem;
}
//получить длину (к-во битов)
int TBitField::GetLength(void) const {
	return BitLen;
}
//установить бит
void TBitField::SetBit(const int n) {
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}
//очистить бит
void TBitField::ClrBit(const int n) {
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}
//получить значение бита
int  TBitField::GetBit(const int n) const {
	if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
		return 1;
	else
		return 0; //если элемент n не равен нулю, то при умножении на его маску, значение не равно 0, следственно значение бита - 1
}
//сравнение
int TBitField::operator==(const TBitField& bf) const {
	if (BitLen != bf.BitLen)
		return 0; //если длины двух битовых полей не равны, то поля не равны
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 0; //элементы полей не равны 
	}
	return 1;
}
//сравнение
int TBitField::operator!=(const TBitField& bf) const {
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				return 1; //элементы полей не равны 
		}
		return 0; //поля равны
	}
	else
		return 1;

}
//присваивание
TBitField& TBitField::operator=(const TBitField& bf) {
	if (this == &bf)
		return *this; //если адреса совпадают — это самоприсваивание
	delete[] pMem; //освобождаем старую память

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

	return *this;
}
//операция или
TBitField  TBitField::operator|(const TBitField& bf) {
	int maxLen = 0;
	if (BitLen > bf.BitLen) maxLen = BitLen;
	else maxLen = bf.BitLen;

	TBitField result(maxLen);//результат объединения двух полей

	int minMem = 0;
	if (MemLen < bf.MemLen) minMem = MemLen;
	else minMem = bf.MemLen;

	for (int i = 0; i < minMem; i++)
		result.pMem[i] = pMem[i] | bf.pMem[i];

	if (MemLen > bf.MemLen)
		for (int i = minMem; i < MemLen; i++)
			result.pMem[i] = pMem[i];
	if (bf.MemLen > MemLen)
		for (int i = minMem; i < bf.MemLen; i++)
			result.pMem[i] = bf.pMem[i];

	return result;
}
//операция "и" 
TBitField  TBitField::operator&(const TBitField& bf) {
	int minLen = 0;
	if (BitLen < bf.BitLen) minLen = BitLen;
	else minLen = bf.BitLen;

	TBitField result(minLen);//результат пересечения двух полей

	int minMem = 0;
	if (MemLen < bf.MemLen) minMem = MemLen;
	else minMem = bf.MemLen;

	for (int i = 0; i < minMem; i++)
		result.pMem[i] = pMem[i] & bf.pMem[i];

	return result;
}
//отрицание
TBitField  TBitField::operator~(void) {
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = ~pMem[i];
	return result;
}
std::istream& operator>>(std::istream& istr, TBitField& bf) {
	for (int i = 0; i < bf.BitLen; i++) {
		char bit;
		istr >> bit;
		if (bit == '1') {
			bf.SetBit(i);
		}
		else if (bit == '0') {
			bf.ClrBit(i);
		}
		else {
			throw std::invalid_argument("Error input bit: waiting '0' or '1'");
		}
	}
	return istr;
}
std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}