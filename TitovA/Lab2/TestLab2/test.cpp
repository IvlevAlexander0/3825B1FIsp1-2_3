#include "pch.h"
#include "..\Project1\utmatrix.h"
#include "..\Project1\Lab2.cpp"
#include <sstream>
#include <stdexcept>

//проверка конструктора
TEST(TVector, create_v) {
    TVector<int> v(5, 2);
    EXPECT_EQ(v.GetSize(), 5);
    EXPECT_EQ(v.GetStartIndex(), 2);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[4], 0);
}

//доступ по индексу и выход за границы
TEST(TVector, vector_get) {
    TVector<int> v(4, 1);
    v[1] = 10; v[3] = 30;
    EXPECT_EQ(v[1], 10);
    EXPECT_EQ(v[3], 30);
    EXPECT_THROW(v[0], std::out_of_range);
    EXPECT_THROW(v[4], std::out_of_range);
}

//копирование и присваивание
TEST(TVector, vector_copy_assign) {
    TVector<int> a(4, 1);
    a[1] = 7; a[2] = 8;
    TVector<int> b(a);
    b[1] = 100;
    EXPECT_EQ(a[1], 7);
    EXPECT_EQ(b[1], 100);
    TVector<int> c;
    c = a;
    EXPECT_TRUE(c == a);
    c = c;
    EXPECT_TRUE(c == a);
}

//сравнение векторов
TEST(TVector, vector_compare) {
    TVector<int> a(3, 0), b(3, 0);
    a[0] = b[0] = 1;
    EXPECT_TRUE(a == b);
    b[2] = 4;
    EXPECT_TRUE(a != b);
}

// операции со скаляром
TEST(TVector, scalar) {
    TVector<int> a(4, 1);
    a[1] = 2; a[2] = 3; a[3] = 4;
    EXPECT_EQ((a + 2)[1], 4);
    EXPECT_EQ((a - 1)[2], 2);
    EXPECT_EQ((a * 3)[3], 12);
}

// операции с вектором и скалярное произведение
TEST(TVector, vector_operation) {
    TVector<int> a(4, 1), b(4, 1);
    a[1] = 1; a[2] = 2; a[3] = 3;
    b[1] = 4; b[2] = 5; b[3] = 6;
    EXPECT_EQ((a + b)[2], 7);
    EXPECT_EQ((a - b)[3], -3);
    EXPECT_EQ(a * b, 32);
}

//ошибка при разных диапазонах
TEST(TVector, vector_sizes_differ) {
    TVector<int> a(4, 1), b(4, 0);
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a * b, std::invalid_argument);
}

//вывод в поток
TEST(TVector, print) {
    TVector<int> v(4, 2);
    v[2] = 5; v[3] = 8;
    std::ostringstream out;
    out << v;
    EXPECT_EQ(out.str(), "0 0 5 8");
}

//ввод из потока
TEST(TVector, read) {
    TVector<int> v(4, 1);
    std::istringstream in("2 4 6");
    in >> v;
    ASSERT_FALSE(in.fail());
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[3], 6);
}

//создание матрицы
TEST(TMatrix, create_m) {
    TMatrix<int> m(3);
    EXPECT_EQ(m.GetSize(), 3);
    EXPECT_EQ(m[0].GetStartIndex(), 0);
    EXPECT_EQ(m[1].GetStartIndex(), 1);
    EXPECT_EQ(m[2].GetStartIndex(), 2);
    EXPECT_EQ(m[2][2], 0);
}

//проверяет, что хранится только верхняя часть
TEST(TMatrix, save_upper_part) {
    TMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][1] = 4; m[1][2] = 5; m[2][2] = 6;
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][1], 4);
    EXPECT_THROW(m[2][1], std::out_of_range);
}

//копирование и присваивание матриц
TEST(TMatrix, copy_assign) {
    TMatrix<int> a(2);
    a[0][0] = 1; a[0][1] = 2; a[1][1] = 3;
    TMatrix<int> b(a);
    b[0][0] = 10;
    EXPECT_EQ(a[0][0], 1);
    EXPECT_EQ(b[0][0], 10);
    TMatrix<int> c(4);
    c = a;
    EXPECT_TRUE(c == a);
    c = c;
    EXPECT_TRUE(c == a);
}

//сравнение матриц
TEST(TMatrix, compare) {
    TMatrix<int> a(2), b(2);
    a[0][0] = b[0][0] = 1;
    a[1][1] = b[1][1] = 2;
    EXPECT_TRUE(a == b);
    b[1][1] = 3;
    EXPECT_TRUE(a != b);
}

//сложение и вычитание
TEST(TMatrix, operetion) {
    TMatrix<int> a(2), b(2);
    a[0][0] = 1; a[0][1] = 2; a[1][1] = 3;
    b[0][0] = 4; b[0][1] = 5; b[1][1] = 6;
    TMatrix<int> sum = a + b;
    TMatrix<int> diff = b - a;
    EXPECT_EQ(sum[0][0], 5);
    EXPECT_EQ(sum[0][1], 7);
    EXPECT_EQ(sum[1][1], 9);
    EXPECT_EQ(diff[0][0], 3);
    EXPECT_EQ(diff[1][1], 3);
}

// разные размеры
TEST(TMatrix, size_dif) {
    TMatrix<int> a(2), b(3);
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
}

//ввод и вывод матрицы
TEST(TMatrix, read_print) {
    TMatrix<int> m(2);
    std::istringstream in("1 2 3");
    in >> m;
    ASSERT_FALSE(in.fail());
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][1], 3);
    std::ostringstream out;
    out << m;
    EXPECT_EQ(out.str(), "1 2\n0 3");
}
