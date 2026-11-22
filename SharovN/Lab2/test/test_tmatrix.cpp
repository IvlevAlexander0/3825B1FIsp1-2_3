#include <gtest/gtest.h>

#include "tmatrix.h"

TEST(Matrix, CreatesOnlyUpperTriangularRows)
{
    const TMatrix<int> matrix(3);
    EXPECT_EQ(matrix.GetSize(), 3);
    for (int row = 0; row < 3; ++row) {
        EXPECT_EQ(matrix[row].GetSize(), 3);
        EXPECT_EQ(matrix[row].GetStartIndex(), row);
        for (int col = row; col < 3; ++col) {
            EXPECT_EQ(matrix[row][col], 0);
        }
    }
    EXPECT_THROW(matrix[1][0], std::out_of_range);
    EXPECT_THROW(matrix[0][3], std::out_of_range);
    EXPECT_THROW(matrix[-1], std::out_of_range);
    EXPECT_THROW(matrix[3], std::out_of_range);
}

TEST(Matrix, HandlesOrderOneAndRejectsInvalidOrders)
{
    const TMatrix<int> defaults;
    EXPECT_EQ(defaults.GetSize(), 10);

    TMatrix<int> one(1);
    one[0][0] = 6;
    const auto doubled = one + one;
    EXPECT_EQ(doubled[0][0], 12);
    EXPECT_THROW(TMatrix<int>(0), std::invalid_argument);
    EXPECT_THROW(TMatrix<int>(-1), std::invalid_argument);
    EXPECT_THROW(TMatrix<int>(MAX_MATRIX_SIZE + 1), std::invalid_argument);
}

TEST(Matrix, CopiesAndAssignsIndependentRows)
{
    TMatrix<int> original(3);
    original[0][0] = 2;
    original[0][1] = -4;
    original[0][2] = 6;
    original[1][1] = -7;
    original[1][2] = 8;
    original[2][2] = 10;
    TMatrix<int> copy(original);
    TMatrix<int> assigned(1);

    EXPECT_EQ(&(assigned = original), &assigned);
    EXPECT_EQ(copy, original);
    EXPECT_EQ(assigned, original);
    copy[1][2] = 12;
    assigned[1][2] = -1;
    const auto& same = original;
    original = same;
    EXPECT_EQ(original[0][0], 2);
    EXPECT_EQ(original[0][1], -4);
    EXPECT_EQ(original[0][2], 6);
    EXPECT_EQ(original[1][1], -7);
    EXPECT_EQ(original[1][2], 8);
    EXPECT_EQ(original[2][2], 10);
    EXPECT_NE(original, copy);
    EXPECT_NE(original, assigned);
    EXPECT_NE(original, TMatrix<int>(2));
}

TEST(Matrix, ConvertsVectorOfTriangularRows)
{
    TVector<TVector<int>> rows(2);
    rows[0] = TVector<int>(2, 0);
    rows[1] = TVector<int>(2, 1);
    rows[0][1] = 5;
    rows[1][1] = 7;

    const TMatrix<int> matrix(rows);
    rows[1][1] = -1;
    EXPECT_EQ(matrix[0][1], 5);
    EXPECT_EQ(matrix[1][1], 7);
}

TEST(Matrix, RejectsInvalidTriangularRows)
{
    TVector<TVector<int>> rows(2);
    rows[0] = TVector<int>(2);
    rows[1] = TVector<int>(3, 1);
    EXPECT_THROW(static_cast<void>(TMatrix<int>(rows)), std::invalid_argument);
    rows[1] = TVector<int>(2, 0);
    EXPECT_THROW(static_cast<void>(TMatrix<int>(rows)), std::invalid_argument);

    const TVector<TVector<int>> shiftedRows(2, 1);
    EXPECT_THROW(static_cast<void>(TMatrix<int>(shiftedRows)), std::invalid_argument);
}

TEST(Matrix, AddsAndSubtractsAllStoredElements)
{
    TMatrix<double> left(2);
    left[0][0] = 1.5;
    left[0][1] = -2.0;
    left[1][1] = 3.0;
    TMatrix<double> right(2);
    right[0][0] = 2.5;
    right[0][1] = 4.0;
    right[1][1] = -1.0;

    const auto sum = left + right;
    const auto difference = left - right;
    EXPECT_DOUBLE_EQ(sum[0][0], 4.0);
    EXPECT_DOUBLE_EQ(sum[0][1], 2.0);
    EXPECT_DOUBLE_EQ(sum[1][1], 2.0);
    EXPECT_DOUBLE_EQ(difference[0][0], -1.0);
    EXPECT_DOUBLE_EQ(difference[0][1], -6.0);
    EXPECT_DOUBLE_EQ(difference[1][1], 4.0);
    EXPECT_EQ(sum[1].GetStartIndex(), 1);
    EXPECT_DOUBLE_EQ(left[0][1], -2.0);
}

TEST(Matrix, RejectsArithmeticWithDifferentOrders)
{
    const TMatrix<int> left(2);
    const TMatrix<int> right(3);
    EXPECT_THROW(left + right, std::invalid_argument);
    EXPECT_THROW(left - right, std::invalid_argument);
}
