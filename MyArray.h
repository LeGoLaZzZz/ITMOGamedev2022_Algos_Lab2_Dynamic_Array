#ifndef LAB2ARRAY_MYARRAY_H
#define LAB2ARRAY_MYARRAY_H

#include <utility>

template<typename T>
class MyArray final {
    T *_data;
    int _size;
    int _capacity;

public:

    MyArray() {
        _size = 0;
        _capacity = 8;
        _data =(T *) malloc(_capacity * sizeof(T));
    }

    MyArray(int capacity) {
        _size = 0;
        _capacity = capacity;
        _data =(T *) malloc(_capacity * sizeof(T));
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
        _data =(T *) malloc(_capacity * sizeof(T));

        for (int i = 0; i < _size; ++i) {
            new(_data + i) T(other._data[i]);
        }

    }

    MyArray(MyArray &&other) {
        _size = other._size;
        _data = other._data;
        other._data = nullptr;
        other._size = 0;
    }

    MyArray &operator=(const MyArray &other) {
        if (this != &other) {

            for (int i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            free(_data);

            _size = other._size;
            _capacity = other._capacity;
            _data = (T *)malloc(_capacity * sizeof(T));

            for (int i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }

            return *this;
        }
    }

    MyArray &operator=(MyArray other) {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
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

            other._data = nullptr;
            other._size = 0;
        }
    }


    int insert(const T &value) {

        if (_size == _capacity) ExpandCapacity();

        T *p = (T *)malloc((_size + 1) * sizeof(T));

        for (int i = 0; i < _size; ++i) {
            new(p + i) T(std::move(_data[i]));
        }

        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);

        _data = p;
        new(_data + _size) T(value);
        _size += 1;
        return _size-1;
    }

    int insert(int index, const T &value) {
        if (_size == _capacity) ExpandCapacity();

        T *p = (T *)malloc((_size + 1) * sizeof(T));

        for (int i = 0; i < index; ++i) {
            new(p + i) T(std::move(_data[i]));
        }
        new(p + index) T(value);

        for (int i = index + 1; i < _size + 1; ++i) {
            new(p + i) T(std::move(_data[i]));
        }

        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);

        _data = p;
        new(_data + _size) T(value);
        _size += 1;

        return index;
    }

    void remove(int index) {

        T *p = (T *)malloc((_size - 1) * sizeof(T));

        for (int i = 0; i < index; ++i) {
            new(p + i) T(std::move(_data[i]));
        }

        for (int i = index; i < _size - 1; ++i) {
            new(p + i - 1) T(std::move(_data[i]));
        }

        for (int i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        free(_data);

        _data = p;
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

    void ExpandCapacity() {

    }

    class Iterator {
        int _curElementId;
        bool _isReversed;
        MyArray<T> * myArray;

    public:
        Iterator(MyArray<T> * other, bool isReversed) {
            myArray = other;
            _isReversed = isReversed;
            if (_isReversed)_curElementId = myArray->size() - 1;
            else _curElementId = 0;
        }

        const T &get() const {
            return (*myArray)[_curElementId];
        }

        void set(const T &value) {
            (*myArray)[_curElementId] = value;
        }

        void next() {
            if (_isReversed) _curElementId--;
            else _curElementId++;
        }

        bool hasNext() const {
            if (_isReversed) return 0 != _curElementId;
            else return (myArray->size()) != (_curElementId);
        }

    };

    Iterator iterator() {
        return Iterator(this, false);
    }
//    ConstIterator iterator() const;

    Iterator reverseIterator() {
        return Iterator(this, true);
    }
//    ConstIterator reverseIterator() const;


};


#endif //LAB2ARRAY_MYARRAY_H
