#include "../../includes/Lab1/tbitfield.h"
#include <iostream>

// методы реализации
int TBitField::GetMemIndex(const int n) const {
    int bits_per_elem = sizeof(TELEM) * 8; //TELEM = 4 байта => 32 бита
    return (n / bits_per_elem);
}  // индекс в pМем для бита n

TELEM TBitField::GetMemMask(const int n) const {
    int bits_per_elem = sizeof(TELEM) * 8;
    int local_pos = n % bits_per_elem; //позиция бита внутри элемента
    return TELEM(1) << local_pos;
} // битовая маска для бита n

TBitField::TBitField(int len) {
    BitLen = len;
    int bits_per_elem = sizeof(TELEM) * 8;
    MemLen = (len + bits_per_elem - 1) / bits_per_elem;
    pMem = new TELEM[MemLen]; //создаем массив (поле) под MemLen битов
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;  //инициализируем все нулями
    }
}

TBitField::TBitField(const TBitField& bf) {  //bf - другое битовое поле, которое нужно скопировать в новое битовое поле
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {     //деструктор, [] - значит удалить массив объектов
    delete[] pMem;
} 

// доступ к битам
int TBitField::GetLength(void) const {
    return BitLen;
}      // получить длину (к-во битов)

void TBitField::SetBit(const int n) {
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n); // | - побитовая операция "или". Используем чтобы установить бит в 1
}       // установить бит

void TBitField::ClrBit(const int n) {
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n); // & - побитовая операция "и". ~ - побитовая операция "не". Используем чтобы занулить конкретный бит
}       // очистить бит

int TBitField::GetBit(const int n) const {
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
} // получить значение бита

// битовые операции
int TBitField::operator==(const TBitField& bf) const {
    if (BitLen != bf.BitLen) {  //если размер битового поля не совпадает, сразу выходим
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {  // сравниваем поэлементно, несовпадение -> выход
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
} // сравнение

int TBitField::operator!=(const TBitField& bf) const { //через this и == вызываем кусок кода, что выше,и делаем return наоборот т.к. у нас != (0->1, 1->0)
    if (*this == bf) {
        return 0;
    }
    return 1;
} // сравнение

TBitField& TBitField::operator=(const TBitField& bf) {
    if (&bf == this) {  //т.к. иначе код ниже очистил бы this, и мы бы читали из освобожденной памяти
        return *this;
    }
    delete[] pMem; //освобождаем память из this, чтобы мы записывали в него из bf
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) { //поэлементно копируем bf в this
        pMem[i] = bf.pMem[i];
    }
    return *this; //именно *this, иначе a=b=c не работали бы
} // присваивание

TBitField TBitField::operator|(const TBitField& bf) {
    int result_len = 0;
    if (BitLen < bf.BitLen) {
        result_len = BitLen;
    }
    else
    {
        result_len = bf.BitLen;
    }
    TBitField result(result_len);
    for (int i = 0; i < result.MemLen; i++) {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return result;

} // операция "или"

TBitField TBitField::operator&(const TBitField& bf) {
    int result_len = 0;
    if (BitLen < bf.BitLen) {
        result_len = BitLen;
    }
    else
    {
        result_len = bf.BitLen;
    }
    TBitField result(result_len);
    for (int i = 0; i < result.MemLen; i++) {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return result;
} // операция "и"

TBitField TBitField::operator~(void) {
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~pMem[i]; //инвертируем все биты, и теперь надо обнулить все незначащие нули
    }
    int bits_per_elem = sizeof(TELEM) * 8; //считаем количество значащих битов в последнем элементе
    int valid_bits = BitLen - (MemLen - 1) * bits_per_elem;
    if (valid_bits < bits_per_elem) { //обнуляем этот хвост
        TELEM mask = (TELEM(1) << valid_bits) - 1;
        result.pMem[MemLen - 1] = result.pMem[MemLen - 1] & mask;
    }
    return result;
} // отрицание

std::istream& operator>>(std::istream& istr, TBitField& bf) { //вводим слева старший направо младший бит (т.е. первый бит самый старший)
    for (int i = bf.BitLen - 1; i >= 0; i--) {
        char c;
        istr >> c; //при такой реализации желательно не ошибаться в записи (не ставить лишние символы и пробелы)
        if (c == '1') {
            bf.SetBit(i);
        }
        else
        {
            bf.ClrBit(i);
        }
    }
    return istr;
}     

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
    for (int i = bf.BitLen - 1; i >= 0; i--) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}