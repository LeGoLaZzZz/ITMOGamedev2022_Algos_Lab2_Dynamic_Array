#ifndef LAB2ARRAY_MYARRAY_H
#define LAB2ARRAY_MYARRAY_H

#include <utility>
#include <iostream>

template<typename T>
class MyArray final {
    T *_data;
    int _size;
    int _capacity;
    const int _expandCapacityModifier = 2;

public:

    MyArray() {
        _size = 0;
        _capacity = 8;
        _data = (T *) malloc(_capacity * sizeof(T));
    }

    MyArray(int capacity) {
        _size = 0;
        _capacity = capacity;
        _data = (T *) malloc(_capacity * sizeof(T));
    }

    ~MyArray() {
        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);
    }


    MyArray(const MyArray &other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = (T *) malloc(_capacity * sizeof(T));

        for (int i = 0; i < _size; ++i) {
            new(_data + i) T(other._data[i]);
        }

    }

    MyArray(MyArray &&other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = other._data;
        other._data = nullptr;
        other._size = 0;
    }

////    вариант без copyswap
//    MyArray &operator=(const MyArray &other) {
//        if (this != &other) {
//
//            for (int i = 0; i < _size; ++i) {
//                _data[i].~T();
//            }
//            free(_data);
//
//            _size = other._size;
//            _capacity = other._capacity;
//            _data = (T *)malloc(_capacity * sizeof(T));
//
//            for (int i = 0; i < _size; ++i) {
//                _data[i] = other._data[i];
//            }
//
//            return *this;
//        }
//    }

////    конфликтует с перемещающим=
//    MyArray &operator=(MyArray other) {
//        std::swap(_data, other._data);
//        std::swap(_size, other._size);
//        std::swap(_capacity, other._capacity);
//        return *this;
//    }

    MyArray &operator=(const MyArray &other) {
            MyArray stackOther = other;
            std::swap(_data, stackOther._data);
            std::swap(_size, stackOther._size);
            std::swap(_capacity, stackOther._capacity);
            return *this;
    }

    MyArray &operator=(MyArray &&other) noexcept {
        if (this != &other) {

            for (int i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            free(_data);

            _size = other._size;
            _data = other._data;
            _capacity = other._capacity;

            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;

            return *this;
        }
    }


    int insert(const T &value) {

        if (_size == _capacity) {
            _capacity *= _expandCapacityModifier;

            T *p = (T *) malloc((_capacity) * sizeof(T));
            for (int i = 0; i < size(); ++i) {
                new(p + i) T(std::move(_data[i]));
            }

            for (int i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            free(_data);

            _data = p;
        }

        new(_data + _size) T(value);
        _size += 1;
        return _size - 1;
    }


    int insert(int index, const T &value) {

        if (_size == _capacity) {
            _capacity *= _expandCapacityModifier;

            T *p = (T *) malloc((_capacity) * sizeof(T));

            for (int i = 0; i < index; ++i) {
                new(p + i) T(std::move(_data[i]));
            }
            new(p + index) T(value);

            for (int i = index + 1; i < _size + 1; ++i) {
                new(p + i) T(std::move(_data[i - 1]));
            }

            for (int i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            free(_data);

            _data = p;


        } else {

            for (int i = index + 1; i < _size + 1; ++i) {
                new(_data + i) T(std::move(_data[i - 1]));
            }
            _data[index].~T();
            new(_data + index) T(value);

        }
        _size += 1;

        return index;
    }

    void remove(int index) {

        if(size()==0){
            throw std::exception("Array is empty");
        }

        for (int i = index; i < _size-1; ++i) {
            _data[i] = std::move(_data[i+1]);
        }
        _data[_size-1].~T();
        _size -= 1;
    }

    const T &operator[](int index) const {
        return _data[index];
    }

    T &operator[](int index) {
        return _data[index];
    }

    int size() const {
        return _size;
    }

    int capacity() const {
        return _capacity;
    }

    class AbstractIterator {
    protected:
        int _curElementId;
        bool _isReversed;
        MyArray<T> *myArrayPtr;
        T *curPtr;

    public:
        AbstractIterator(MyArray<T> *other, bool isReversed) {
            myArrayPtr = other;
            _isReversed = isReversed;
            if (_isReversed) {
                _curElementId = myArrayPtr->size() - 1;
                curPtr = (myArrayPtr->_data + (myArrayPtr->size() - 1));
            } else {
                _curElementId = 0;
                curPtr = (myArrayPtr->_data);
            }
        }

        const T &get() const {
            return *curPtr;
//            return (*myArrayPtr)[_curElementId];
        }

        void next() {
            if (!hasNext()) throw std::exception("Out of iter");

            if (_isReversed) {
                curPtr--;
                _curElementId--;
            } else {
                curPtr++;
                _curElementId++;
            }
        }

        bool hasNext() const {
            if (_isReversed) return -1 < _curElementId;
            else return (myArrayPtr->size()) > (_curElementId);
        }

    };

    class ConstIterator : public AbstractIterator {
    public:
        ConstIterator(MyArray<T> *other, bool isReversed) : AbstractIterator(other, isReversed) {
        }
    };

    class Iterator : public AbstractIterator {

    public:
        Iterator(MyArray<T> *other, bool isReversed) : AbstractIterator(other, isReversed) {
        }

        void set(const T &value) {
            *curPtr = value;
//            (*myArrayPtr)[_curElementId] = value;
        }
    };

    Iterator iterator() {
        return Iterator(this, false);
    }

    ConstIterator constIterator() {
        return ConstIterator(this, false);
    }

    Iterator reverseIterator() {
        return Iterator(this, true);
    }

    ConstIterator constReverseIterator() {
        return ConstIterator(this, true);
    }

};


#endif //LAB2ARRAY_MYARRAY_H
