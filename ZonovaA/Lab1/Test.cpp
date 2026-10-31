#include <gtest/gtest.h>
#include <sstream>  //тестирование потоков ввода/вывода
#include "../../includes/Lab1/tbitfield.h"
#include "../../includes/Lab1/tset.h"

using namespace std;

TEST(TBFTest, GetLenBit) { //проверка, что конструктор создает поле нужной длины со всеми битами - нулями
    TBitField bf(1000);
    EXPECT_EQ(bf.GetLength(), 1000);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(bf.GetBit(i), 0);
    }
}

TEST(TBFTest, SetGet) { //проверка, что методы set - установить и get - получить корректны
    TBitField bf(50);
    bf.SetBit(0);
    bf.SetBit(4);

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(4), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(2), 0);
    EXPECT_EQ(bf.GetBit(49), 0);
}

TEST(TBFTest, ClrBit) { //очищение бита работает
    TBitField bf(5);
    bf.SetBit(3);
    EXPECT_EQ(bf.GetBit(3), 1);
    bf.SetBit(4);
    bf.ClrBit(3);

    EXPECT_EQ(bf.GetBit(3), 0);
    EXPECT_EQ(bf.GetBit(4), 1);
}

TEST(TBFTest, Copy) { //конструктор копирования
    TBitField bf1(5);
    bf1.SetBit(2);
    EXPECT_EQ(bf1.GetBit(2), 1);

    TBitField bf2(bf1); //копирование

    EXPECT_EQ(bf2.GetBit(2), 1);
    EXPECT_EQ(bf2.GetBit(4), 0);
    bf2.SetBit(4);      
    EXPECT_EQ(bf2.GetBit(4), 1);
    EXPECT_EQ(bf1.GetBit(4), 0);
}

TEST(TBFTest, OperPris) { //проверка оператора присваивания
    TBitField bf1(5);
    bf1.SetBit(4);
    EXPECT_EQ(bf1.GetBit(4), 1);
    TBitField bf2(5);
    bf2 = bf1;
    EXPECT_EQ(bf2.GetBit(4), 1);

    bf1 = bf1;
    EXPECT_EQ(bf1.GetBit(4), 1);
}

TEST(TBFTest, OAN) { //битовые операции
    TBitField bf1(5);
    bf1.SetBit(1); 
    bf1.SetBit(2); // 0110

    TBitField bf2(5);
    bf2.SetBit(2); 
    bf2.SetBit(3); // 1100

    //объединение
    TBitField bf_or = bf1 | bf2;
    EXPECT_EQ(bf_or.GetBit(0), 0);
    EXPECT_EQ(bf_or.GetBit(1), 1);
    EXPECT_EQ(bf_or.GetBit(2), 1);
    EXPECT_EQ(bf_or.GetBit(3), 1);
    EXPECT_EQ(bf_or.GetBit(4), 0);

    //пересечение
    TBitField bf_and = bf1 & bf2;
    EXPECT_EQ(bf_and.GetBit(0), 0);
    EXPECT_EQ(bf_and.GetBit(1), 0);
    EXPECT_EQ(bf_and.GetBit(2), 1);
    EXPECT_EQ(bf_and.GetBit(3), 0);
    EXPECT_EQ(bf_and.GetBit(4), 0);

    //инверсия
    TBitField bf_not = ~bf1;
    EXPECT_EQ(bf_not.GetBit(0), 1);
    EXPECT_EQ(bf_not.GetBit(1), 0);
    EXPECT_EQ(bf_not.GetBit(2), 0);
    EXPECT_EQ(bf_not.GetBit(3), 1);
    EXPECT_EQ(bf_not.GetBit(4), 1);
}

TEST(TBFTest, OperSrav) { //операторы сравнения
    TBitField bf1(5); 
    bf1.SetBit(4);
    TBitField bf2(5); 
    bf2.SetBit(4);
    TBitField bf3(5); 
    bf3.SetBit(3);

    EXPECT_TRUE(bf1 == bf2);
    EXPECT_FALSE(bf1 == bf3);
    EXPECT_TRUE(bf1 != bf3);
}





TEST(TSTest, ConstrBOper) { //проверка создания множества определенной мощности
    TSet s(5);
    EXPECT_EQ(s.GetMaxPower(), 5); //максимальная мощность множества

    s.InsElem(3); //добавить элемент
    s.InsElem(4);

    EXPECT_TRUE(s.IsMember(3)); //наличие элемента
    EXPECT_TRUE(s.IsMember(4));
    EXPECT_FALSE(s.IsMember(2));

    s.DelElem(3); //удалить элемнт
    EXPECT_FALSE(s.IsMember(3));
}

TEST(TSTest, CConstrPris) { //проверка конструктора копирования и оператор присваивания
    TSet s1(5);
    s1.InsElem(2);
    EXPECT_TRUE(s1.IsMember(2));
    TSet s2(s1);
    EXPECT_TRUE(s2.IsMember(2));
    s2.InsElem(3);
    EXPECT_FALSE(s1.IsMember(3));

    TSet s3(5);
    s3 = s1;
    EXPECT_TRUE(s3.IsMember(2));
}

TEST(TSTest, OperPM) { //добавить, удалить элемент
    TSet s(6);
    s.InsElem(1);

    TSet s_plus = s + 5;
    EXPECT_TRUE(s_plus.IsMember(1));
    EXPECT_TRUE(s_plus.IsMember(5));
    EXPECT_FALSE(s.IsMember(5));

    TSet s_minus = s_plus - 1;
    EXPECT_FALSE(s_minus.IsMember(1));
    EXPECT_TRUE(s_minus.IsMember(5));
    EXPECT_TRUE(s_plus.IsMember(1));
}

TEST(TSTest, OperM) { //теоретико-множественные операции
    TSet A(10); 
    A.InsElem(1); 
    A.InsElem(2);
    TSet B(10); 
    B.InsElem(2); 
    B.InsElem(3);

    EXPECT_NO_THROW(A + B);
    EXPECT_NO_THROW(A * B);
    //объединение
    TSet C = A + B;
    EXPECT_TRUE(C.IsMember(1));
    EXPECT_TRUE(C.IsMember(2));
    EXPECT_TRUE(C.IsMember(3));

    //пересечение
    TSet D = A * B;
    EXPECT_TRUE(D.IsMember(2));
    EXPECT_FALSE(D.IsMember(1));
    EXPECT_FALSE(D.IsMember(3));

    //дополнение
    TSet E(5); 
    E.InsElem(0); 
    E.InsElem(2); // {0, 2}
    TSet otr = ~E; // Должно быть {1, 3, 4}
    EXPECT_FALSE(otr.IsMember(0));
    EXPECT_TRUE(otr.IsMember(1));
    EXPECT_FALSE(otr.IsMember(2));
    EXPECT_TRUE(otr.IsMember(3));
    EXPECT_TRUE(otr.IsMember(4));
}

TEST(TSTest, OperSrav) { //операторы сравнения
    TSet s1(10); 
    s1.InsElem(5);
    TSet s2(10); 
    s2.InsElem(5);
    TSet s3(10); 
    s3.InsElem(6);
    EXPECT_NO_THROW(s1 == s2);
    EXPECT_NO_THROW(s2 != s3);
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_TRUE(s2 != s3);
}

TEST(TSTest, ConBF) { //преобразование типов
    TBitField bf(10);
    bf.SetBit(4);
    bf.SetBit(8);

    //конструктор из битового поля
    TSet s(bf);
    EXPECT_TRUE(s.IsMember(4));
    EXPECT_TRUE(s.IsMember(8));
    EXPECT_EQ(s.GetMaxPower(), 10);

    //оператор преобразования в битовое поле
    TBitField bf2 = (TBitField)s;
    EXPECT_EQ(bf2.GetBit(4), 1);
    EXPECT_EQ(bf2.GetBit(8), 1);
}

TEST(TSTest, Univers) { //проверка для разных универсов
    TSet A(10);  
    TSet B(20);  
    A.InsElem(5);
    B.InsElem(15);
    
    EXPECT_THROW(A + B, std::invalid_argument);
    EXPECT_THROW(A * B, std::invalid_argument);
    EXPECT_THROW(A == B, std::invalid_argument);
    EXPECT_THROW(A != B, std::invalid_argument);
}
TEST(TSTest, UniversR) {
    TSet A(10);
    TSet B(10);  

    A.InsElem(1);
    A.InsElem(2);
    B.InsElem(2);
    B.InsElem(3);

    EXPECT_NO_THROW(A + B);
    EXPECT_NO_THROW(A * B);
    EXPECT_NO_THROW(A == B);
    EXPECT_NO_THROW(A != B);

    TSet C = A + B;
    EXPECT_EQ(C.GetMaxPower(), 10);
    EXPECT_TRUE(C.IsMember(1));
    EXPECT_TRUE(C.IsMember(2));
    EXPECT_TRUE(C.IsMember(3));

    TSet D = A * B;
    EXPECT_EQ(D.GetMaxPower(), 10);
    EXPECT_TRUE(D.IsMember(2));
    EXPECT_FALSE(D.IsMember(1));
    EXPECT_FALSE(D.IsMember(3));
}



TEST(TSEx, InpInv) { //ввод недопустимого значения
    TSet s(10);
    std::istringstream bad("1 2 A 3");
    
    EXPECT_THROW(bad >> s, std::invalid_argument);
}

TEST(TSEx, InpThr) { //выход за пределы мощности
    TSet s(5); 
    std::istringstream bad("1 3 6 -1"); 

    EXPECT_THROW(bad >> s, std::out_of_range);
}

TEST(TSEx, InpStop) { //ввод корректно останавливается при встрече отрицательного числа
    TSet s(10);
    std::istringstream good("1 3 5 -1 8");
    good >> s;

    EXPECT_TRUE(s.IsMember(1));
    EXPECT_TRUE(s.IsMember(3));
    EXPECT_TRUE(s.IsMember(5));
    EXPECT_FALSE(s.IsMember(8)); // 8 не должна добавиться
}


