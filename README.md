# ITMOGamedev2022_Algos_Lab2_Dynamic_Array

### MyArray.h:
 
- MyArray() 
- MyArray(int capacity)  
- ~MyArray()  
- MyArray(const MyArray &other)  
- MyArray(MyArray &&other)  

- //    вариант без copyswap   MyArray &operator=(const MyArray &other)  

- //    конфликтует с перемещающим= MyArray &operator=(MyArray other) 

- MyArray &operator=(MyArray &other)  
- MyArray &operator=(MyArray &&other) noexcept  
- int insert(const T &value)  
- int insert(int index, const T &value)  
- void remove(int index)  
- const T &operator[](int index) const  
- T &operator[](int index)  
- int size() const  
- int capacity() const  
- class Iterator  
- Iterator iterator()  
- Iterator reverseIterator()  

### GoogleTests/MyArrayTests.cpp:
- TEST_F(ArrayTests, DefaultConstructor) 
- TEST_F(ArrayTests, TestConstructorCapacity)
- TEST_F(ArrayTests, TestCopyConstructor_Empty)
- TEST_F(ArrayTests, TestCopyConstructor_Filled)
- TEST_F(ArrayTests, TestMoveConstructor_Filled)
- TEST_F(ArrayTests, TestCopyAssigment_Filled)
- TEST_F(ArrayTests, TestMoveAssigment_Filled)
- TEST_F(ArrayTests, TestInsertEnd)
- TEST_F(ArrayTests, TestInsertStart)
- TEST_F(ArrayTests, TestRemoveStart) 
- TEST_F(ArrayTests, TestRemoveEnd) 
- TEST_F(ArrayTests, TestRemoveMid) 
- TEST_F(ArrayTests, TestCapacityExpand) 
- TEST_F(ArrayTests, TestIterator)
- TEST_F(ArrayTests, TestReverseIterator)