#include <gtest/gtest.h>
#include "tbitfield.h"
#include "tset.h"
#include <stdexcept>

//геенрация случайного числа в диапазоне, Автор: Князев Никита
int GetRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

//для класса TBitField

//создание битового поля заданной длины, Автор: Князев Никита
TEST(TBitField, Test_Create) {
    ASSERT_NO_THROW(TBitField bf(50));
}

//отрицательная длина должна дать исключение
TEST(TBitField, Test_Create_Negative_Length) {
    ASSERT_THROW(TBitField bf(-5), std::invalid_argument);
}

//нулевая длина допустима
TEST(TBitField, Test_Create_Zero_Length) {
    ASSERT_NO_THROW(TBitField bf(0));
}

//получение длины поля
TEST(TBitField, Test_Get_Length) {
    int randomLen = GetRandomInt(100, 400);
    TBitField bf(randomLen);
    EXPECT_EQ(randomLen, bf.GetLength());
}

//установка и получение бита, Автор: Князев Никита
TEST(TBitField, Test_Set_And_Get_Bit) {
    int len = GetRandomInt(20, 100);
    TBitField bf(len);
    int randomBitIndex = GetRandomInt(0, len - 1);
    bf.SetBit(randomBitIndex);
    EXPECT_EQ(1, bf.GetBit(randomBitIndex));
}

//очистка бита, Автор: Князев Никита
TEST(TBitField, Test_Clear_Bit) {
    int len = GetRandomInt(20, 100);
    TBitField bf(len);
    int randomBitIndex = GetRandomInt(0, len - 1);
    bf.SetBit(randomBitIndex);
    bf.ClrBit(randomBitIndex);
    EXPECT_EQ(0, bf.GetBit(randomBitIndex));
}

//выход за границы поля, Автор: Князев Никита
TEST(TBitField, Test_Bit_Out_Of_Bounds) {
    int len = 32;
    TBitField bf(len);

    ASSERT_NO_THROW(bf.SetBit(0));
    ASSERT_NO_THROW(bf.SetBit(len - 1));

    ASSERT_ANY_THROW(bf.SetBit(len));
    ASSERT_ANY_THROW(bf.SetBit(-1));
    ASSERT_ANY_THROW(bf.GetBit(len));
    ASSERT_ANY_THROW(bf.GetBit(-1));
}

//оператор равенства
TEST(TBitField, Test_Operator_Equal) {
    int len = GetRandomInt(20, 00);
    TBitField bf1(len);
    TBitField bf2(len);
    int bitIndex = GetRandomInt(0, len - 1);
    bf1.SetBit(bitIndex);
    bf2.SetBit(bitIndex);
    EXPECT_EQ(bf1, bf2);
}

//оператор неравенства
TEST(TBitField, Test_Operator_Not_Equal) {
    int len = GetRandomInt(20, 200);
    TBitField bf1(len);
    TBitField bf2(len);
    bf1.SetBit(5);
    bf2.SetBit(10);
    EXPECT_NE(bf1, bf2);
}

//оператор ИЛИ, Автор: Князев Никита
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

//оператор И, Автор: Князев Никита
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

//оператор НЕ, Автор: Марков Александр
TEST(TBitField, Test_Operator_Inverse) {
    int len = GetRandomInt(10, 50);
    TBitField bf(len);
    bf.SetBit(0);
    bf.SetBit(2);
    TBitField res = ~bf;
    EXPECT_EQ(0, res.GetBit(0));
    EXPECT_EQ(1, res.GetBit(1));
    EXPECT_EQ(0, res.GetBit(2));
    EXPECT_EQ(1, res.GetBit(3));
    EXPECT_EQ(1, res.GetBit(4));
}

//оператор присваивания
TEST(TBitField, Test_Operator_Assign) {
    int len = GetRandomInt(10, 50);
    TBitField bf1(len);
    bf1.SetBit(5);
    bf1.SetBit(10);

    TBitField bf2(len);
    bf2 = bf1;

    EXPECT_EQ(bf1, bf2);
    EXPECT_EQ(1, bf2.GetBit(5));
    EXPECT_EQ(1, bf2.GetBit(10));
}

//конструктор копирования
TEST(TBitField, Test_Copy_Constructor) {
    int len = GetRandomInt(10, 50);
    TBitField bf1(len);
    bf1.SetBit(3);
    bf1.SetBit(7);

    TBitField bf2(bf1);

    EXPECT_EQ(bf1, bf2);
    EXPECT_EQ(1, bf2.GetBit(3));
    EXPECT_EQ(1, bf2.GetBit(7));
}

//множественная установка битов
TEST(TBitField, Test_Multiple_Bits) {
    int len = 64;
    TBitField bf(len);
    for (int i = 0; i < len; i += 2) {
        bf.SetBit(i);
    }
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            EXPECT_EQ(1, bf.GetBit(i));
        }
        else {
            EXPECT_EQ(0, bf.GetBit(i));
        }
    }
}

//операция ИЛИ с разными полями (должно дать исключение)
TEST(TBitField, Test_Or_Different_Lengths) {
    TBitField bf1(10);
    TBitField bf2(20);
    ASSERT_ANY_THROW(bf1 | bf2);
}

// для класса TSet

//создание множества заданной мощности, Автор: Марков Александр
TEST(TSet, Test_Create_Set) {
    ASSERT_NO_THROW(TSet s(50));
}

//отрицательная мощность должна дать исключение
TEST(TSet, Test_Create_Negative_Power) {
    ASSERT_THROW(TSet s(-10), std::invalid_argument);
}

//включение элемента и проверка принадлежности, Автор: Марков Александр
TEST(TSet, Test_InsElem_IsMember) {
    TSet s(20);
    s.InsElem(7);
    EXPECT_TRUE(s.IsMember(7));
    EXPECT_FALSE(s.IsMember(6));
}

//удаление элемента, Автор: Марков Александр
TEST(TSet, Test_DelElem) {
    TSet s(20);
    s.InsElem(7);
    s.DelElem(7);
    EXPECT_FALSE(s.IsMember(7));
}

//выход элемента за границы множества, Автор: Князев Никита
TEST(TSet, Test_Element_Out_Of_Bounds) {
    int power = 32;
    TSet s(power);

    ASSERT_NO_THROW(s.InsElem(0));
    ASSERT_NO_THROW(s.InsElem(power - 1));

    ASSERT_ANY_THROW(s.InsElem(power));
    ASSERT_ANY_THROW(s.InsElem(-1));
    ASSERT_ANY_THROW(s.IsMember(power));
    ASSERT_ANY_THROW(s.IsMember(-1));
    ASSERT_ANY_THROW(s.DelElem(power));
    ASSERT_ANY_THROW(s.DelElem(-1));
}

//операция объединения множеств, Автор: Марков Александр
TEST(TSet, Test_Operation_Union) {
    TSet s1(10), s2(10);
    s1.InsElem(1);
    s2.InsElem(3);
    TSet res = s1 + s2;
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_FALSE(res.IsMember(2));
}

//операция пересечения множеств, Автор: Марков Александр
TEST(TSet, Test_Operation_Intersection) {
    TSet s1(10), s2(10);
    s1.InsElem(1);
    s1.InsElem(3);
    s2.InsElem(3);
    TSet res = s1 * s2;
    EXPECT_FALSE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(3));
}

//операция дополнения множества, Автор: Марков Александр
TEST(TSet, Test_Operation_Complement) {
    TSet s(5);
    s.InsElem(0);
    s.InsElem(2);
    TSet res = ~s;
    EXPECT_FALSE(res.IsMember(0));
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_FALSE(res.IsMember(2));
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(4));
}

//операция объединения с элементом, Автор: Князев Никита
TEST(TSet, Test_Operator_Union_With_Element) {
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

//операция пересечения с общим элементом, Автор: Князев Никита
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

//операция дополнения, Автор: Князев Никита
TEST(TSet, Test_Operator_Inverse) {
    int power = GetRandomInt(10, 50);
    TSet s(power);
    int elem = GetRandomInt(0, power - 1);
    s.InsElem(elem);
    TSet res = ~s;
    EXPECT_FALSE(res.IsMember(elem));
}

//оператор равенства множеств
TEST(TSet, Test_Operator_Equal) {
    int power = GetRandomInt(10, 50);
    TSet s1(power);
    TSet s2(power);
    s1.InsElem(5);
    s1.InsElem(10);
    s2.InsElem(5);
    s2.InsElem(10);
    EXPECT_EQ(s1, s2);
}

//оператор неравенства множеств
TEST(TSet, Test_Operator_Not_Equal) {
    int power = GetRandomInt(10, 50);
    TSet s1(power);
    TSet s2(power);
    s1.InsElem(5);
    s2.InsElem(10);
    EXPECT_NE(s1, s2);
}

//оператор присваивания множеств
TEST(TSet, Test_Operator_Assign) {
    int power = GetRandomInt(20, 50);
    TSet s1(power);
    s1.InsElem(5);
    s1.InsElem(10);

    TSet s2(power);
    s2 = s1;

    EXPECT_EQ(s1, s2);
    EXPECT_TRUE(s2.IsMember(5));
    EXPECT_TRUE(s2.IsMember(10));
}

//копирование множества
TEST(TSet, Test_Copy_Constructor) {
    int power = GetRandomInt(10, 50);
    TSet s1(power);
    s1.InsElem(3);
    s1.InsElem(7);

    TSet s2(s1);

    EXPECT_EQ(s1, s2);
    EXPECT_TRUE(s2.IsMember(3));
    EXPECT_TRUE(s2.IsMember(7));
}

//объединение множеств с разными мощностями (должно дать исключение)
TEST(TSet, Test_Union_Different_Powers) {
    TSet s1(10);
    TSet s2(20);
    ASSERT_ANY_THROW(s1 + s2);
}

//пересечение множеств с разными мощностями (должно дать исключение)
TEST(TSet, Test_Intersection_Different_Powers) {
    TSet s1(10);
    TSet s2(20);
    ASSERT_ANY_THROW(s1 * s2);
}

//пустое множество
TEST(TSet, Test_Empty_Set) {
    int power = GetRandomInt(10, 50);
    TSet s(power);

    for (int i = 0; i < power; i++) {
        EXPECT_FALSE(s.IsMember(i));
    }
}

//полное множество
TEST(TSet, Test_Full_Set) {
    int power = GetRandomInt(10, 50);
    TSet s(power);
    for (int i = 0; i < power; i++) {
        s.InsElem(i);
    }
    for (int i = 0; i < power; i++) {
        EXPECT_TRUE(s.IsMember(i));
    }
    TSet complement = ~s;
    for (int i = 0; i < power; i++) {
        EXPECT_FALSE(complement.IsMember(i));
    }
}

//операция разности с элементом
TEST(TSet, Test_Operator_Minus_Element) {
    int power = GetRandomInt(10, 50);
    TSet s(power);
    int elem = GetRandomInt(0, power - 1);
    s.InsElem(elem);

    TSet res = s - elem;
    EXPECT_FALSE(res.IsMember(elem));

    EXPECT_TRUE(s.IsMember(elem));
}

//получение максимальной мощности
TEST(TSet, Test_Get_Max_Power) {
    int power = GetRandomInt(10, 100);
    TSet s(power);
    EXPECT_EQ(power, s.GetMaxPower());
}

//множественные операций над множествами
TEST(TSet, Test_Multiple_Operations) {
    int power = 20;
    TSet s1(power);
    TSet s2(power);
    TSet s3(power);

    for (int i = 0; i < 10; i += 2) {  // s1 = {0, 2, 4, 6, 8}
        s1.InsElem(i);
    }
    for (int i = 1; i < 10; i += 2) {  // s2 = {1, 3, 5, 7, 9}
        s2.InsElem(i);
    }
    s3 = s1 + s2;  // s3 = s1 + s2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(s3.IsMember(i));
    }
    TSet intersection = s1 * s2;
    for (int i = 0; i < 10; i++) {
        EXPECT_FALSE(intersection.IsMember(i));
    }
}