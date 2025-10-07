#include <initializer_list>

#include <gtest/gtest.h>

#include "array.hpp"

TEST(StandartArrayTest, CreationTest) {
    Array array;
    ASSERT_EQ(array.Size(), 0);
    ASSERT_NE(array.Capacity(), 0);
}

TEST(StandartArrayTest, PushBackTest) {
    Array array;
    unsigned char character = 'h';
    array.PushBack(character);
    ASSERT_EQ(array.Get(0), character);
    ASSERT_EQ(array.Size(), 1);
}

TEST(StandartArrayTest, ReserveTest) {
    Array array;
    std::size_t initialCapacity = array.Capacity();
    array.Reserve(initialCapacity + 1);
    ASSERT_EQ(array.Capacity(), initialCapacity + 1);
}

TEST(StandartArrayTest, PushBackOutOfBounds) {
    std::size_t initialCapacity = 5;
    Array array(initialCapacity);
    for (int i = 0; i < initialCapacity; ++i) {
        array.PushBack(0);
    }
    array.PushBack(0);
    ASSERT_NE(array.Capacity(), initialCapacity);
    ASSERT_EQ(array.Size(), initialCapacity + 1);
}

TEST(StandartArrayTest, CopyConstructorTest) {
    std::size_t size = 12;
    Array array(size, 'a');
    Array copy = array;
    ASSERT_EQ(array.Size(), size);
    ASSERT_EQ(copy.Size(), size);

    for (int i = 0; i < size; ++i) {
        ASSERT_EQ(array.Get(i), copy.Get(i));
    }

}

TEST(StandartArrayTest, CopyEqualsTest) {
    std::size_t size = 12;
    Array array(size, 'a');
    Array copy = array;

    ASSERT_TRUE(array.Equals(copy));
    ASSERT_TRUE(copy.Equals(array));
}

TEST(StandartArrayTest, ManualCopyEqualsTest) {
    std::size_t size = 12;
    unsigned char ch = 'a';
    Array array(size, ch);
    Array other;

    for (int i = 0; i < size; ++i) {
        other.PushBack(ch);
    }

    ASSERT_TRUE(array.Equals(other));
    ASSERT_TRUE(other.Equals(array));
}

TEST(ReserveArrayTest, BasicTest) {
    std::size_t initialCapacity = 20;
    Array array(initialCapacity);
    ASSERT_EQ(array.Capacity(), initialCapacity);
}

TEST(ReserveArrayTest, ReserveTest) {
    Array array;
    std::size_t initialCapacity = array.Capacity();
    if (initialCapacity != 1) {
        array.Reserve(std::max(static_cast<std::size_t>(1), initialCapacity - 1));
        ASSERT_EQ(array.Capacity(), initialCapacity);
    }
    array.Reserve(initialCapacity + 1);
    ASSERT_EQ(array.Capacity(), initialCapacity + 1);
}


TEST(OtherConstructorsTests, InitializerListTest) {
    Array array({'1', 'd', 'b'});
    ASSERT_EQ(array.Capacity(), 3);
    ASSERT_EQ(array.Size(), 3);
    ASSERT_EQ(array.Get(0), '1');
    ASSERT_EQ(array.Get(1), 'd');
    ASSERT_EQ(array.Get(2), 'b');
}

TEST(OtherConstructorsTests, StringTest) {
    std::string str = "abs";
    Array array(str);
    ASSERT_EQ(array.Capacity(), 3);
    ASSERT_EQ(array.Size(), 3);
    ASSERT_EQ(array.Get(0), 'a');
    ASSERT_EQ(array.Get(1), 'b');
    ASSERT_EQ(array.Get(2), 's');
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
