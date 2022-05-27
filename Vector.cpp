#include "Vector.h"


Vector::Vector(const Value* rawArray, const size_t size, float coef) {
    if (coef <= 1) {
        coef = 2;
    }
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    _data = new Value[_capacity];
    for (int i = 0; i < size; i++) {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other):
        _size(other._size), _multiplicativeCoef(other._multiplicativeCoef),
        _capacity(other._size) {
    _data = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _capacity = other._size;
    delete[] _data;
    _data = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
    return *this;
}



Vector::Vector(Vector&& other) noexcept {
    if (this == &other) {
        return;
    }
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = other._data;
    _capacity = other._size;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 1;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    std::swap(*this, other);
    return *this;
}

Vector::~Vector() {
    delete[] _data;
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    if (pos > _size) {
        return;
    } // ???

    reserve(_size + size);
    if (_size > 0) {
        for (int i = int(_size); i > pos; i--) {
            _data[i + size - 1] = _data[i - 1];
        }
    }
    for (int i = 0; i < size; i++) {
        _data[pos + i] = values[i];
    }
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos) {
    insert(vector._data, vector._size, pos);
}

void Vector::insert(const Value& value, size_t pos) {
    insert(&value, 1, pos);
}

void Vector::pushBack(const Value& value) {
    insert(&value, 1, _size);
}

void Vector::pushFront(const Value& value) {
    insert(&value, 1, 0);
}

void Vector::erase(size_t pos, size_t count) {
    if (_size == 0) {
        throw std::out_of_range("_size == 0");
    }
    if (pos + count > _size) {
        count = _size - pos;
    }

    for (int i = 0; i < _size - pos - count; i++) {
        _data[pos + i] = _data[pos + count + i];
    }
    _size -= count;
}

void Vector::popBack() {
    erase(_size - 1);
}

void Vector::popFront() {
    erase(0);
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    if (endPos >= _size) {
        _size = beginPos;
    }
    else {
        erase(beginPos, endPos - beginPos);
    }
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}

double Vector::loadFactor() const {
    return static_cast<double>(_size) / static_cast<double>(_capacity);
}

Value& Vector::operator[](size_t ind) {
    return _data[ind];
}

const Value& Vector::operator[](size_t ind) const {
    return _data[ind];
}

void Vector::shrinkToFit() {
    Value* newData = new Value[_size];
    for (int i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }
    _capacity = _size;
    delete _data;
    _data = newData;
}

void Vector::reserve(size_t capacity) {
    if (capacity <= _capacity) {
        return;
    }
    if (_capacity == 0) {
        _capacity = size_t(_multiplicativeCoef);
    }
    if (_capacity < capacity) {
        _capacity = capacity;
    }
    Value* dataTmp = new Value[_capacity];
    for (int i = 0; i < _size; i++) {
        dataTmp[i] = _data[i];
    }
    delete[] _data;
    _data = dataTmp;
}

long long Vector::find(const Value& value) const {
    for (long long i = 0; i < _size; i++) {
        if (_data[i] == value) {
            return i;
        }
    }
    return -1;
}


Vector::Iterator::Iterator(Value* ptr) {
    _ptr = ptr;
}

Value& Vector::Iterator::operator*() {
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const {
    return *_ptr;
}

Value* Vector::Iterator::operator->() {
    return _ptr;
}

const Value* Vector::Iterator::operator->() const {
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
    ++_ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int noUse) {
    Value* tmpptr = _ptr;
    _ptr++;
    return Vector::Iterator(tmpptr);
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin() {
    return Vector::Iterator(&_data[0]);
}

Vector::Iterator Vector::end() {
    return Vector::Iterator(&_data[_size]);
}