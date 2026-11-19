#include "pch.h"
#include "../Laba1/tset_realiz.h"
#include "../Laba1/tbitfield_realiz.h"
#include "random"

int GetRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

TEST(TBitField, Test_Correct_Length) {
    int randomLen = GetRandomInt(1, 1000);
    ASSERT_NO_THROW(TBitField bf(randomLen));
}

TEST(TBitField, Test_Correct_Length_Zero) {
    int randomLen = 0;
    ASSERT_NO_THROW(TBitField bf(randomLen));
}

TEST(TBitField, Test_Incorrect_Length) {
    int randomNegative = -GetRandomInt(1, 1000);
    ASSERT_ANY_THROW(TBitField bf(randomNegative));
}

TEST(TBitField, Test_Get_Length) {
    int randomLen = GetRandomInt(5, 500);
    TBitField bf(randomLen);
    EXPECT_EQ(randomLen, bf.GetLength());
}

TEST(TBitField, Test_Set_And_Get_Bit) {
    int len = GetRandomInt(20, 100);
    TBitField bf(len);
    int randomBitIndex = GetRandomInt(0, len - 1);

    bf.SetBit(randomBitIndex);
    EXPECT_EQ(1, bf.GetBit(randomBitIndex));
}

TEST(TBitField, Test_Clear_Bit) {
    int len = GetRandomInt(20, 100);
    TBitField bf(len);
    int randomBitIndex = GetRandomInt(0, len - 1);

    bf.SetBit(randomBitIndex);
    bf.ClrBit(randomBitIndex);
    EXPECT_EQ(0, bf.GetBit(randomBitIndex));
}

TEST(TBitField, Test_Bit_Out_Of_Bounds) {
    int len = 32;
    TBitField bf(len);

    //конкретные случаи
    ASSERT_NO_THROW(bf.SetBit(0));
    ASSERT_NO_THROW(bf.SetBit(len - 1));

    ASSERT_ANY_THROW(bf.SetBit(len));
    ASSERT_ANY_THROW(bf.SetBit(-1));
    ASSERT_ANY_THROW(bf.GetBit(len));
    ASSERT_ANY_THROW(bf.GetBit(-1));
}

TEST(TBitField, Test_Operator_Equal) {
    int len = GetRandomInt(10, 100);
    TBitField bf1(len);
    TBitField bf2(len);

    int bitIndex = GetRandomInt(0, len - 1);
    bf1.SetBit(bitIndex);
    bf2.SetBit(bitIndex);

    EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, Test_Operator_Or) {
    int len = GetRandomInt(20, 100);
    TBitField bf1(len);
    TBitField bf2(len);

    int b1 = GetRandomInt(0, len / 2);
    int b2 = GetRandomInt(len / 2 + 1, len - 1);

    bf1.SetBit(b1);
    bf2.SetBit(b2);

    TBitField res = bf1 | bf2;
    EXPECT_EQ(1, res.GetBit(b1));
    EXPECT_EQ(1, res.GetBit(b2));
}

TEST(TBitField, Test_Operator_And) {
    int len = GetRandomInt(20, 100);
    TBitField bf1(len);
    TBitField bf2(len);

    int commonBit = GetRandomInt(0, len - 1);
    bf1.SetBit(commonBit);
    bf2.SetBit(commonBit);

    int uniqueBit = (commonBit + 1) % len;
    bf1.SetBit(uniqueBit);

    TBitField res = bf1 & bf2;
    EXPECT_EQ(1, res.GetBit(commonBit));
    EXPECT_EQ(0, res.GetBit(uniqueBit));
}

TEST(TBitField, Test_Operator_Inverse) {
    int len = GetRandomInt(10, 50);
    TBitField bf(len);
    int bitIndex = GetRandomInt(0, len - 1);
    bf.SetBit(bitIndex);

    TBitField res = ~bf;
    EXPECT_EQ(0, res.GetBit(bitIndex));
}

TEST(TSet, Test_Correct_MaxPower) {
    int randomPower = GetRandomInt(1, 500);
    ASSERT_NO_THROW(TSet s(randomPower));
}

TEST(TSet, Test_Correct_MaxPower_Zero) {
    int randomPower = 0;
    ASSERT_NO_THROW(TSet s(randomPower));
}

TEST(TSet, Test_Incorrect_MaxPower) {
    int randomNegative = -GetRandomInt(1, 500);
    ASSERT_ANY_THROW(TSet s(randomNegative));
}

TEST(TSet, Test_Get_MaxPower) {
    int randomPower = GetRandomInt(5, 200);
    TSet s(randomPower);
    EXPECT_EQ(randomPower, s.GetMaxPower());
}

TEST(TSet, Test_Insert_And_IsMember) {
    int power = GetRandomInt(20, 100);
    TSet s(power);
    int elem = GetRandomInt(0, power - 1);

    s.InsElem(elem);
    EXPECT_TRUE(s.IsMember(elem));
}

TEST(TSet, Test_Delete_Element) {
    int power = GetRandomInt(20, 100);
    TSet s(power);
    int elem = GetRandomInt(0, power - 1);

    s.InsElem(elem);
    s.DelElem(elem);
    EXPECT_FALSE(s.IsMember(elem));
}

TEST(TSet, Test_Element_Out_Of_Bounds) {
    int power = 32;
    TSet s(power);

    ASSERT_NO_THROW(s.InsElem(0));
    ASSERT_NO_THROW(s.InsElem(power - 1));

    ASSERT_ANY_THROW(s.InsElem(power));
    ASSERT_ANY_THROW(s.InsElem(-1));
    ASSERT_ANY_THROW(s.IsMember(power));
    ASSERT_ANY_THROW(s.DelElem(power));
}

TEST(TSet, Test_Operator_Union) {
    int power = GetRandomInt(20, 100);
    TSet s1(power);
    TSet s2(power);

    int e1 = GetRandomInt(0, power / 2);
    int e2 = GetRandomInt(power / 2 + 1, power - 1);

    s1.InsElem(e1);
    s2.InsElem(e2);

    TSet res = s1 + s2;
    EXPECT_TRUE(res.IsMember(e1));
    EXPECT_TRUE(res.IsMember(e2));
}

TEST(TSet, Test_Operator_Intersection) {
    int power = GetRandomInt(20, 100);
    TSet s1(power);
    TSet s2(power);

    int commonElem = GetRandomInt(0, power - 1);
    s1.InsElem(commonElem);
    s2.InsElem(commonElem);

    TSet res = s1 * s2;
    EXPECT_TRUE(res.IsMember(commonElem));
}

TEST(TSet, Test_Operator_Inverse) {
    int power = GetRandomInt(10, 50);
    TSet s(power);
    int elem = GetRandomInt(0, power - 1);
    s.InsElem(elem);

    TSet res = ~s;
    EXPECT_FALSE(res.IsMember(elem));
}