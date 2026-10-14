#include "tset.h"

using namespace std;

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const
{
  return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem)
{
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
  BitField.ClrBit(Elem);
}

TSet& TSet::operator=(const TSet &s)
{
  MaxPower = s.MaxPower;
  BitField = s.BitField;
  return *this;
}

int TSet::operator==(const TSet &s) const
{
  return MaxPower == s.MaxPower && BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const
{
  return !(*this == s);
}

TSet TSet::operator+(const TSet &s)
{
  return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem)
{
  TSet res(*this);
  res.InsElem(Elem);
  return res;
}

TSet TSet::operator-(const int Elem)
{
  TSet res(*this);
  res.DelElem(Elem);
  return res;
}

TSet TSet::operator*(const TSet &s)
{
  return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void)
{
  return TSet(~BitField);
}

istream &operator>>(istream &istr, TSet &s)
{
  int count, elem;
  istr >> count;
  for (int i = 0; i < count; i++)
  {
    istr >> elem;
    s.InsElem(elem);
  }
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s)
{
  ostr << "{ ";
  for (int i = 0; i < s.MaxPower; i++)
    if (s.IsMember(i))
      ostr << i << " ";
  ostr << "}";
  return ostr;
}
