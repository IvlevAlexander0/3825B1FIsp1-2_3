#include "pch.h"

#include "../../includes/Lab1/tbitfield.h"
#include "../../includes/Lab1/tset.h"
#include <sstream>
#include <stdexcept>

TEST(TBitField, Constructor)
{
    TBitField bf(10);
    EXPECT_EQ(bf.GetLength(), 10);
}

TEST(TBitField, SetBit)
{
    TBitField bf(5);
    bf.SetBit(2);
    EXPECT_EQ(bf.GetBit(2), 1);
}

TEST(TBitField, ClearBit)
{
    TBitField bf(5);
    bf.SetBit(2);
    bf.ClrBit(2);
    EXPECT_EQ(bf.GetBit(2), 0);
}

TEST(TBitField, GetBit)
{
    TBitField bf(5);
    bf.SetBit(3);
    EXPECT_EQ(bf.GetBit(3), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
}

TEST(TBitField, CopyConstructor)
{
    TBitField bf(5);
    bf.SetBit(1);
    TBitField copy(bf);
    EXPECT_EQ(copy, bf);
}

TEST(TBitField, Assignment)
{
    TBitField bf1(5);
    bf1.SetBit(2);
    TBitField bf2(5);
    bf2 = bf1;
    EXPECT_EQ(bf2, bf1);
}

TEST(TBitField, Equality)
{
    TBitField bf1(5);
    TBitField bf2(5);
    EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, Inequality)
{
    TBitField bf1(5);
    TBitField bf2(5);
    bf1.SetBit(1);
    EXPECT_NE(bf1, bf2);
}

TEST(TBitField, BitwiseOr)
{
    TBitField bf1(4);
    TBitField bf2(4);
    bf1.SetBit(0);
    bf2.SetBit(2);

    TBitField result = bf1 | bf2;

    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(2), 1);
}

TEST(TBitField, BitwiseAnd)
{
    TBitField bf1(4);
    TBitField bf2(4);
    bf1.SetBit(1);
    bf1.SetBit(2);
    bf2.SetBit(2);

    TBitField result = bf1 & bf2;

    EXPECT_EQ(result.GetBit(1), 0);
    EXPECT_EQ(result.GetBit(2), 1);
}

TEST(TBitField, ZeroLength)
{
    TBitField bf(0);
    EXPECT_EQ(bf.GetLength(), 0);
}

TEST(TBitField, FirstAndLastBit)
{
    TBitField bf(5);

    bf.SetBit(0);
    bf.SetBit(4);

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(4), 1);
    EXPECT_EQ(bf.GetBit(2), 0);
}

TEST(TBitField, NegativeIndexThrows)
{
    TBitField bf(5);
    EXPECT_THROW(bf.SetBit(-1), std::out_of_range);
}

TEST(TBitField, IndexEqualToLengthThrows)
{
    TBitField bf(5);
    EXPECT_THROW(bf.SetBit(5), std::out_of_range);
}

TEST(TBitField, GetBitOutOfRangeThrows)
{
    TBitField bf(5);
    EXPECT_THROW(bf.GetBit(5), std::out_of_range);
}

TEST(TBitField, ClearBitOutOfRangeThrows)
{
    TBitField bf(5);
    EXPECT_THROW(bf.ClrBit(-1), std::out_of_range);
}

TEST(TBitField, CopyIsIndependent)
{
    TBitField original(5);
    original.SetBit(2);

    TBitField copy(original);
    copy.ClrBit(2);

    EXPECT_EQ(original.GetBit(2), 1);
    EXPECT_EQ(copy.GetBit(2), 0);
}

TEST(TBitField, SelfAssignment)
{
    TBitField bf(5);
    bf.SetBit(2);

    bf = bf;

    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetLength(), 5);
}

TEST(TBitField, AssignmentDifferentLengths)
{
    TBitField source(7);
    source.SetBit(6);

    TBitField destination(3);
    destination = source;

    EXPECT_EQ(destination.GetLength(), 7);
    EXPECT_EQ(destination.GetBit(6), 1);
}

TEST(TBitField, Complement)
{
    TBitField bf(4);
    bf.SetBit(1);

    TBitField result = ~bf;

    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(1), 0);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(3), 1);
}

TEST(TBitField, OrDifferentLengthsThrows)
{
    TBitField bf1(4);
    TBitField bf2(5);

    EXPECT_THROW(bf1 | bf2, std::invalid_argument);
}

TEST(TBitField, AndDifferentLengthsThrows)
{
    TBitField bf1(4);
    TBitField bf2(5);

    EXPECT_THROW(bf1 & bf2, std::invalid_argument);
}

TEST(TBitField, InputAndOutput)
{
    TBitField bf(5);

    std::istringstream input("10101");
    input >> bf;

    EXPECT_TRUE(input.good() || input.eof());

    EXPECT_EQ(bf.GetBit(4), 1);
    EXPECT_EQ(bf.GetBit(3), 0);
    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(0), 1);

    std::ostringstream output;
    output << bf;

    EXPECT_EQ(output.str(), "10101");
}

TEST(TBitField, InputInvalidCharacter)
{
    TBitField bf(3);

    std::istringstream input("10x");
    input >> bf;

    EXPECT_TRUE(input.fail());
}

TEST(TBitField, LengthAcrossMemoryBoundary)
{
    const int bitsPerElement = sizeof(TELEM) * 8;
    TBitField bf(bitsPerElement + 1);

    bf.SetBit(0);
    bf.SetBit(bitsPerElement);

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(bitsPerElement), 1);
}


TEST(TSet, Constructor)
{
    TSet s(10);
    EXPECT_EQ(s.GetMaxPower(), 10);
}

TEST(TSet, InsertElement)
{
    TSet s(10);
    s.InsElem(3);
    EXPECT_EQ(s.IsMember(3), 1);
}

TEST(TSet, DeleteElement)
{
    TSet s(10);
    s.InsElem(3);
    s.DelElem(3);
    EXPECT_EQ(s.IsMember(3), 0);
}

TEST(TSet, IsMember)
{
    TSet s(10);
    s.InsElem(4);
    EXPECT_EQ(s.IsMember(4), 1);
    EXPECT_EQ(s.IsMember(5), 0);
}

TEST(TSet, CopyConstructor)
{
    TSet s(10);
    s.InsElem(2);
    TSet copy(s);
    EXPECT_EQ(copy, s);
}

TEST(TSet, Assignment)
{
    TSet s1(10);
    s1.InsElem(2);
    TSet s2(10);
    s2 = s1;
    EXPECT_EQ(s2, s1);
}

TEST(TSet, Equality)
{
    TSet s1(10);
    TSet s2(10);
    EXPECT_EQ(s1, s2);
}

TEST(TSet, Inequality)
{
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1);
    EXPECT_NE(s1, s2);
}

TEST(TSet, Union)
{
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1);
    s2.InsElem(2);

    TSet result = s1 + s2;

    EXPECT_EQ(result.IsMember(1), 1);
    EXPECT_EQ(result.IsMember(2), 1);
}

TEST(TSet, Intersection)
{
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1);
    s1.InsElem(2);
    s2.InsElem(2);

    TSet result = s1 * s2;

    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(2), 1);
}

TEST(TSet, EmptySet)
{
    TSet s(0);
    EXPECT_EQ(s.GetMaxPower(), 0);
}

TEST(TSet, FirstAndLastElement)
{
    TSet s(10);

    s.InsElem(0);
    s.InsElem(9);

    EXPECT_EQ(s.IsMember(0), 1);
    EXPECT_EQ(s.IsMember(9), 1);
    EXPECT_EQ(s.IsMember(5), 0);
}

TEST(TSet, InsertOutOfRangeThrows)
{
    TSet s(5);

    EXPECT_THROW(s.InsElem(5), std::out_of_range);
}

TEST(TSet, DeleteOutOfRangeThrows)
{
    TSet s(5);

    EXPECT_THROW(s.DelElem(-1), std::out_of_range);
}

TEST(TSet, UnionWithElement)
{
    TSet s(5);
    s.InsElem(1);

    TSet result = s + 3;

    EXPECT_EQ(result.IsMember(1), 1);
    EXPECT_EQ(result.IsMember(3), 1);
    EXPECT_EQ(s.IsMember(3), 0);
}

TEST(TSet, DifferenceWithElement)
{
    TSet s(5);
    s.InsElem(1);
    s.InsElem(3);

    TSet result = s - 1;

    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(3), 1);
    EXPECT_EQ(s.IsMember(1), 1);
}

TEST(TSet, Complement)
{
    TSet s(4);
    s.InsElem(1);
    s.InsElem(3);

    TSet result = ~s;

    EXPECT_EQ(result.IsMember(0), 1);
    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(3), 0);
}

TEST(TSet, UnionDifferentPowersThrows)
{
    TSet s1(4);
    TSet s2(5);

    EXPECT_THROW(s1 + s2, std::invalid_argument);
}

TEST(TSet, IntersectionDifferentPowersThrows)
{
    TSet s1(4);
    TSet s2(5);

    EXPECT_THROW(s1 * s2, std::invalid_argument);
}

TEST(TSet, SelfAssignment)
{
    TSet s(5);
    s.InsElem(2);

    s = s;

    EXPECT_EQ(s.GetMaxPower(), 5);
    EXPECT_EQ(s.IsMember(2), 1);
}

TEST(TSet, AssignmentDifferentPowers)
{
    TSet source(7);
    source.InsElem(6);

    TSet destination(3);
    destination = source;

    EXPECT_EQ(destination.GetMaxPower(), 7);
    EXPECT_EQ(destination.IsMember(6), 1);
}

TEST(TSet, CopyIsIndependent)
{
    TSet original(5);
    original.InsElem(2);

    TSet copy(original);
    copy.DelElem(2);

    EXPECT_EQ(original.IsMember(2), 1);
    EXPECT_EQ(copy.IsMember(2), 0);
}

TEST(TSet, EmptySetUnion)
{
    TSet empty(5);
    TSet other(5);
    other.InsElem(2);

    TSet result = empty + other;

    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(1), 0);
}

TEST(TSet, EmptySetIntersection)
{
    TSet s1(5);
    TSet s2(5);
    s2.InsElem(2);

    TSet result = s1 * s2;

    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(result.IsMember(i), 0);
}

TEST(TSet, InputAndOutput)
{
    TSet s(5);

    std::istringstream input("10101");
    input >> s;

    EXPECT_TRUE(input.good() || input.eof());

    EXPECT_EQ(s.IsMember(4), 1);
    EXPECT_EQ(s.IsMember(3), 0);
    EXPECT_EQ(s.IsMember(2), 1);
    EXPECT_EQ(s.IsMember(1), 0);
    EXPECT_EQ(s.IsMember(0), 1);

    std::ostringstream output;
    output << s;

    EXPECT_EQ(output.str(), "10101");
}
