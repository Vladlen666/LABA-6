#include "gtest/gtest.h"
#include "TableManager.h"

// Tests for TableManager

TEST(TableManager, can_create_table_manager_with_tables)
{
  ASSERT_NO_THROW(TableManager m(2););
}

TEST(TTable, cant_create_table_manager_with_incorrect_size)
{
  ASSERT_ANY_THROW(TableManager m(0));
  ASSERT_ANY_THROW(TableManager m(-1));
}

TEST(TableManager, can_set_active_table)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.setActiveTable(1));
}

TEST(TableManager, can_get_cur_size_of_tables)
{
  TableManager m(2);
  EXPECT_EQ(0, m.getCurSize());
}

TEST(TableManager, can_get_max_size_of_tables)
{
  TableManager m(2);
  EXPECT_EQ(2, m.getMaxSize());
}

TEST(TableManager, can_get_count_of_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.getCountTables());
}

TEST(TableManager, can_get_active_table_ind)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.getActiveTableInd());
}

TEST(TableManager, can_set_active_table_ind)
{
  TableManager m(2);
  int actInd = -1;
  if (m.getCountTables() >= 1)
    actInd = 1;
  else if (m.getCountTables() == 0)
    actInd = 0;
  m.setActiveTable(actInd);
  EXPECT_EQ(actInd, m.getActiveTableInd());
}

TEST(TableManager, throw_when_set_negative_active_table_ind)
{
  TableManager m(2);
  ASSERT_ANY_THROW(m.setActiveTable(-1));
}

TEST(TableManager, throw_when_set_too_large_active_table_ind)
{
  TableManager m(2);
  ASSERT_ANY_THROW(m.setActiveTable(m.getCountTables() + 1));
}

TEST(TableManager, new_table_manager_is_empty)
{
  TableManager m(2);
  EXPECT_EQ(m.getCurSize(), 0);
}

TEST(TableManager, can_add_elem_into_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Insert("name", "xyz"));
}

TEST(TableManager, insert_elem_increases_cur_size_in_table_manager)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  EXPECT_EQ(m.getCurSize(), 1);
}

TEST(TableManager, can_find_elem)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  EXPECT_EQ(m.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TableManager, cant_replace_existing_elem_when_insert)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Insert("name", "x2");
  EXPECT_EQ(m.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TableManager, can_delete_existing_elem_from_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_NO_THROW(m.Delete("name"));
}

TEST(TableManager, delete_elem_decreases_size_of_table_manager)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Insert("bob", "x2");
  m.Delete("name");
  EXPECT_EQ(m.getCurSize(), 1);
}

TEST(TableManager, no_throw_deleting_non_existing_elem_from_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_NO_THROW(m.Delete("x"));
}

TEST(TableManager, delete_non_existing_elem_doesnt_change_size_of_table_manager)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Delete("bob");
  EXPECT_EQ(m.getCurSize(), 1);
}

TEST(TableManager, throw_when_add_elem_to_full_table_manager)
{
  TableManager m(1);
  m.Insert("name", "xyz");
  ASSERT_ANY_THROW(m.Insert("bob", "x2"););
}

TEST(TableManager, throw_when_delete_from_empty_table_manager)
{
  TableManager m(2);
  ASSERT_ANY_THROW(m.Delete("x"));
}
