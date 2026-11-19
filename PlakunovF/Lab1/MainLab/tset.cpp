#include "tset.h"
#include <iostream>

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const
{
	return MaxPower;
}

void TSet::InsElem(const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) { throw std::invalid_argument("Елемент выходит за границы множества"); }
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) { throw std::invalid_argument("Елемент выходит за границы множества"); }
	BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const
{
	if (Elem < 0 || Elem >= MaxPower) { return 0; }
	return BitField.GetBit(Elem);

}

int TSet::operator== (const TSet& s) const
{
	if (MaxPower != s.MaxPower) { return 0; }
	return BitField == s.BitField;
}

int TSet::operator!= (const TSet& s) const
{
	return !(*this == s);
}

TSet& TSet::operator=(const TSet& s)
{
	if (this != &s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

TSet TSet::operator+ (const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) { throw std::invalid_argument("Элемент не входит в универс"); }
	TSet res(*this);
	res.BitField.SetBit(Elem);
	return res;
}

TSet TSet::operator- (const int Elem)
{
	if (Elem < 0 || Elem >= MaxPower) { throw std::invalid_argument("Элемент не входит в универс"); }
	TSet res(*this);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator+ (const TSet& s)
{
	if (MaxPower != s.MaxPower) { throw std::invalid_argument("Разные мощности множеств"); }
	TSet res(*this);
	res.BitField = BitField | s.BitField;
	return res;
}

TSet TSet::operator* (const TSet& s)
{
	if (MaxPower != s.MaxPower) { throw std::invalid_argument("Разные мощности множеств"); }
	TSet res(*this);
	res.BitField = BitField & s.BitField;
	return res;
}

TSet TSet::operator~ (void)
{
	TSet res(*this);
	res.BitField = ~BitField;
	return res;
}

std::istream& operator>>(std::istream& istr, TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i) {
		bf.DelElem(i);
	}
	int val;
	while (istr >> val) {
		if (val >= 0 && val < bf.MaxPower) {
			bf.InsElem(val);
		}
	}
	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& bf)
{
	bool first = true;
	for (int i = 0; i < bf.MaxPower; ++i) {
		if (bf.IsMember(i)) {
			if (!first) ostr << " ";
			ostr << i;
			first = false;
		}
	}
	return ostr;
}