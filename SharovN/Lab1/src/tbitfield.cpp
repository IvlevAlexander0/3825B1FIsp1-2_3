#include "tbitfield.h"

#include <stdexcept>

using namespace std;

const int BITS_IN_ELEM = sizeof(TELEM) * 8;

TBitField::TBitField(int len)
{
  if (len < 0)
    throw invalid_argument("negative length");
  BitLen = len;
  MemLen = (len + BITS_IN_ELEM - 1) / BITS_IN_ELEM;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf)
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const
{
  return n / BITS_IN_ELEM;
}

TELEM TBitField::GetMemMask(const int n) const
{
  return 1u << (n % BITS_IN_ELEM);
}

int TBitField::GetLength(void) const
{
  return BitLen;
}

void TBitField::SetBit(const int n)
{
  if (n < 0 || n >= BitLen)
    throw out_of_range("wrong bit index");
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
  if (n < 0 || n >= BitLen)
    throw out_of_range("wrong bit index");
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
  if (n < 0 || n >= BitLen)
    throw out_of_range("wrong bit index");
  if (pMem[GetMemIndex(n)] & GetMemMask(n))
    return 1;
  return 0;
}

TBitField& TBitField::operator=(const TBitField &bf)
{
  if (this != &bf)
  {
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
      pMem[i] = bf.pMem[i];
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const
{
  if (BitLen != bf.BitLen)
    return 0;
  for (int i = 0; i < MemLen; i++)
    if (pMem[i] != bf.pMem[i])
      return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf)
{
  int len = BitLen;
  if (bf.BitLen > len)
    len = bf.BitLen;
  TBitField res(len);
  for (int i = 0; i < MemLen; i++)
    res.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    res.pMem[i] |= bf.pMem[i];
  return res;
}

TBitField TBitField::operator&(const TBitField &bf)
{
  int len = BitLen;
  if (bf.BitLen > len)
    len = bf.BitLen;
  int minMemLen = MemLen;
  if (bf.MemLen < minMemLen)
    minMemLen = bf.MemLen;
  TBitField res(len);
  for (int i = 0; i < minMemLen; i++)
    res.pMem[i] = pMem[i] & bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void)
{
  TBitField res(BitLen);
  for (int i = 0; i < BitLen; i++)
    if (GetBit(i) == 0)
      res.SetBit(i);
  return res;
}

istream &operator>>(istream &istr, TBitField &bf)
{
  char c;
  for (int i = 0; i < bf.BitLen; i++)
  {
    istr >> c;
    if (c == '1')
      bf.SetBit(i);
    else
      bf.ClrBit(i);
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf)
{
  for (int i = 0; i < bf.BitLen; i++)
    ostr << bf.GetBit(i);
  return ostr;
}
