#pragma once
#include "gtest/gtest.h"
#include "TPostfix.h"
#include "TPostfix.cpp"

struct TabManForTests
{
  TableManager tabMan;
  TabManForTests(int size) :tabMan(size)
  {
    tabMan.Insert("sad", "-3x2+y3");
    tabMan.Insert("bad", "xyz-1");
    tabMan.Insert("ded", "z3+x2y");
    tabMan.Insert("Inside", "x7-z7");
  }
};

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p("x"));
}

TEST(TPostfix, can_create_postfix_with_argument)
{
  string polStr = "xyz+3x2y2";

  ASSERT_NO_THROW(TPostfix p(polStr));
}

TEST(TPostfix, can_create_postfix_with_correct_brackets)
{
  string polStr = "(xyz+3x2y2) + (x2-z)";

  ASSERT_NO_THROW(TPostfix p(polStr));
}

TEST(TPostfix, throws_when_create_postfix_with_too_much_closing_brackets)
{
  string polStr = "(xyz+3x2y2)) + (x2-z)";

  ASSERT_ANY_THROW(TPostfix p(polStr));
}

TEST(TPostfix, throws_when_create_postfix_with_too_much_opening_brackets)
{
  string polStr = "((xyz+3x2y2) + (x2-z)";

  ASSERT_ANY_THROW(TPostfix p(polStr));
}

TEST(TPostfix, can_create_postfix_with_correct_names_of_variables)
{
  string polStr = "sad + bad - bold + 3x2";

  ASSERT_NO_THROW(TPostfix p(polStr));
}

TEST(TPostfix, throws_when_create_postfix_with_incorrect_name_of_variable)
{
  string polStr = "3sad+3x2";

  ASSERT_ANY_THROW(TPostfix p(polStr));
}

TEST(TPostfix, can_get_infix)
{
  string polStr = "xyz+3x2y2";

  ASSERT_NO_THROW(TPostfix(polStr).GetInfix());
}

TEST(TPostfix, can_get_string_infix)
{
  string polStr = "3x2y2 + z2 ";
  string result = TPostfix(polStr).GetStringInfix();
  string a;
  EXPECT_EQ(polStr, TPostfix(polStr).GetStringInfix());
}

TEST(TPostfix, can_get_postfix)
{
  string polStr = "3x2y2 + z2";

  EXPECT_NO_THROW(TPostfix(polStr).GetPostfix());
}

TEST(TPostfix, can_get_string_postfix)
{
  string polStr = "3x2y2 + z2";
  string postfix = "3x2y2 z2 + ";

  EXPECT_EQ(postfix, TPostfix(polStr).GetStringPostfix());
}

TEST(TPostfix, can_get_postfix_with_operations_which_have_different_priorities)
{
  //string polStr = "(3x2+y2) * 3 - d(2x3 + xyz)/dx";
  string polStr = "3x2 + y2 * 2";

  EXPECT_NO_THROW(TPostfix(polStr).GetPostfix());
}

TEST(TPostfix, can_get_string_postfix_with_operations_which_have_different_priorities)
{
  string polStr = "3x2 + y2 * 2";
  string postfix = "3x2 y2 2 * + ";

  EXPECT_EQ(postfix, TPostfix(polStr).GetStringPostfix());
}

TEST(TPostfix, can_get_postfix_with_expressions_with_brackets)
{
  string polStr = "(3x2 + y2) * 2";

  EXPECT_NO_THROW(TPostfix(polStr).GetPostfix());
}

TEST(TPostfix, can_get_string_postfix_with_expressions_with_brackets)
{
  string polStr = "(3x2 + y2) * 2";
  string postfix = "3x2 y2 + 2 * ";

  EXPECT_NO_THROW(TPostfix(polStr).GetStringPostfix());
}

// +

TEST(TPostfix, can_calculate_arithmetic_expression_with_plus)
{
  string polStr = "3xyz + 7xyz + x3";
  Polinom result("x3+10xyz");

  EXPECT_EQ(result, TPostfix(polStr).Calculate());
}

TEST(TPostfix, can_be_friends_with_sad)
{
  string polStr = "(((((sad)))))";
  Polinom result("-3x2+y3");

  TabManForTests tm(10);

  EXPECT_EQ(result, TPostfix(polStr, &tm.tabMan).Calculate());
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_plus_and_variables)
{
  string polStr = "sad + bad + 3x2 + 7";
  Polinom result("xyz+y3+6");

  TabManForTests tm(10);
  EXPECT_EQ(result, TPostfix(polStr, &tm.tabMan).Calculate());
}

// -

TEST(TPostfix, can_calculate_arithmetic_expression_with_minus)
{
  string polStr = "3x2 - 3x2 + xyz";
  Polinom result("xyz");

  EXPECT_EQ(result, TPostfix(polStr).Calculate());
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_minus_and_variables)
{
  string polStr = "sad - bad - 3x2 + 7";
  Polinom result("-6x2-xyz+y3+8");

  TabManForTests tm(10);
  EXPECT_EQ(result, TPostfix(polStr, &tm.tabMan).Calculate());
}

// *

TEST(TPostfix, can_calculate_arithmetic_expression_with_multiplication)
{
  string polStr = "3x2 * 3x2 * xyz * 2";
  Polinom result("18x5yz");

  EXPECT_EQ(result, TPostfix(polStr).Calculate());
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_multiplication_and_variables)
{
  string polStr = "sad * bad";
  Polinom result("-3x3yz+3x2+xy4z-y3");

  TabManForTests tm(10);
  EXPECT_EQ(result, TPostfix(polStr, &tm.tabMan).Calculate());
}

// d

TEST(TPostfix, can_calculate_arithmetic_expression_with_differentional)
{
  string polStr = "d(3xy2z - z3 + y)/dz";
  Polinom result("3xy2-3z2");

  EXPECT_EQ(result, TPostfix(polStr).Calculate());
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_differentional_and_variables)
{
  string polStr = "d(sad)/dx + d(Inside)/dz";
  Polinom result("-6x-7z6");

  TabManForTests tm(10);
  EXPECT_EQ(result, TPostfix(polStr, &tm.tabMan).Calculate());
}

//I
TEST(TPostfix, can_calculate_arithmetic_expression_with_integral)
{
  string polStr = "I(x7+z2)dx + I(x2)dz";
  Polinom result("0.125x8+x2z+xz2");

  EXPECT_EQ(result, TPostfix(polStr).Calculate());
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_integral_and_variables)
{
  string polStr = "I(sad)dx + I(Inside)/dz";
  Polinom result("-1x3+x7z+xy3-0.125z8");

  TabManForTests tm(10);
  EXPECT_EQ(result, TPostfix(polStr, &tm.tabMan).Calculate());
}


