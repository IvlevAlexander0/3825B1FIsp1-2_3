#include "pch.h"
#include "..\lab2\rl_utmatrix.h"

//   TVector  

TEST(VectorSuite, EqualityComparisons)
{
    TVector<int> a(5), b(5), c(7), d(5, 2);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a != d);
}

TEST(VectorSuite, ScalarArithmetic)
{
    TVector<int> base(4), out(4);
    for (int i = 0; i < 4; i++) {
        base[i] = i + 2;
    }

    out = base + 10;
    EXPECT_EQ(12, out[0]);

    out = base - 1;
    EXPECT_EQ(1, out[0]);

    out = base * 4;
    EXPECT_EQ(8, out[0]);
}

TEST(VectorSuite, CreateValid)
{
    ASSERT_NO_THROW(TVector<int> a(7));
    ASSERT_NO_THROW(TVector<int> empty(0));
}

TEST(VectorSuite, VectorArithmetic)
{
    TVector<int> a(4), b(4), c(6);
    for (int i = 0; i < 4; i++) {
        a[i] = i + 2;
        b[i] = 5;
    }

    EXPECT_EQ(7, (a + b)[0]);
    EXPECT_EQ(-3, (a - b)[0]);
    EXPECT_EQ(70, a * b);

    ASSERT_ANY_THROW(a + c);
    ASSERT_ANY_THROW(a - c);
    ASSERT_ANY_THROW(a * c);
}

TEST(VectorSuite, IndexOutOfRangeThrows)
{
    TVector<int> vec(5, 2);
    ASSERT_ANY_THROW(vec[-2] = 1);
    ASSERT_ANY_THROW(vec[1] = 1);
    ASSERT_ANY_THROW(vec[7] = 1);
}

TEST(VectorSuite, CopyConstructor)
{
    TVector<int> src(6);
    for (int i = 0; i < 6; i++) {
        src[i] = (i + 1) * 2;
    }
    TVector<int> copy(src);
    EXPECT_EQ(src, copy);

    copy[0] = 500;
    EXPECT_NE(src, copy);
}

TEST(VectorSuite, AssignmentOperator)
{
    TVector<int> first(5), second(8);
    for (int i = 0; i < 5; i++) {
        first[i] = i + 10;
    }

    ASSERT_NO_THROW(first = first);

    second = first;
    EXPECT_EQ(5, second.GetSize());
    EXPECT_EQ(first, second);
}

TEST(VectorSuite, SizeAndStartIndex)
{
    TVector<int> vec(6, 3);
    EXPECT_EQ(6, vec.GetSize());
    EXPECT_EQ(3, vec.GetStartIndex());

    vec[3] = 77;
    EXPECT_EQ(77, vec[3]);
}

TEST(VectorSuite, CreateInvalidThrows)
{
    ASSERT_ANY_THROW(TVector<int> a(MAX_VECTOR_SIZE + 1));
    ASSERT_ANY_THROW(TVector<int> a(-3));
    ASSERT_ANY_THROW(TVector<int> a(6, -1));
    ASSERT_ANY_THROW(TVector<int> a(6, MAX_VECTOR_SIZE + 1));
}

//   TMatrix  

TEST(MatrixSuite, SizeAndElementAccess)
{
    TMatrix<int> mat(5);
    EXPECT_EQ(5, mat.GetSize());

    mat[2][3] = 91;
    EXPECT_EQ(91, mat[2][3]);
}

TEST(MatrixSuite, AddSubtract)
{
    TMatrix<int> a(4), b(4), c(6);
    a[0][2] = 15;
    b[0][2] = 6;

    EXPECT_EQ(21, (a + b)[0][2]);
    EXPECT_EQ(9, (a - b)[0][2]);

    ASSERT_ANY_THROW(a + c);
    ASSERT_ANY_THROW(a - c);
}

TEST(MatrixSuite, CreateValid)
{
    ASSERT_NO_THROW(TMatrix<int> m(6));
    ASSERT_NO_THROW(TMatrix<int> empty(0));
}

TEST(MatrixSuite, IndexOutOfRangeThrows)
{
    TMatrix<int> mat(5);
    ASSERT_ANY_THROW(mat[-1][0] = 3);
    ASSERT_ANY_THROW(mat[5][5] = 3);
    ASSERT_ANY_THROW(mat[3][0] = 3);
}

TEST(MatrixSuite, EqualityComparisons)
{
    TMatrix<int> a(4), b(4), c(6);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
}

TEST(MatrixSuite, CopyConstructor)
{
    TMatrix<int> src(4);
    src[1][1] = 7;

    TMatrix<int> copy(src);
    EXPECT_EQ(src, copy);

    copy[1][1] = 111;
    EXPECT_NE(src, copy);
}

TEST(MatrixSuite, AssignmentOperator)
{
    TMatrix<int> a(4), b(6);
    a[0][0] = 8;

    ASSERT_NO_THROW(a = a);

    b = a;
    EXPECT_EQ(4, b.GetSize());
    EXPECT_EQ(a, b);
}

TEST(MatrixSuite, CreateInvalidThrows)
{
    ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
    ASSERT_ANY_THROW(TMatrix<int> m(-2));
}