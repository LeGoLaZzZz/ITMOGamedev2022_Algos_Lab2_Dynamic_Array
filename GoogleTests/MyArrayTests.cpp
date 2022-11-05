#include "gtest/gtest.h"
#include "../MyArray.h"

// To use a test fixture, derive a class from testing::Test.

class ArrayTests : public testing::Test {
protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    void SetUp() override {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }

    template<typename T>
    void TestConstructor() {
        MyArray<T> a;
        EXPECT_EQ(0, a.size());
        EXPECT_EQ(8, a.capacity());

    }

    template<typename T>
    void TestConstructorCapacity() {
        int capacity = 10;
        MyArray<T> a(capacity);
        EXPECT_EQ(0, a.size());
        EXPECT_EQ(capacity, a.capacity());
    }

    template<typename T>
    void TestCopyConstructor_Empty() {
        int capacity = 10;
        MyArray<T> a(capacity);
        MyArray<T> b = a;

        EXPECT_EQ(0, a.size());
        EXPECT_EQ(0, b.size());
        EXPECT_EQ(capacity, b.capacity());
    }

    template<typename T>
    void TestCopyConstructor_Filled(T *items, int capacity, int size) {

        MyArray<T> a(capacity);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        MyArray<T> b = a;

        EXPECT_EQ(size, a.size());
        EXPECT_EQ(size, b.size());
        EXPECT_EQ(capacity, b.capacity());

        for (int i = 0; i < a.size(); ++i) {
            EXPECT_EQ(items[i], a[i]);
        }

        for (int i = 0; i < b.size(); ++i) {
            EXPECT_EQ(items[i], b[i]);
        }
    }


    template<typename T>
    void TestMoveConstructor_Filled(T *items, int capacity, int size) {

        MyArray<T> a(capacity);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        MyArray<T> b = std::move(a);

        EXPECT_EQ(size, b.size());
        EXPECT_EQ(capacity, b.capacity());

        for (int i = 0; i < b.size(); ++i) {
            EXPECT_EQ(items[i], b[i]);
        }
    }


    template<typename T>
    void TestCopyAssigment_Filled(T *items, int capacity, int size) {

        MyArray<T> a(capacity);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        MyArray<T> b{};
        b = a;

        EXPECT_EQ(size, a.size());
        EXPECT_EQ(size, b.size());
        EXPECT_EQ(capacity, b.capacity());

        for (int i = 0; i < a.size(); ++i) {
            EXPECT_EQ(items[i], a[i]);
        }

        for (int i = 0; i < b.size(); ++i) {
            EXPECT_EQ(items[i], b[i]);
        }
    }

    template<typename T>
    void TestMoveAssigment_Filled(T *items, int capacity, int size) {

        MyArray<T> a(capacity);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        MyArray<T> b{};
        b = std::move(a);

        EXPECT_EQ(size, b.size());
        EXPECT_EQ(capacity, b.capacity());

        for (int i = 0; i < b.size(); ++i) {
            EXPECT_EQ(items[i], b[i]);
        }
    }

    template<typename T>
    void TestInsert(T *items, int size, int index, T value) {

        MyArray<T> a(size);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        EXPECT_EQ(size, a.size());
        EXPECT_EQ(size, a.capacity());

        for (int i = 0; i < a.size(); ++i) {
            EXPECT_EQ(items[i], a[i]);
        }

        a.insert(index, value);

        // до вставки
        for (int i = 0; i < index; ++i) {
            EXPECT_EQ(items[i], a[i]);
        }

        // вставка
        EXPECT_EQ(value, a[index]);

        // после вставки
        for (int i = index; i < a.size() - 1; ++i) {
            EXPECT_EQ(items[i], a[i + 1]);
        }
    }

    template<typename T>
    void TestRemove(T *items, int size, int removeIndex) {
        MyArray<T> a(size);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        a.remove(removeIndex);

        for (int i = 0; i < size - 1; ++i) {
            if (i < removeIndex) {
                EXPECT_EQ(items[i], a[i]);
            } else if (i > removeIndex) {
                EXPECT_EQ(items[i], a[i - 1]);
            }
        }
    }

    template<typename T>
    void TestCapacityExpand(T *items, int size) {
        MyArray<T> a(size);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        EXPECT_EQ(size, a.capacity());
        a.insert(items[0]);
        EXPECT_EQ(size * 2, a.capacity());

        for (int i = 1; i < size; ++i) {
            a.insert(items[i]);
        }
        EXPECT_EQ(size * 2, a.capacity());
        a.insert(items[0]);
        EXPECT_EQ(size * 4, a.capacity());

    }


    template<typename T>
    void TestIterator(T *items, int size) {
        MyArray<T> a(size);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        auto iter = a.iterator();

        for (int i = 0; i < size; ++i) {
            EXPECT_EQ(iter.get(), a[i]);
            iter.next();
            EXPECT_EQ(iter.hasNext(), i < size - 1);
        }
    }

    template<typename T>
    void TestReverseIterator(T *items, int size) {
        MyArray<T> a(size);
        for (int i = 0; i < size; ++i) {
            a.insert(items[i]);
        }
        auto iter = a.reverseIterator();

        for (int i = size - 1; i >= 0; --i) {
            EXPECT_EQ(iter.get(), a[i]);
            iter.next();
            EXPECT_EQ(iter.hasNext(), i > 0);
        }
    }


};


TEST_F(ArrayTests, DefaultConstructor) {
    TestConstructor<int>();
    TestConstructor<std::string>();
}

TEST_F(ArrayTests, TestConstructorCapacity) {
    TestConstructorCapacity<int>();
    TestConstructorCapacity<std::string>();
}

TEST_F(ArrayTests, TestCopyConstructor_Empty) {
    TestCopyConstructor_Empty<int>();
    TestCopyConstructor_Empty<std::string>();
}

TEST_F(ArrayTests, TestCopyConstructor_Filled) {
    int ints[3] = {1, 2, 3};
    TestCopyConstructor_Filled<int>(ints, 10, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestCopyConstructor_Filled<std::string>(strings, 10, 3);
}


TEST_F(ArrayTests, TestMoveConstructor_Filled) {
    int ints[3] = {1, 2, 3};
    TestMoveConstructor_Filled<int>(ints, 10, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestMoveConstructor_Filled<std::string>(strings, 10, 3);
}

TEST_F(ArrayTests, TestCopyAssigment_Filled) {
    int ints[3] = {1, 2, 3};
    TestCopyAssigment_Filled<int>(ints, 10, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestCopyAssigment_Filled<std::string>(strings, 10, 3);
}

TEST_F(ArrayTests, TestMoveAssigment_Filled) {
    int ints[3] = {1, 2, 3};
    TestMoveAssigment_Filled<int>(ints, 10, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestMoveAssigment_Filled<std::string>(strings, 10, 3);
}

TEST_F(ArrayTests, TestInsertEnd) {
    int ints[3] = {1, 2, 3};
    TestInsert<int>(ints, 3, 3, 4);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestInsert<std::string>(strings, 3, 3, "44444444444444444444444444444");;
}

TEST_F(ArrayTests, TestInsertStart) {
    int ints[3] = {1, 2, 3};
    TestInsert<int>(ints, 3, 0, 4);


    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestInsert<std::string>(strings, 3, 0, "44444444444444444444444444444");;
}

TEST_F(ArrayTests, TestRemoveStart) {
    int ints[3] = {1, 2, 3};
    TestRemove<int>(ints, 3, 0);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestRemove<std::string>(strings, 3, 0);;
}

TEST_F(ArrayTests, TestRemoveEnd) {
    int ints[3] = {1, 2, 3};
    TestRemove<int>(ints, 3, 2);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestRemove<std::string>(strings, 3, 2);
}


TEST_F(ArrayTests, TestRemoveMid) {
    int ints[3] = {1, 2, 3};
    TestRemove<int>(ints, 3, 1);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestRemove<std::string>(strings, 3, 1);
}

TEST_F(ArrayTests, TestCapacityExpand) {
    int ints[3] = {1, 2, 3};
    TestCapacityExpand<int>(ints, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestCapacityExpand<std::string>(strings, 3);
}

TEST_F(ArrayTests, TestIterator) {
    int ints[3] = {1, 2, 3};
    TestIterator<int>(ints, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestIterator<std::string>(strings, 3);
}

TEST_F(ArrayTests, TestReverseIterator) {
    int ints[3] = {1, 2, 3};
    TestReverseIterator<int>(ints, 3);

    std::string strings[3] = {"1111111", "22222222222", "33333333333333"};
    TestReverseIterator<std::string>(strings, 3);
}


TEST(ArrayTest, sampleTest) {

    MyArray<int> a;
    for (int i = 0; i < 10; ++i) {
        a.insert(i + 1);
    }
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ((i + 1) * 2, a[i]);
    }
}

TEST(ArrayTest, stringSampleTest) {

    MyArray<std::string> a;
    for (int i = 0; i < 10; ++i) {
        a.insert(std::to_string(i + 1));
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(std::to_string(i + 1), a[i]);
    }
}








