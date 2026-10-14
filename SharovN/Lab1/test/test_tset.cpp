#include "tset.h"

#include <gtest/gtest.h>
#include <sstream>

TEST(TSet, can_get_max_power_set)
{
  const int size = 5;
  TSet set(size);
  EXPECT_EQ(size, set.GetMaxPower());
}

TEST(TSet, throws_when_create_set_with_negative_power)
{
  ASSERT_ANY_THROW(TSet set(-1));
}

TEST(TSet, can_create_empty_universe_set)
{
  TSet set(0);
  EXPECT_EQ(0, set.GetMaxPower());
}

TEST(TSet, new_set_is_empty)
{
  TSet set(50);
  for (int i = 0; i < 50; i++)
    EXPECT_EQ(0, set.IsMember(i));
}

TEST(TSet, can_insert_non_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.InsElem(k);
  EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, can_insert_existing_element)
{
  const int size = 5;
  const int k = 3;
  TSet set(size);
  set.InsElem(k);
  set.InsElem(k);
  EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, can_delete_non_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.DelElem(k);
  EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, can_delete_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.InsElem(k);
  EXPECT_GT(set.IsMember(k), 0);
  set.DelElem(k);
  EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, throws_when_insert_element_out_of_universe)
{
  TSet set(5);
  ASSERT_ANY_THROW(set.InsElem(5));
  ASSERT_ANY_THROW(set.InsElem(-1));
}

TEST(TSet, throws_when_delete_element_out_of_universe)
{
  TSet set(5);
  ASSERT_ANY_THROW(set.DelElem(5));
  ASSERT_ANY_THROW(set.DelElem(-1));
}

TEST(TSet, throws_when_check_membership_out_of_universe)
{
  TSet set(5);
  ASSERT_ANY_THROW(set.IsMember(5));
  ASSERT_ANY_THROW(set.IsMember(-1));
}

TEST(TSet, copied_set_is_equal_to_source_one)
{
  TSet set(70);
  set.InsElem(1);
  set.InsElem(65);
  TSet copy(set);
  EXPECT_EQ(set, copy);
}

TEST(TSet, copied_set_has_its_own_memory)
{
  TSet set(10);
  TSet copy(set);
  copy.InsElem(2);
  EXPECT_EQ(0, set.IsMember(2));
}

TEST(TSet, can_create_set_from_bitfield)
{
  TBitField bf(10);
  bf.SetBit(2);
  bf.SetBit(9);
  TSet set(bf);
  EXPECT_EQ(10, set.GetMaxPower());
  EXPECT_EQ(1, set.IsMember(2));
  EXPECT_EQ(1, set.IsMember(9));
  EXPECT_EQ(0, set.IsMember(0));
}

TEST(TSet, can_convert_set_to_bitfield)
{
  TSet set(10);
  set.InsElem(4);
  TBitField bf = (TBitField)set;
  EXPECT_EQ(10, bf.GetLength());
  EXPECT_EQ(1, bf.GetBit(4));
  EXPECT_EQ(0, bf.GetBit(5));
}

TEST(TSet, conversion_to_bitfield_and_back_gives_same_set)
{
  TSet set(40);
  set.InsElem(0);
  set.InsElem(39);
  TSet res((TBitField)set);
  EXPECT_EQ(set, res);
}

TEST(TSet, can_assign_set_of_equal_size)
{
  const int size = 10;
  TSet set1(size), set2(size);
  set1.InsElem(1);
  set1.InsElem(7);
  set2 = set1;
  EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_non_equal_size)
{
  TSet set1(5), set2(100);
  set2.InsElem(80);
  set1 = set2;
  EXPECT_EQ(100, set1.GetMaxPower());
  EXPECT_EQ(set2, set1);
}

TEST(TSet, can_assign_set_to_itself)
{
  TSet set(10);
  set.InsElem(3);
  TSet &ref = set;
  set = ref;
  EXPECT_EQ(1, set.IsMember(3));
  EXPECT_EQ(10, set.GetMaxPower());
}

TEST(TSet, can_chain_assignment)
{
  TSet a(5), b(5), c(5);
  c.InsElem(2);
  a = b = c;
  EXPECT_EQ(c, a);
  EXPECT_EQ(c, b);
}

TEST(TSet, compare_two_sets_of_non_equal_sizes)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);
  EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, compare_two_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  set1.InsElem(1);
  set1.InsElem(3);
  set2.InsElem(1);
  set2.InsElem(3);
  EXPECT_EQ(set1, set2);
}

TEST(TSet, compare_two_non_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  set1.InsElem(1);
  set1.InsElem(3);
  set2.InsElem(1);
  set2.InsElem(2);
  EXPECT_EQ(1, set1 != set2);
  EXPECT_EQ(0, set1 == set2);
}

TEST(TSet, can_insert_non_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);
  updatedSet = set + k;
  EXPECT_NE(0, updatedSet.IsMember(k));
}

TEST(TSet, plus_element_does_not_change_source_set)
{
  TSet set(5);
  TSet res = set + 2;
  EXPECT_EQ(0, set.IsMember(2));
  EXPECT_EQ(1, res.IsMember(2));
}

TEST(TSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  const int size = 4;
  const int k = 6;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);
  ASSERT_ANY_THROW(updatedSet = set + k);
}

TEST(TSet, can_insert_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(k);
  updatedSet = set + k;
  EXPECT_NE(0, set.IsMember(k));
  EXPECT_EQ(set, updatedSet);
}

TEST(TSet, can_delete_element_using_minus_operator)
{
  TSet set(5);
  set.InsElem(1);
  set.InsElem(3);
  TSet res = set - 3;
  EXPECT_EQ(0, res.IsMember(3));
  EXPECT_EQ(1, res.IsMember(1));
  EXPECT_EQ(1, set.IsMember(3));
}

TEST(TSet, can_delete_non_existing_element_using_minus_operator)
{
  TSet set(5);
  set.InsElem(1);
  TSet res = set - 2;
  EXPECT_EQ(set, res);
}

TEST(TSet, throws_when_delete_element_out_of_range_using_minus_operator)
{
  TSet set(5);
  ASSERT_ANY_THROW(set - 5);
  ASSERT_ANY_THROW(set - (-1));
}

TEST(TSet, can_combine_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);
  EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size);
  set1.InsElem(1);
  set2.InsElem(0);
  set3 = set1 + set2;
  EXPECT_EQ(size, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(6);
  set3 = set1 + set2;
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);
  expSet.InsElem(6);
  EXPECT_EQ(expSet, set3);
  EXPECT_EQ(expSet, set2 + set1);
}

TEST(TSet, union_with_empty_set_gives_same_set)
{
  TSet set(10), empty(10);
  set.InsElem(3);
  set.InsElem(9);
  EXPECT_EQ(set, set + empty);
}

TEST(TSet, can_intersect_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 * set2;
  expSet.InsElem(1);
  expSet.InsElem(2);
  EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(4);
  set2.InsElem(6);
  set3 = set1 * set2;
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);
  EXPECT_EQ(expSet, set3);
  EXPECT_EQ(expSet, set2 * set1);
}

TEST(TSet, intersection_of_disjoint_sets_is_empty)
{
  TSet set1(10), set2(10), empty(10);
  set1.InsElem(1);
  set2.InsElem(2);
  EXPECT_EQ(empty, set1 * set2);
}

TEST(TSet, check_negation_operator)
{
  const int size = 4;
  TSet set(size), set1(size), expSet(size);
  set.InsElem(1);
  set.InsElem(3);
  set1 = ~set;
  expSet.InsElem(0);
  expSet.InsElem(2);
  EXPECT_EQ(expSet, set1);
}

TEST(TSet, complement_of_empty_set_is_universe)
{
  const int size = 40;
  TSet set(size), full(size);
  for (int i = 0; i < size; i++)
    full.InsElem(i);
  EXPECT_EQ(full, ~set);
}

TEST(TSet, union_with_complement_is_universe_and_intersection_is_empty)
{
  const int size = 37;
  TSet set(size), full(size), empty(size);
  for (int i = 0; i < size; i++)
    full.InsElem(i);
  set.InsElem(0);
  set.InsElem(17);
  set.InsElem(36);
  EXPECT_EQ(full, set + ~set);
  EXPECT_EQ(empty, set * ~set);
}

TEST(TSet, de_morgan_law_holds)
{
  TSet a(20), b(20);
  a.InsElem(1);
  a.InsElem(5);
  a.InsElem(19);
  b.InsElem(5);
  b.InsElem(7);
  TSet left = ~(a + b);
  TSet right = ~a * ~b;
  EXPECT_EQ(left, right);
}

TEST(TSet, can_output_set)
{
  TSet set(10);
  set.InsElem(0);
  set.InsElem(3);
  set.InsElem(9);
  std::ostringstream out;
  out << set;
  EXPECT_EQ("{ 0 3 9 }", out.str());
}

TEST(TSet, can_output_empty_set)
{
  TSet set(10);
  std::ostringstream out;
  out << set;
  EXPECT_EQ("{ }", out.str());
}

TEST(TSet, can_input_set)
{
  TSet set(10), expSet(10);
  expSet.InsElem(1);
  expSet.InsElem(4);
  expSet.InsElem(8);
  std::istringstream in("3 1 4 8");
  in >> set;
  EXPECT_EQ(expSet, set);
}

TEST(TSet, throws_when_input_element_out_of_universe)
{
  TSet set(5);
  std::istringstream in("2 1 7");
  ASSERT_ANY_THROW(in >> set);
}
