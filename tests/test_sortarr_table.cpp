#include "gtest/gtest.h"
#include "TableManager.h"

typedef SortArrayTable Tab;

TEST(SortArrayTable, can_create_table)
{
  ASSERT_NO_THROW(Tab t);
}

TEST(SortArrayTable, can_get_size_of_table)
{
  Tab t;
  ASSERT_NO_THROW(t.getCurSize());
}

TEST(SortArrayTable, new_table_is_empty)
{
  Tab t;
  EXPECT_EQ(t.getCurSize(), 0);
}

TEST(SortArrayTable, can_add_elem_in_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
}

TEST(SortArrayTable, insert_elem_increases_size_of_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.getCurSize(), 1);
}

TEST(SortArrayTable, cant_change_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Insert(PolinomObj::Create("name", "x2"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
}

TEST(SortArrayTable, can_find_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
  EXPECT_EQ(t.Find("name")->get()->getName(), "name");
  EXPECT_EQ(t.Find("name")->get()->getPol(), Polinom("xyz"));
}

TEST(SortArrayTable, cant_find_non_existing_elem_in_table)
{
  Tab t;
  EXPECT_EQ(t.Find("x"), nullptr);
}

TEST(SortArrayTable, can_delete_existing_elem_from_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(SortArrayTable, delete_elem_decreases_size_of_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.getCurSize(), 0);
}

TEST(SortArrayTable, can_delete_non_existing_elem_from_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Delete("x"));
}

TEST(SortArrayTable, delete_non_existing_elem_doesnt_change_size_of_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("bob");
  EXPECT_EQ(t.getCurSize(), 1);
}
