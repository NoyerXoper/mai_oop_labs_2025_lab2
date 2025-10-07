#include <gtest/gtest.h>

#include "seven.hpp"

TEST(StandartSevenTests, DefaultConstructorTest) {
    ASSERT_NO_THROW({
        Seven number1;
    });
}

TEST(StandartSevenTests, NonEmptyStringConstructorTest) {
    ASSERT_NO_THROW({
        Seven number1("1234");
    });
}

TEST(StandartSevenTests, NonEmptyInitializerListConstructorTest) {
    ASSERT_NO_THROW({
        Seven number1({1, 2});
    });
}

TEST(StandartSevenTests, NonZeroRepeatConstructorTest) {
    ASSERT_NO_THROW({
        Seven number1(1, 5);
    });
}

TEST(StandartSevenTests, CopyConstructor) {
    ASSERT_NO_THROW({
        Seven number(2, 4);
        Seven copy = number;
    });
}

TEST(StandartSevenTests, MoveConstructorTest) {
    ASSERT_NO_THROW({
        Seven number(2, 4);
        Seven copy = std::move(number);
    });
}

TEST(StandartSevenTests, EmptyInitilizerListTest) {
    ASSERT_THROW({
        Seven number({});
    }, std::invalid_argument);
}

TEST(StandartSevenTests, EmptyStringTest) {
    ASSERT_THROW({
        Seven number("");
    }, std::invalid_argument);
}

TEST(StandartSevenTests, ZeroRepeatTest) {
    ASSERT_THROW({
        Seven number(0, 2);
    }, std::invalid_argument);
}

TEST(StandartSevenTests, BadInitilizerListException) {
    ASSERT_THROW({
        Seven number({1, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'});
    }, std::invalid_argument);
}

TEST(StandartSevenTests, BadStringException) {
    ASSERT_THROW({
        Seven number("1HelloWorld!");
    }, std::invalid_argument);
}

TEST(StandartSevenTests, BadRepeatTest) {
    ASSERT_THROW({
        Seven number(3, 'd');
    }, std::invalid_argument);
}

TEST(ComparisonTests, StringConstructorAndInitializerConstructorTest) {
    Seven number1({1, 0});
    Seven number2("1");
    ASSERT_FALSE(number1.Equals(number2));

    ASSERT_FALSE(number1.Smaller(number2));
    ASSERT_TRUE(number1.Greater(number2));

    ASSERT_TRUE(number2.Smaller(number1));
    ASSERT_FALSE(number2.Greater(number1));
}

TEST(ComparisonTests, StringConstructorAndRepeatConstructorTest) {
    Seven number1(2, 4);
    Seven number2("01");
    ASSERT_FALSE(number1.Equals(number2));

    ASSERT_FALSE(number1.Smaller(number2));
    ASSERT_TRUE(number1.Greater(number2));

    ASSERT_TRUE(number2.Smaller(number1));
    ASSERT_FALSE(number2.Greater(number1));
}

TEST(OperationTests, AdditionTest) {
    Seven first("123");
    Seven second("6");
    Seven expected("132");

    Seven result = Seven::Add(first, second);
    ASSERT_TRUE(expected.Equals(result));
}

TEST(OperationTests, SubtractionTest) {
    Seven first("123");
    Seven second("6");
    Seven expected("114");

    Seven result = Seven::Subtract(first, second);
    ASSERT_TRUE(expected.Equals(result));
}

TEST(OperationTests, SubtractionResultZeroTest) {
    Seven first("123");
    Seven second("123");
    Seven expected("0");

    Seven result = Seven::Subtract(first, second);
    ASSERT_TRUE(expected.Equals(result));
}

TEST(OperationTests, SubtractionCollapsOfNumberTest) {
    Seven first("1234560123456");
    Seven second("1234560123455");
    Seven expected("1");

    Seven result = Seven::Subtract(first, second);
    ASSERT_TRUE(expected.Equals(result));
}

TEST(OperationTests, BadSubtractionTest) {
    ASSERT_THROW({
        Seven first("123");
        Seven second("6");

        Seven result = Seven::Subtract(second, first);
    }, std::invalid_argument);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
