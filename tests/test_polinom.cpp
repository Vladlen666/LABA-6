#include "gtest/gtest.h"
#include "polinom.hpp"

TEST(Polinom, can_create_polinom)
{
  ASSERT_NO_THROW(Polinom p);
}

TEST(Polinom, can_init_polinom)
{
  Polinom p;
  ASSERT_NO_THROW(p = Polinom("2xy5z"));
}

TEST(Polinom, can_print_polinom)
{
  Polinom p("2x5y");
  EXPECT_EQ(p.ToString(), "2x5y");
}

TEST(Polinom, can_copy_polinom)
{
  Polinom p1("2x5y"), p2;
  p2 = p1;
  EXPECT_EQ(p2.ToString(), "2x5y");
}

TEST(Polinom, can_compare_polinom)
{
  Polinom p1("2x5y"), p2("2x5y");
  bool l = p1 == p2;
  EXPECT_EQ(true, l);
}

TEST(Polinom, can_add_polinom)
{
  Polinom p1("2x5y"), p2("3y"), p3;
  p3 = p1 + p2;
  EXPECT_EQ(p3.ToString(), "2x5y+3y");
}

TEST(Polinom, can_inverse_polinom)
{
  Polinom p1("2x5y"), p2;
  p2 = -p1;
  EXPECT_EQ("-2x5y", p2.ToString());
}

TEST(Polinom, can_subtract_polinom)
{
  Polinom p1("2x5y"), p2("3y"), p3;
  p3 = p1 - p2;
  EXPECT_EQ(p3.ToString(), "2x5y-3y");
}

TEST(Polinom, can_multiply_polinom)
{
  Polinom p1("2x5y"), p2("3y"), p3;
  p3 = p1 * p2;
  EXPECT_EQ(p3.ToString(), "6x5y2");
}

TEST(Polinom, can_calculate_polinom)
{
  Polinom p1("2x5y");
  EXPECT_EQ(p1.Calculate(1, 1, 0), 2);
}

TEST(Polinom, can_differentiate_polinom)
{
  Polinom p1("2x5y");
  EXPECT_EQ(p1.Differentiate('x').ToString(), "10x4y");
}

TEST(Polinom, can_integrate_polinom)
{
  Polinom p1("2x5y");
  EXPECT_EQ(p1.Integrate('y').ToString(), "x5y2");
}
