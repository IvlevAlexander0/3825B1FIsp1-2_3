#include "pch.h"
#include "utmatrix_r.h"

TEST(TVectorTest, InvalidStartIndex) {           // некорректный StartIndex
    ASSERT_THROW(TVector<int> v(5, -1), std::invalid_argument);
    ASSERT_THROW(TVector<int> v(5, 6), std::invalid_argument);
    ASSERT_NO_THROW(TVector<int> v(5, 5));
    TVector<int> v(5, 5);
    EXPECT_EQ(0, v.GetSize() - v.GetStartIndex());
}
TEST(TVectorTest, DefaultConstructor) {       // вектор с параметрами по умолчанию
    ASSERT_NO_THROW(TVector<int> v());
    TVector<int> v;
    EXPECT_EQ(10, v.GetSize());
    EXPECT_EQ(0, v.GetStartIndex());
}

TEST(TVectorTest, ParameterizedConstructor) {      // вектор с заданным размером и начальным индексом
    ASSERT_NO_THROW(TVector<double> v(5, 2));
    TVector<double> v(5, 2);
    EXPECT_EQ(5, v.GetSize());
    EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVectorTest, NegativeSize) {     //отрицательный размер
    ASSERT_THROW(TVector<int> v(-5), std::invalid_argument);
}


TEST(TVectorTest, TooLargeSize) {       // размер больше максимального
    ASSERT_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1), std::invalid_argument);
}


TEST(TVectorTest, ZeroSize) {     // нулевой размер
    ASSERT_THROW(TVector<int> v(0), std::invalid_argument);
}

TEST(TVectorTest, AccessElements) {
    TVector<int> v(5, 1);
    v[1] = 10;
    v[3] = 30;
    v[4] = 40;
    EXPECT_EQ(10, v[1]);
    EXPECT_EQ(30, v[3]);
    EXPECT_EQ(40, v[4]);
}

TEST(TVectorTest, AssignmentOperator) {      // оператор присваивания
    TVector<int> v1(5, 2);
    v1[2] = 100;

    TVector<int> v2(3, 0);
    v2 = v1;

    EXPECT_EQ(v1.GetSize(), v2.GetSize());
    EXPECT_EQ(100, v2[2]);
}

TEST(TVectorTest, SelfAssignment) {  // самоприсваивание
    TVector<int> v(5, 2);
    v[2] = 100;
    v = v;
    EXPECT_EQ(100, v[2]);
}

TEST(TVectorTest, EqualOperator) {  // оператор равенства
    TVector<int> v1(5, 2);
    TVector<int> v2(5, 2);
    v1[2] = 10;
    v2[2] = 10;
    EXPECT_TRUE(v1 == v2);
}

TEST(TVectorTest, NotEqualOperator) {  // оператор неравенства
    TVector<int> v1(5, 2);
    TVector<int> v2(5, 2);
    v1[2] = 10;
    v2[2] = 20;
    EXPECT_TRUE(v1 != v2);
}

TEST(TVectorTest, DifferentSizeNotEqual) {  // сравнение векторов разного размера
    TVector<int> v1(5, 2);
    TVector<int> v2(10, 2);
    EXPECT_TRUE(v1 != v2);
}

TEST(TVectorTest, AddScalar) {   // сложение со скаляром
    TVector<int> v(3, 0);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    TVector<int> result = v + 10;

    EXPECT_EQ(11, result[0]);
    EXPECT_EQ(12, result[1]);
    EXPECT_EQ(13, result[2]);

    EXPECT_EQ(1, v[0]);
}

TEST(TVectorTest, SubtractScalar) {    // вычитание скаляра
    TVector<int> v(3, 0);
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;

    TVector<int> result = v - 5;

    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(15, result[1]);
    EXPECT_EQ(25, result[2]);
}

TEST(TVectorTest, MultiplyScalar) {    // умножение на скаляр
    TVector<int> v(3, 0);
    v[0] = 2;
    v[1] = 3;
    v[2] = 4;

    TVector<int> result = v * 3;

    EXPECT_EQ(6, result[0]);
    EXPECT_EQ(9, result[1]);
    EXPECT_EQ(12, result[2]);
}

TEST(TVectorTest, AddVectors) {  // сложение двух векторов
    TVector<int> v1(3, 0);
    TVector<int> v2(3, 0);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    TVector<int> result = v1 + v2;

    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(7, result[1]);
    EXPECT_EQ(9, result[2]);
}

TEST(TVectorTest, AddDifferentSizeVectors) {    // сложение векторов разного размера
    TVector<int> v1(3, 0);
    TVector<int> v2(5, 0);
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVectorTest, SubtractVectors) {          // вычитание двух векторов
    TVector<int> v1(3, 0);
    TVector<int> v2(3, 0);
    v1[0] = 10; v1[1] = 20; v1[2] = 30;
    v2[0] = 1;  v2[1] = 2;  v2[2] = 3;

    TVector<int> result = v1 - v2;

    EXPECT_EQ(9, result[0]);
    EXPECT_EQ(18, result[1]);
    EXPECT_EQ(27, result[2]);
}

TEST(TVectorTest, DotProduct) {    // скалярное произведение
    TVector<int> v1(3, 0);
    TVector<int> v2(3, 0);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    int result = v1 * v2;          // 1*4 + 2*5 + 3*6 = 32

    EXPECT_EQ(32, result);
}

TEST(TVectorTest, DotProductDifferentSize) {    // скалярное произведение векторов разного размера
    TVector<int> v1(3, 0);
    TVector<int> v2(5, 0);
    ASSERT_ANY_THROW(v1 * v2);
}

TEST(TVectorTest, NonZeroStartIndex) {  // вектор с ненулевым начальным индексом
    TVector<int> v(15, 10);

    v[10] = 100;
    v[14] = 140;

    EXPECT_EQ(100, v[10]);
    EXPECT_EQ(140, v[14]);

    ASSERT_ANY_THROW(v[9]);
    ASSERT_ANY_THROW(v[15]);
}

TEST(TMatrixTest, DefaultConstructor) {  //матрица с параметром по умолчанию
    ASSERT_NO_THROW(TMatrix<int> m());
    TMatrix<int> m;
    EXPECT_EQ(10, m.GetSize());
}

TEST(TMatrixTest, ParameterizedConstructor) {     // матрица заданного размера
    ASSERT_NO_THROW(TMatrix<double> m(5));
    TMatrix<double> m(5);
    EXPECT_EQ(5, m.GetSize());
}

TEST(TMatrixTest, NegativeSize) {  //  отрицательный размер матрицы
    ASSERT_THROW(TMatrix<int> m(-5), std::invalid_argument);
}

TEST(TMatrixTest, TooLargeSize) {  // размер больше максимального
    ASSERT_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1), std::invalid_argument);
}

TEST(TMatrixTest, ZeroSize) {  //нулевой размер матрицы
    ASSERT_THROW(TMatrix<int> m(0), std::invalid_argument);
}

TEST(TMatrixTest, AssignmentOperator) {  // оператор присваивания матрицы
    TMatrix<int> m1(3);
    m1[0][0] = 100;

    TMatrix<int> m2(5);
    m2 = m1;

    EXPECT_EQ(m1.GetSize(), m2.GetSize());
    EXPECT_EQ(100, m2[0][0]);
}

TEST(TMatrixTest, EqualOperator) {  // оператор равенства матриц
    TMatrix<int> m1(3);
    TMatrix<int> m2(3);
    m1[0][0] = 1; m2[0][0] = 1;
    m1[1][1] = 2; m2[1][1] = 2;
    m1[2][2] = 3; m2[2][2] = 3;

    EXPECT_TRUE(m1 == m2);
}

TEST(TMatrixTest, NotEqualOperator) {  // оператор неравенства матриц
    TMatrix<int> m1(3);
    TMatrix<int> m2(3);
    m1[0][0] = 1;
    m2[0][0] = 2;

    EXPECT_TRUE(m1 != m2);
}


TEST(TMatrixTest, AddMatrices) {  // сложение двух матриц
    TMatrix<int> m1(3);
    TMatrix<int> m2(3);

    m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
    m1[1][1] = 4; m1[1][2] = 5;
    m1[2][2] = 6;

    m2[0][0] = 10; m2[0][1] = 20; m2[0][2] = 30;
    m2[1][1] = 40; m2[1][2] = 50;
    m2[2][2] = 60;

    TMatrix<int> result = m1 + m2;

    EXPECT_EQ(11, result[0][0]);
    EXPECT_EQ(22, result[0][1]);
    EXPECT_EQ(33, result[0][2]);
    EXPECT_EQ(44, result[1][1]);
    EXPECT_EQ(55, result[1][2]);
    EXPECT_EQ(66, result[2][2]);
}

TEST(TMatrixTest, AddDifferentSizeMatrices) {  // сложение матриц разного размера
    TMatrix<int> m1(3);
    TMatrix<int> m2(5);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrixTest, SubtractMatrices) {  // вычитание двух матриц
    TMatrix<int> m1(3);
    TMatrix<int> m2(3);

    m1[0][0] = 10; m1[0][1] = 20;
    m2[0][0] = 1;  m2[0][1] = 2;

    TMatrix<int> result = m1 - m2;

    EXPECT_EQ(9, result[0][0]);
    EXPECT_EQ(18, result[0][1]);
}

TEST(TMatrixTest, SubtractDifferentSizeMatrices) { // вычитание матриц разного размера
    TMatrix<int> m1(3);
    TMatrix<int> m2(5);
    ASSERT_ANY_THROW(m1 - m2);
}

TEST(TMatrixTest, SingleElementMatrix) {  // матрица 1 на 1
    TMatrix<int> m(1);
    EXPECT_EQ(1, m.GetSize());
    EXPECT_EQ(1, m[0].GetSize());
    EXPECT_EQ(0, m[0].GetStartIndex());

    m[0][0] = 42;
    EXPECT_EQ(42, m[0][0]);
}

TEST(TMatrixTest, TwoByTwoMatrix) {  // матрица размера 2 на 2
    TMatrix<int> m(2);

    EXPECT_EQ(2, m[0].GetSize());
    EXPECT_EQ(2, m[1].GetSize());

    EXPECT_EQ(0, m[0].GetStartIndex());
    EXPECT_EQ(1, m[1].GetStartIndex());

    m[0][0] = 1; m[0][1] = 2;
    m[1][1] = 3;

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
    EXPECT_EQ(3, m[1][1]);

    ASSERT_ANY_THROW(m[1][0]);
}