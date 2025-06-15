#include <gtest/gtest.h>

#include <print>
#include <string_view>

using std::println;
using std::string_view;

TEST(MathTestSuite, TrivialAddition) {
  EXPECT_EQ(1 + 1, 2);
}

TEST(StringTestSuite, HandlesStringView) {
  constexpr string_view message = "Hello, Modern C++!";
  
  EXPECT_EQ(message.length(), 18);
  EXPECT_TRUE(message.starts_with("Hello"));
  EXPECT_FALSE(message.empty());
}

int main(int argc, char* argv[]) {
  println("--- Running Google Test Suite ---");

  ::testing::InitGoogleTest(&argc, argv);

  const int result = RUN_ALL_TESTS();

  println("--- Test execution finished. ---");

  return result;
}

