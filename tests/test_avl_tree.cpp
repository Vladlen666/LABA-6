#include "gtest/gtest.h"
#include "avl_tree.hpp"
#include "TTable.h"

TEST(AVLTree, can_create_tree)
{
  ASSERT_NO_THROW(AVLTree t);
}

TEST(AVLTree, can_get_size_of_tree)
{
  AVLTree t;
  ASSERT_NO_THROW(t.getSize());
}

TEST(AVLTree, new_tree_is_empty)
{
  AVLTree t;
  EXPECT_EQ(t.getSize(), 0);
}

TEST(AVLTree, can_add_elem_in_tree)
{
  AVLTree t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
}

TEST(AVLTree, insert_elem_increases_size_of_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.getSize(), 1);
}

TEST(AVLTree, cant_change_existing_elem_in_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Insert(PolinomObj::Create("name", "x2"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
}

TEST(AVLTree, can_find_existing_elem_in_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
  EXPECT_EQ(t.Find("name")->get()->getName(), "name");
  EXPECT_EQ(t.Find("name")->get()->getPol(), Polinom("xyz"));
}

TEST(AVLTree, cant_find_non_existing_elem_in_tree)
{
  AVLTree t;
  EXPECT_EQ(t.Find("x"), nullptr);
}

TEST(AVLTree, can_delete_existing_elem_from_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(AVLTree, delete_elem_decreases_size_of_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.getSize(), 0);
}

TEST(AVLTree, can_delete_non_existing_elem_from_tree)
{
  AVLTree t;
  ASSERT_NO_THROW(t.Delete("x"));
}

TEST(AVLTree, delete_non_existing_elem_doesnt_change_size_of_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("bob");
  EXPECT_EQ(t.getSize(), 1);
}
