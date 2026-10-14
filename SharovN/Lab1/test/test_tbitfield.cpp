#include "tbitfield.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(TBitField, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, can_create_bitfield_with_zero_length)
{
  TBitField bf(0);
  EXPECT_EQ(0, bf.GetLength());
}

TEST(TBitField, throws_when_create_bitfield_with_negative_length)
{
  ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, can_get_length)
{
  TBitField bf(3);
  EXPECT_EQ(3, bf.GetLength());
}

TEST(TBitField, new_bitfield_is_set_to_zero)
{
  TBitField bf(100);
  int sum = 0;
  for (int i = 0; i < bf.GetLength(); i++)
    sum += bf.GetBit(i);
  EXPECT_EQ(0, sum);
}

TEST(TBitField, can_set_bit)
{
  TBitField bf(10);
  EXPECT_EQ(0, bf.GetBit(3));
  bf.SetBit(3);
  EXPECT_NE(0, bf.GetBit(3));
}

TEST(TBitField, setting_bit_does_not_change_other_bits)
{
  TBitField bf(64);
  bf.SetBit(33);
  for (int i = 0; i < 64; i++)
    EXPECT_EQ(i == 33 ? 1 : 0, bf.GetBit(i));
}

TEST(TBitField, can_clear_bit)
{
  TBitField bf(10);
  int bitIdx = 3;
  bf.SetBit(bitIdx);
  EXPECT_NE(0, bf.GetBit(bitIdx));
  bf.ClrBit(bitIdx);
  EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(TBitField, can_set_and_clear_first_and_last_bits)
{
  TBitField bf(65);
  bf.SetBit(0);
  bf.SetBit(64);
  EXPECT_EQ(1, bf.GetBit(0));
  EXPECT_EQ(1, bf.GetBit(64));
  bf.ClrBit(0);
  bf.ClrBit(64);
  EXPECT_EQ(0, bf.GetBit(0));
  EXPECT_EQ(0, bf.GetBit(64));
}

TEST(TBitField, can_set_bits_on_element_boundary)
{
  TBitField bf(100);
  bf.SetBit(31);
  bf.SetBit(32);
  EXPECT_EQ(1, bf.GetBit(31));
  EXPECT_EQ(1, bf.GetBit(32));
  EXPECT_EQ(0, bf.GetBit(30));
  EXPECT_EQ(0, bf.GetBit(33));
}

TEST(TBitField, throws_when_set_bit_with_negative_index)
{
  TBitField bf(10);
  ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(TBitField, throws_when_set_bit_with_too_large_index)
{
  TBitField bf(10);
  ASSERT_ANY_THROW(bf.SetBit(10));
}

TEST(TBitField, throws_when_get_bit_with_negative_index)
{
  TBitField bf(10);
  ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(TBitField, throws_when_get_bit_with_too_large_index)
{
  TBitField bf(10);
  ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(TBitField, throws_when_clear_bit_with_negative_index)
{
  TBitField bf(10);
  ASSERT_ANY_THROW(bf.ClrBit(-3));
}

TEST(TBitField, throws_when_clear_bit_with_too_large_index)
{
  TBitField bf(10);
  ASSERT_ANY_THROW(bf.ClrBit(11));
}

TEST(TBitField, throws_on_any_bit_access_in_zero_length_bitfield)
{
  TBitField bf(0);
  ASSERT_ANY_THROW(bf.SetBit(0));
  ASSERT_ANY_THROW(bf.GetBit(0));
  ASSERT_ANY_THROW(bf.ClrBit(0));
}

TEST(TBitField, can_create_copied_bitfield)
{
  TBitField bf(10);
  ASSERT_NO_THROW(TBitField bf1(bf));
}

TEST(TBitField, copied_bitfield_is_equal_to_source_one)
{
  TBitField bf(100);
  bf.SetBit(1);
  bf.SetBit(50);
  bf.SetBit(99);
  TBitField copy(bf);
  EXPECT_EQ(bf, copy);
}

TEST(TBitField, copied_bitfield_has_its_own_memory)
{
  TBitField bf(10);
  TBitField copy(bf);
  copy.SetBit(5);
  EXPECT_EQ(0, bf.GetBit(5));
}

TEST(TBitField, can_assign_bitfields_of_equal_size)
{
  const int size = 2;
  TBitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
    bf1.SetBit(i);
  bf2 = bf1;
  EXPECT_NE(0, bf2.GetBit(0));
  EXPECT_NE(0, bf2.GetBit(1));
}

TEST(TBitField, assign_operator_changes_bitfield_size)
{
  TBitField bf1(2), bf2(5);
  bf1 = bf2;
  EXPECT_EQ(5, bf1.GetLength());
}

TEST(TBitField, can_assign_bitfields_of_non_equal_size)
{
  TBitField bf1(2), bf2(100);
  bf2.SetBit(70);
  bf1 = bf2;
  EXPECT_EQ(bf2, bf1);
  EXPECT_EQ(1, bf1.GetBit(70));
}

TEST(TBitField, can_assign_to_itself)
{
  TBitField bf(10);
  bf.SetBit(4);
  TBitField &ref = bf;
  bf = ref;
  EXPECT_EQ(1, bf.GetBit(4));
  EXPECT_EQ(10, bf.GetLength());
}

TEST(TBitField, assigned_bitfield_has_its_own_memory)
{
  TBitField bf1(10), bf2(10);
  bf2 = bf1;
  bf2.SetBit(3);
  EXPECT_EQ(0, bf1.GetBit(3));
}

TEST(TBitField, compare_equal_bitfields_of_equal_size)
{
  TBitField bf1(2), bf2(2);
  bf1.SetBit(0);
  bf2.SetBit(0);
  EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, compare_non_equal_bitfields_of_equal_size)
{
  TBitField bf1(40), bf2(40);
  bf1.SetBit(35);
  EXPECT_NE(bf1, bf2);
}

TEST(TBitField, bitfields_of_non_equal_size_are_not_equal)
{
  TBitField bf1(4), bf2(5);
  EXPECT_NE(bf1, bf2);
  EXPECT_FALSE(bf1 == bf2);
}

TEST(TBitField, empty_bitfields_are_equal)
{
  TBitField bf1(0), bf2(0);
  EXPECT_TRUE(bf1 == bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  bf1.SetBit(2);
  bf1.SetBit(3);
  bf2.SetBit(1);
  bf2.SetBit(3);
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);
  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
  TBitField bf1(4), bf2(5), expBf(5);
  bf1.SetBit(2);
  bf1.SetBit(3);
  bf2.SetBit(1);
  bf2.SetBit(3);
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);
  EXPECT_EQ(expBf, bf1 | bf2);
  EXPECT_EQ(expBf, bf2 | bf1);
}

TEST(TBitField, or_operator_does_not_change_operands)
{
  TBitField bf1(4), bf2(4);
  bf1.SetBit(0);
  bf2.SetBit(1);
  TBitField res = bf1 | bf2;
  EXPECT_EQ(0, bf1.GetBit(1));
  EXPECT_EQ(0, bf2.GetBit(0));
}

TEST(TBitField, and_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  TBitField bf1(size), bf2(size), expBf(size);
  bf1.SetBit(2);
  bf1.SetBit(3);
  bf2.SetBit(1);
  bf2.SetBit(3);
  expBf.SetBit(3);
  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
  TBitField bf1(4), bf2(5), expBf(5);
  bf1.SetBit(2);
  bf1.SetBit(3);
  bf2.SetBit(1);
  bf2.SetBit(3);
  bf2.SetBit(4);
  expBf.SetBit(3);
  EXPECT_EQ(expBf, bf1 & bf2);
  EXPECT_EQ(expBf, bf2 & bf1);
}

TEST(TBitField, and_operator_applied_to_large_bitfields_of_non_equal_size)
{
  TBitField bf1(40), bf2(100), expBf(100);
  bf1.SetBit(39);
  bf2.SetBit(39);
  bf2.SetBit(70);
  expBf.SetBit(39);
  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, can_invert_bitfield)
{
  const int size = 2;
  TBitField bf(size), negBf(size), expNegBf(size);
  bf.SetBit(1);
  negBf = ~bf;
  expNegBf.SetBit(0);
  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, can_invert_large_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);
  bf.SetBit(35);
  negBf = ~bf;
  for (int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  expNegBf.ClrBit(35);
  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, invert_does_not_set_bits_outside_of_length)
{
  TBitField bf(5), full(5);
  for (int i = 0; i < 5; i++)
    full.SetBit(i);
  EXPECT_EQ(full, ~bf);
}

TEST(TBitField, double_invert_gives_source_bitfield)
{
  TBitField bf(70);
  bf.SetBit(0);
  bf.SetBit(33);
  bf.SetBit(69);
  EXPECT_EQ(bf, ~~bf);
}

TEST(TBitField, invert_plus_and_operator_on_different_size_bitfield)
{
  const int firstSze = 4, secondSize = 8;
  TBitField firstBf(firstSze), negFirstBf(firstSze), secondBf(secondSize), testBf(secondSize);
  firstBf.SetBit(0);
  negFirstBf = ~firstBf;

  secondBf.SetBit(3);
  secondBf.SetBit(4);

  testBf.SetBit(3);

  EXPECT_EQ(secondBf & negFirstBf, testBf);
}

TEST(TBitField, can_invert_zero_length_bitfield)
{
  TBitField bf(0);
  EXPECT_EQ(bf, ~bf);
}

TEST(TBitField, can_invert_many_random_bits_bitfield)
{
  const int size = 38;
  TBitField bf(size), negBf(size), expNegBf(size);

  std::vector<int> bits;
  bits.push_back(0);
  bits.push_back(1);
  bits.push_back(14);
  bits.push_back(16);
  bits.push_back(33);
  bits.push_back(37);

  for (unsigned int i = 0; i < bits.size(); i++)
    bf.SetBit(bits[i]);

  negBf = ~bf;

  for (int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  for (unsigned int i = 0; i < bits.size(); i++)
    expNegBf.ClrBit(bits[i]);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, bitfields_with_different_bits_are_not_equal)
{
  const int size = 38;
  TBitField bf1(size), bf2(size);
  bf1.SetBit(1);
  bf1.SetBit(25);
  bf2.SetBit(1);
  bf2.SetBit(35);
  EXPECT_NE(bf1, bf2);
}

TEST(TBitField, can_output_bitfield)
{
  TBitField bf(5);
  bf.SetBit(1);
  bf.SetBit(4);
  std::ostringstream out;
  out << bf;
  EXPECT_EQ("01001", out.str());
}

TEST(TBitField, can_input_bitfield)
{
  TBitField bf(5), expBf(5);
  expBf.SetBit(0);
  expBf.SetBit(3);
  std::istringstream in("10010");
  in >> bf;
  EXPECT_EQ(expBf, bf);
}

TEST(TBitField, output_then_input_gives_same_bitfield)
{
  TBitField bf(40), res(40);
  bf.SetBit(0);
  bf.SetBit(31);
  bf.SetBit(32);
  bf.SetBit(39);
  std::stringstream ss;
  ss << bf;
  ss >> res;
  EXPECT_EQ(bf, res);
}
