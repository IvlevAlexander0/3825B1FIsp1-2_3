#include <gtest/gtest.h>

#include "tmatrix.h"

TEST(Vector, InitializesDefaultVectorToZero)
{
    const TVector<int> vector;

    EXPECT_EQ(vector.GetSize(), 10);
    EXPECT_EQ(vector.GetStartIndex(), 0);
    for (int i = 0; i < vector.GetSize(); ++i) {
        EXPECT_EQ(vector[i], 0);
    }
}

TEST(Vector, ValidatesSizeAndStartIndex)
{
    EXPECT_THROW(TVector<int>(0), std::invalid_argument);
    EXPECT_THROW(TVector<int>(-1), std::invalid_argument);
    EXPECT_THROW(TVector<int>(MAX_VECTOR_SIZE + 1), std::invalid_argument);
    EXPECT_THROW(TVector<int>(3, -1), std::invalid_argument);
    EXPECT_THROW(TVector<int>(3, 3), std::invalid_argument);

    const TVector<int> lastOnly(MAX_VECTOR_SIZE, MAX_VECTOR_SIZE - 1);
    EXPECT_EQ(lastOnly.GetSize(), MAX_VECTOR_SIZE);
    EXPECT_EQ(lastOnly[MAX_VECTOR_SIZE - 1], 0);
}

TEST(Vector, AccessesOnlyStoredIndices)
{
    TVector<int> vector(5, 2);
    vector[2] = 7;
    vector[4] = 9;
    const auto& view = vector;

    EXPECT_EQ(view[2], 7);
    EXPECT_EQ(view[4], 9);
    EXPECT_THROW(vector[1], std::out_of_range);
    EXPECT_THROW(vector[5], std::out_of_range);
    EXPECT_THROW(view[-1], std::out_of_range);
    EXPECT_THROW(view[5], std::out_of_range);
}

TEST(Vector, CopiesAndAssignsIndependentStorage)
{
    TVector<int> original(3, 1);
    original[1] = -3;
    original[2] = 9;

    TVector<int> copy(original);
    TVector<int> assigned(1);
    EXPECT_EQ(&(assigned = original), &assigned);
    EXPECT_EQ(copy, original);
    EXPECT_EQ(assigned, original);

    copy[2] = 4;
    assigned[2] = 5;
    const auto& same = original;
    original = same;
    EXPECT_EQ(original[1], -3);
    EXPECT_EQ(original[2], 9);
    EXPECT_NE(copy, original);
    EXPECT_NE(assigned, original);
}

TEST(Vector, EqualityIncludesSizeAndStartIndex)
{
    const TVector<int> vector(4, 1);
    EXPECT_NE(vector, TVector<int>(5, 1));
    EXPECT_NE(vector, TVector<int>(4, 0));
}

TEST(Vector, PerformsScalarArithmeticOnStoredElements)
{
    TVector<double> vector(4, 2);
    vector[2] = 1.5;
    vector[3] = -2.0;

    const auto sum = vector + 1.0;
    const auto difference = vector - 2.0;
    const auto product = vector * -2.0;

    EXPECT_EQ(sum.GetSize(), 4);
    EXPECT_EQ(sum.GetStartIndex(), 2);
    EXPECT_DOUBLE_EQ(sum[2], 2.5);
    EXPECT_DOUBLE_EQ(sum[3], -1.0);
    EXPECT_DOUBLE_EQ(difference[2], -0.5);
    EXPECT_DOUBLE_EQ(difference[3], -4.0);
    EXPECT_DOUBLE_EQ(product[2], -3.0);
    EXPECT_DOUBLE_EQ(product[3], 4.0);
    EXPECT_DOUBLE_EQ(vector[2], 1.5);
}

TEST(Vector, AddsSubtractsAndComputesDotProduct)
{
    TVector<int> left(4, 2);
    left[2] = 3;
    left[3] = -2;
    TVector<int> right(4, 2);
    right[2] = 4;
    right[3] = 5;

    const auto sum = left + right;
    const auto difference = left - right;
    EXPECT_EQ(sum[2], 7);
    EXPECT_EQ(sum[3], 3);
    EXPECT_EQ(difference[2], -1);
    EXPECT_EQ(difference[3], -7);
    EXPECT_EQ(left * right, 2);
}

TEST(Vector, RejectsIncompatibleOperands)
{
    const TVector<int> vector(4, 1);
    const TVector<int> differentSize(5, 1);
    const TVector<int> differentStart(4, 2);
    EXPECT_THROW(vector + differentSize, std::invalid_argument);
    EXPECT_THROW(vector - differentSize, std::invalid_argument);
    EXPECT_THROW(vector * differentSize, std::invalid_argument);
    EXPECT_THROW(vector + differentStart, std::invalid_argument);
    EXPECT_THROW(vector - differentStart, std::invalid_argument);
    EXPECT_THROW(vector * differentStart, std::invalid_argument);
}
