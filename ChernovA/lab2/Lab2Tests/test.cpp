#include "pch.h"
#include "../Lab2/matrix.h"

//тесты на создание

TEST(tvector, default_constructor) {
    TVector<int> v;
    EXPECT_EQ(10, v.GetSize());
    EXPECT_EQ(0, v.GetStartIndex());
}

TEST(tvector, zero_size_throws) {
    EXPECT_THROW(TVector<int>(0), std::invalid_argument);
}

TEST(tvector, huge_size_throws) {
    EXPECT_THROW(TVector<int>(MAX_VECTOR_SIZE + 100), std::invalid_argument);
}

TEST(tvector, negative_start_throws) {
    EXPECT_THROW(TVector<int>(3, -10), std::invalid_argument);
}

TEST(tvector, start_not_less_size) { //StartIndex должен быть меньше Size
    EXPECT_THROW(TVector<int>(3, 3), std::invalid_argument);
}


//тесты на копирование

TEST(tvector, copy_is_equal) {
    TVector<int> v(5, 2);   // допустимые индексы 2, 3, 4
    v[2] = 1;
    v[3] = 2;
    v[4] = 3;

    TVector<int> v_copy(v);

    EXPECT_EQ(v, v_copy);
}

TEST(tvector, copy_is_independent) { //копия и оригинал разные и независимые 
    TVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    TVector<int> v_copy(v);
    v_copy[0] = 100;

    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(100, v_copy[0]);
}


//доступы по индексу

TEST(tvector, start_index_offset) {
    TVector<int> v(8, 5);   // допустимые индексы 5, 6, 7
    v[5] = 1;
    v[7] = 3;

    EXPECT_EQ(1, v[5]);
    EXPECT_EQ(0, v[6]);
    EXPECT_EQ(3, v[7]);
}

TEST(tvector, index_below_start) {
    TVector<int> v(7, 3);   // допустимые индексы 3, 4, 5, 6
    EXPECT_THROW(v[2], std::out_of_range);
}

TEST(tvector, index_above_end) {
    TVector<int> v(7, 3);
    EXPECT_THROW(v[7], std::out_of_range);
}


//тесты на присваивание

TEST(tvector, self_assignment) {
    TVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    TVector<int>& same = v;
    v = same;

    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(tvector, assign_same_size) {
    TVector<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    TVector<int> b(3);

    b = a;

    EXPECT_EQ(a, b);
}

TEST(tvector, assign_changes_size) {
    TVector<int> a(3);
    TVector<int> b(7, 2);
    b[2] = 1;
    b[6] = 5;

    a = b;

    EXPECT_EQ(7, a.GetSize());
    EXPECT_EQ(2, a.GetStartIndex());
    EXPECT_EQ(b, a);
}

TEST(tvector, assign_same_count) { //Size разный, но хранится одинаковое число элементов
    TVector<int> a(5, 2);
    TVector<int> b(3);
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;

    a = b;

    EXPECT_EQ(3, a.GetSize());
    EXPECT_EQ(0, a.GetStartIndex());
    EXPECT_EQ(b, a);
}


//тесты на сравнение

TEST(tvector, equal_vectors) {
    TVector<int> a(4, 1);
    TVector<int> b(4, 1);
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    b[1] = 1;
    b[2] = 2;
    b[3] = 3;

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(tvector, different_elements) {
    TVector<int> a(3);
    TVector<int> b(3);
    a[2] = 1;
    b[2] = 2;

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(tvector, different_size) {
    TVector<int> a(3);
    TVector<int> b(2);

    EXPECT_TRUE(a != b);
}


//тесты на скалярные операции

TEST(tvector, add_scalar) {
    TVector<int> v(5, 2);
    v[2] = 1;
    v[3] = 2;
    v[4] = 3;

    TVector<int> result = v + 10;

    EXPECT_EQ(11, result[2]);
    EXPECT_EQ(12, result[3]);
    EXPECT_EQ(13, result[4]);
}

TEST(tvector, sub_scalar) {
    TVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    TVector<int> result = v - 1;

    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(1, result[1]);
    EXPECT_EQ(2, result[2]);
}

TEST(tvector, mul_scalar) {
    TVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    TVector<int> result = v * 2;

    EXPECT_EQ(2, result[0]);
    EXPECT_EQ(4, result[1]);
    EXPECT_EQ(6, result[2]);
}


//тесты на векторные операции

TEST(tvector, add_vectors) {
    TVector<int> a(4, 1);
    TVector<int> b(4, 1);
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    b[1] = 4;
    b[2] = 5;
    b[3] = 6;

    TVector<int> result = a + b;

    EXPECT_EQ(5, result[1]);
    EXPECT_EQ(7, result[2]);
    EXPECT_EQ(9, result[3]);
}

TEST(tvector, sub_vectors) {
    TVector<int> a(3);
    TVector<int> b(3);
    a[0] = 4;
    a[1] = 5;
    a[2] = 6;
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;

    TVector<int> result = a - b;

    EXPECT_EQ(3, result[0]);
    EXPECT_EQ(3, result[1]);
    EXPECT_EQ(3, result[2]);
}

TEST(tvector, dot_product) {
    TVector<int> a(3);
    TVector<int> b(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    EXPECT_EQ(32, a * b);
}

TEST(tvector, size_mismatch_throws) {
    TVector<int> a(3);
    TVector<int> b(2);

    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
    EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(tvector, start_mismatch_throws) {
    TVector<int> a(3, 0);
    TVector<int> b(3, 1);

    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
    EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(tvector, negative_size_throws) {
    EXPECT_THROW(TVector<int>(-5), std::invalid_argument);
}

//тесты на матрицы

//тесты на создание

TEST(tmatrix, default_constructor) {
    TMatrix<int> m;
    EXPECT_EQ(10, m.GetSize());
}

TEST(tmatrix, create_single) {
    TMatrix<int> m(1);
    EXPECT_EQ(1, m.GetSize());
    EXPECT_EQ(0, m[0][0]);
}

TEST(tmatrix, zero_size_throws) {
    EXPECT_THROW(TMatrix<int>(0), std::invalid_argument);
}

TEST(tmatrix, huge_size_throws) {
    EXPECT_THROW(TMatrix<int>(MAX_MATRIX_SIZE + 100), std::invalid_argument);
}

TEST(tmatrix, negative_size_throws) {
    EXPECT_THROW(TMatrix<int>(-30), std::invalid_argument);
}

TEST(tmatrix, row_layout) { //у каждой строки полная длина n, а начало сдвигается на i
    TMatrix<int> m(4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(4, m[i].GetSize());
        EXPECT_EQ(i, m[i].GetStartIndex());
    }
}


//тесты на доступ

TEST(tmatrix, diagonal_access) {
    TMatrix<int> m(3);
    m[0][0] = 1;
    m[2][2] = 3;

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(3, m[2][2]);
}

TEST(tmatrix, below_diagonal_throws) {
    TMatrix<int> m(3);
    EXPECT_THROW(m[1][0], std::out_of_range);
    EXPECT_THROW(m[2][1], std::out_of_range);
}

TEST(tmatrix, column_above_end) {
    TMatrix<int> m(3);
    EXPECT_THROW(m[0][3], std::out_of_range);
}


//тесты на копирование

TEST(tmatrix, copy_is_independent) {
    TMatrix<int> m(2);
    m[1][1] = 4;

    TMatrix<int> m_copy(m);
    m_copy[1][1] = 100;

    EXPECT_EQ(4, m[1][1]);
    EXPECT_EQ(100, m_copy[1][1]);
}


//тесты на присваивание

TEST(tmatrix, assign_same_size) {
    TMatrix<int> a(2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][1] = 3;
    TMatrix<int> b(2);

    b = a;

    EXPECT_EQ(a, b);
}

TEST(tmatrix, assign_changes_size) {
    TMatrix<int> a(5);
    TMatrix<int> b(2);
    b[0][1] = 7;

    a = b;

    EXPECT_EQ(2, a.GetSize());
    EXPECT_EQ(b, a);
}


//тесты на сравнение

TEST(tmatrix, equal_matrices) {
    TMatrix<int> a(2);
    TMatrix<int> b(2);
    a[0][1] = 2;
    b[0][1] = 2;

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(tmatrix, different_elements) {
    TMatrix<int> a(2);
    TMatrix<int> b(2);
    a[1][1] = 1;
    b[1][1] = 2;

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(tmatrix, different_size) {
    TMatrix<int> a(2);
    TMatrix<int> b(3);

    EXPECT_TRUE(a != b);
}


//тесты на сложение и вычитание

TEST(tmatrix, add_matrices) {
    TMatrix<int> a(2);
    TMatrix<int> b(2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][1] = 3;
    b[0][0] = 4;
    b[0][1] = 5;
    b[1][1] = 6;

    TMatrix<int> result = a + b;

    EXPECT_EQ(5, result[0][0]);
    EXPECT_EQ(7, result[0][1]);
    EXPECT_EQ(9, result[1][1]);
}

TEST(tmatrix, sub_matrices) {
    TMatrix<int> a(2);
    TMatrix<int> b(2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][1] = 3;
    b[0][0] = 4;
    b[0][1] = 5;
    b[1][1] = 6;

    TMatrix<int> result = a - b;

    EXPECT_EQ(-3, result[0][0]);
    EXPECT_EQ(-3, result[0][1]);
    EXPECT_EQ(-3, result[1][1]);
}

TEST(tmatrix, size_mismatch_throws) {
    TMatrix<int> a(3);
    TMatrix<int> b(4);

    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);
}