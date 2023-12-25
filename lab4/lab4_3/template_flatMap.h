#pragma once
#include <iostream>
#include <stdbool.h>
#include <string.h>

const int START_CAPACITY = 10;

using namespace std;

template<class Key, class Value>
class FlatMap {
    struct KVE {
        Key* keyPtr;
        Key key;
        Value* valuePtr;
        Value value;
    };
    KVE* kve;

    int _capacity;
    int _size;

public:
    FlatMap() {
        kve = new KVE[START_CAPACITY];
        _capacity = START_CAPACITY;
        _size = 0;
    };

    FlatMap(const FlatMap& other_map) {
        kve = new KVE[other_map._capacity];

        copy(other_map.kve, other_map.kve + other_map._size, kve);

        _capacity = other_map._capacity;
        _size = other_map._size;
    };

    ~FlatMap() {
        delete[] kve;
    };

    FlatMap& operator=(const FlatMap& other_map) {
        if (this != &other_map) {
            delete[] kve;

            kve = new KVE[other_map._capacity];

            copy(other_map.kve, other_map.kve + other_map._size, kve);

            _capacity = other_map._capacity;
            _size = other_map._size;
        };

        return *this;
    };

    int getSize() const {
        return _size;
    };

    Value& operator[](const Key& key) {
        if (_size == 0) {
            kve[0].key = key;
            _size++;
            return kve[0].value;
        }

        if (_size == _capacity) {
            reCap();
        }

        int kve_index = binSearch(0, _size - 1, key);

        if (kve_index < 0) {
            kve_index = (kve_index + 1) * -1;

            if (kve[kve_index].keyPtr != (Key*)nullptr) {
                shift(_size, kve_index, 'r');
            }

            kve[kve_index].key = key;
            _size++;
        }

        return kve[kve_index].value;
    };

    bool contains(const Key& key) {
        return (binSearch(0, _size - 1, key) >= 0) ? true : false;
    };

    int erase(const Key& key) {
        int kve_index = binSearch(0, _size - 1, key);

        if (kve_index < 0) {
            return 0;
        }
        else {
            if (kve_index != _capacity - 1 && kve[kve_index + 1].keyPtr != (Key*)nullptr) {
                shift(_size, kve_index, 'l');
            }

            kve[_size - 1].keyPtr = (Key*)nullptr;
            kve[_size - 1].valuePtr = (Key*)nullptr;

            _size--;

            return 1;
        }
    };

    void clear() {
        while (_size > 0) {
            kve[_size - 1].keyPtr = (Key*)nullptr;
            kve[_size - 1].valuePtr = (Key*)nullptr;

            _size--;
        }
    };

    KVE* begin() {
        return kve;
    };

    KVE* end() {
        return kve + _size;
    };

    KVE* find(const Key& key) {
        int kve_index = binSearch(0, _size - 1, key);

        if (kve_index < 0) {
            return kve + _size - 1;
        }
        else {
            return kve + kve_index;
        }
    };

private:
    int binSearch(int low, int high, const Key& a) {
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (kve[mid].key == a) {
                return mid;
            }

            if (kve[mid].key < a) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return (-1 * low) - 1;
    };

    void shift(int border, int index, char mode) {
        if (mode == 'r') {
            while (border != index) {
                kve[border] = kve[border - 1];
                border--;
            }
        }
        else {
            while (index != border - 1) {
                kve[index] = kve[index + 1];
                index++;
            }
        }
    };

    void reCap() {
        KVE* new_kve = new KVE[static_cast<size_t>(_capacity) * 2];

        copy(kve, kve + _size, new_kve);

        delete[] kve;

        kve = new_kve;

        _capacity *= 2;
    };
};
