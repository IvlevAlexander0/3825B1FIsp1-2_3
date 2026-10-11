// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#pragma once

#include "tbitfield.h"

class TSet
{
private:
    int MaxPower;       // максимальная мощность множества
    TBitField BitField; // битовое поле для хранения характеристического вектора

public:
    TSet(int mp) : BitField(mp) {
        MaxPower = mp;
    }

    TSet(const TSet& s) : BitField(s.BitField) {
        MaxPower = s.MaxPower;
    }      // конструктор копирования

    TSet(const TBitField& bf) : BitField(bf) {
        MaxPower = bf.GetLength();
    } // конструктор преобразования типа

    operator TBitField() {
        return BitField;
    }      // преобразование типа к битовому полю

    // доступ к битам

    int GetMaxPower(void) const {
        return MaxPower;
    }     // максимальная мощность множества

    void InsElem(const int Elem) {
        BitField.SetBit(Elem);
    }       // включить элемент в множество

    void DelElem(const int Elem) {
        BitField.ClrBit(Elem);
    }       // удалить элемент из множества

    int IsMember(const int Elem) const {
        return BitField.GetBit(Elem);
    } // проверить наличие элемента в множестве

    // теоретико-множественные операции
    int operator== (const TSet& s) const {
        return BitField == s.BitField;
    } // сравнение

    int operator!= (const TSet& s) const {
        if (*this == s) {
            return 0;
        }
        return 1;
    } // несравнение

    TSet& operator=(const TSet& s) {
        if (&s == this) {
            return *this;
        }

        MaxPower = s.MaxPower;
        BitField = s.BitField;
        return *this;
    }  // присваивание

    TSet operator+ (const int Elem) {
        TSet result(*this);
        result.InsElem(Elem);
        return result;
    } // объединение с элементом
      // элемент должен быть из того же универса

    TSet operator- (const int Elem) {
        TSet result(*this);
        result.DelElem(Elem);
        return result;
    } // разность с элементом
      // элемент должен быть из того же универса

    TSet operator+ (const TSet& s) {
        TBitField result_bf = BitField | s.BitField;
        return TSet(result_bf);
    }  // объединение

    TSet operator* (const TSet& s) {
        TBitField result_bf = BitField & s.BitField;
        return TSet(result_bf);
    }  // пересечение

    TSet operator~ (void) {
        TBitField result_bf = ~BitField;
        return TSet(result_bf);
    }           // дополнение

    friend std::istream& operator>>(std::istream& istr, TSet& bf) {
        istr >> bf.BitField;
        return istr;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
        ostr << bf.BitField;
        return ostr;
    }
};