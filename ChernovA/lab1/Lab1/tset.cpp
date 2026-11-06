#include "../../../includes/Lab1/tset.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

TSet::TSet(int mp) : BitField(mp) {
    MaxPower = mp;
}

TSet::TSet(const TSet& s) : BitField(s.BitField) {
    MaxPower = s.MaxPower;
}      // конструктор копирования

TSet::TSet(const TBitField& bf) : BitField(bf) {
    MaxPower = bf.GetLength();
} // конструктор преобразования типа

TSet::operator TBitField() {
    return BitField;
}      // преобразование типа к битовому полю

// доступ к битам
int TSet::GetMaxPower(void) const {
    return MaxPower;
}     // максимальная мощность множества

void TSet::InsElem(const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of universe bounds");
    }
    BitField.SetBit(Elem);
}       // включить элемент в множество

void TSet::DelElem(const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of universe bounds");
    }
    BitField.ClrBit(Elem);
}      // удалить элемент из множества

int TSet::IsMember(const int Elem) const {
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of universe bounds");
    }
    return BitField.GetBit(Elem);
} // проверить наличие элемента в множестве

    // теоретико-множественные операции
int TSet::operator== (const TSet& s) const {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Cannot compare sets with different MaxPower");
    }
    return BitField == s.BitField;
} // сравнение

int TSet::operator!= (const TSet& s) const {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Cannot compare sets with different MaxPower");
    }
    if (*this == s) {
        return 0;
    }
    return 1;
} // несравнение

TSet& TSet::operator=(const TSet& s) {
    if (&s == this) {
        return *this;
    }
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}  // присваивание

TSet TSet::operator+ (const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of universe bounds");
    }
    TSet result(*this);
    result.InsElem(Elem);
    return result;
} // объединение с элементом
  // элемент должен быть из того же универса

TSet TSet::operator- (const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element is out of universe bounds");
    }
    TSet result(*this);
    result.DelElem(Elem);
    return result;
} // разность с элементом
  // элемент должен быть из того же универса

TSet TSet::operator+ (const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Cannot unite sets with different MaxPower");
    }
    TBitField result_bf = BitField | s.BitField;
    return TSet(result_bf);
} // объединение

TSet TSet::operator* (const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Cannot intersect sets with different MaxPower");
    }
    TBitField result_bf = BitField & s.BitField;
    return TSet(result_bf);
}  // пересечение

TSet TSet::operator~ (void) {
    TBitField result_bf = ~BitField;
    return TSet(result_bf);
}           // дополнение

std::istream& operator>>(std::istream& istr, TSet& s) {
    //читаем всю строку целиком чтобы обработать числа введенные через пробел
    std::string line;
    std::getline(istr, line);
    //загружаем строку в поток для удобного чтения чисел
    std::stringstream ss(line);
    int val;
    //пока получается считать число — добавляем его в множество
    while (ss >> val) {
        s.InsElem(val); //если вне диапазона, сработает искл
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) {
    ostr << "{";
    bool first = true;
    for (int i = 0; i < s.MaxPower; ++i) {
        if (s.IsMember(i)) {
            if (!first) {
                ostr << ", ";
            }
            ostr << i;
            first = false;
        }
    }
    ostr << "}";
    return ostr;
}