#include "pch.h" 
#include "../Lab1/tset_reliz.h"
#include "../Lab1/tbitfield_reliz.h"
#include <sstream>
#include <stdexcept>

// TBitField 

TEST(TBitField, Constructor_Valid) {
    EXPECT_NO_THROW(TBitField bf(1));
    EXPECT_NO_THROW(TBitField bf(32));
    EXPECT_NO_THROW(TBitField bf(33)); 
}

TEST(TBitField, Constructor_Negative_Throws) {
    EXPECT_THROW(TBitField bf(-1), std::invalid_argument);
}

TEST(TBitField, GetLength) {
    TBitField bf(10);
    EXPECT_EQ(10, bf.GetLength());
}

TEST(TBitField, SetAndGetBit_Boundaries) {
    TBitField bf(32);
    bf.SetBit(0);
    bf.SetBit(31);
    EXPECT_EQ(1, bf.GetBit(0));
    EXPECT_EQ(1, bf.GetBit(31));
    EXPECT_EQ(0, bf.GetBit(1));
}

TEST(TBitField, OutOfBounds_Throws) {
    TBitField bf(32);
    EXPECT_THROW(bf.SetBit(32), std::out_of_range);
    EXPECT_THROW(bf.SetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.GetBit(32), std::out_of_range);
}

TEST(TBitField, ClearBit) {
    TBitField bf(10);
    bf.SetBit(5);
    bf.ClrBit(5);
    EXPECT_EQ(0, bf.GetBit(5));
}

TEST(TBitField, CopyConstructor_DeepCopy) {
    TBitField bf1(10);
    bf1.SetBit(1);
    TBitField bf2(bf1);
    bf2.SetBit(2);

    EXPECT_EQ(1, bf2.GetBit(1));
    EXPECT_EQ(1, bf2.GetBit(2));
    EXPECT_EQ(0, bf1.GetBit(2)); 
}

TEST(TBitField, OperatorAssign_DeepCopy) {
    TBitField bf1(10), bf2(10);
    bf1.SetBit(1);
    bf2 = bf1;
    bf2.SetBit(2);

    EXPECT_EQ(0, bf1.GetBit(2)); 
}

TEST(TBitField, Operator_Or) {
    TBitField bf1(10), bf2(10);
    bf1.SetBit(1);
    bf2.SetBit(2);
    TBitField res = bf1 | bf2;
    EXPECT_EQ(1, res.GetBit(1));
    EXPECT_EQ(1, res.GetBit(2));
    EXPECT_EQ(0, res.GetBit(3));
}

TEST(TBitField, Operator_And) {
    TBitField bf1(10), bf2(10);
    bf1.SetBit(1); bf1.SetBit(2);
    bf2.SetBit(2); bf2.SetBit(3);
    TBitField res = bf1 & bf2;
    EXPECT_EQ(0, res.GetBit(1));
    EXPECT_EQ(1, res.GetBit(2));
    EXPECT_EQ(0, res.GetBit(3));
}

TEST(TBitField, Stream_Input_Output) {
    TBitField bf(5);
    std::istringstream in("10101");
    in >> bf;
    EXPECT_EQ(1, bf.GetBit(0));
    EXPECT_EQ(0, bf.GetBit(1));
    EXPECT_EQ(1, bf.GetBit(2));

    std::ostringstream out;
    out << bf;
    EXPECT_EQ("10101", out.str());
}

// TSet

TEST(TSet, Constructor_And_MaxPower) {
    TSet s(20);
    EXPECT_EQ(20, s.GetMaxPower());
    EXPECT_THROW(TSet(-1), std::invalid_argument);
}

TEST(TSet, InsElem_IsMember_DelElem) {
    TSet s(10);
    s.InsElem(3);
    EXPECT_TRUE(s.IsMember(3));
    s.DelElem(3);
    EXPECT_FALSE(s.IsMember(3));
}

TEST(TSet, Element_OutOfBounds_Throws) {
    TSet s(10);
    EXPECT_THROW(s.InsElem(10), std::out_of_range);
    EXPECT_THROW(s.InsElem(-1), std::out_of_range);
}

TEST(TSet, Operator_Union_WithElement) {
    TSet s(10);
    s.InsElem(1);
    TSet res = s + 5;
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(5));
    EXPECT_FALSE(s.IsMember(5)); 
}

TEST(TSet, Operator_Union_Set) {
    TSet s1(10), s2(10);
    s1.InsElem(1);
    s2.InsElem(2);
    TSet res = s1 + s2;
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(2));
}

TEST(TSet, Operator_Intersection_Set) {
    TSet s1(10), s2(10);
    s1.InsElem(1); s1.InsElem(2);
    s2.InsElem(2); s2.InsElem(3);
    TSet res = s1 * s2;
    EXPECT_FALSE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(2));
    EXPECT_FALSE(res.IsMember(3));
}

TEST(TSet, Operator_Complement) {
    TSet s(5);
    s.InsElem(1);
    TSet res = ~s;
    EXPECT_FALSE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(0));
    EXPECT_TRUE(res.IsMember(4));
}

TEST(TSet, Stream_Input_Output) {
    TSet s(10);
    std::istringstream in("{1, 3, 5}");
    in >> s;

    std::ostringstream out;
    out << s;
    EXPECT_EQ("{1, 3, 5}", out.str());
}