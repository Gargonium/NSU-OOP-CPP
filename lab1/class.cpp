#include "class.h"
#include <iostream>
#include <stdbool.h>
#include <string.h>
#define START_CAPACITY 10

using namespace std;

FlatMap::FlatMap() {
    kve = new KVE[START_CAPACITY];
    _capacity = START_CAPACITY;
    _size = 0;
};

FlatMap::FlatMap(const FlatMap& other_map) {
    kve = new KVE[other_map._capacity];

    copy(other_map.kve, other_map.kve + other_map._size, kve);

    _capacity = other_map._capacity;
    _size = other_map._size;
};

FlatMap::~FlatMap() {
    delete[] kve;
}

FlatMap& FlatMap::operator=(const FlatMap& other_map)
{
    if (this == &other_map) {
        return *this;
    };
    delete[] kve;

    kve = new KVE[other_map._capacity];

    copy(other_map.kve, other_map.kve + other_map._size, kve);

    _capacity = other_map._capacity;
    _size = other_map._size;

    return *this;
};

int FlatMap::getSize() const {
    return _size;
};

string& FlatMap::operator[](const string& key) {

    if (_size == 0) {
        kve[0].key = key;
        _size++;
        return kve[0].value;
    }

    if (_size == _capacity) {
        reCap();
    }

    int kve_index = binSearch(kve, 0, _size - 1, key);

    if (kve_index < 0) {

        kve_index = (kve_index + 1) * -1;

        if (kve[kve_index].key != " ") {
            shift(_size, kve_index, "r");
        }

        kve[kve_index].key = key;
        _size++;
    }

    return kve[kve_index].value;

}

bool FlatMap::contains(const string& key) {
    return (binSearch(kve, 0, _size - 1, key) >= 0) ? true : false;
}

int FlatMap::erase(const string& key) {

    int kve_index = binSearch(kve, 0, _size - 1, key);

    if (kve_index < 0) {
        return 0;
    }
    else {
        if (kve_index != _capacity - 1 && kve[kve_index + 1].key != " ") {
            shift(_size, kve_index, "l");
        }

        kve[_size - 1].key = " ";
        kve[_size - 1].value = " ";

        _size--;

        return 1;
    }
}

void FlatMap::clear() {
    while (_size > 0)
    {
        kve[_size - 1].key = " ";
        kve[_size - 1].value = " ";

        _size--;
    }
};

FlatMap::KVE* FlatMap::begin() {
    return kve;
}

FlatMap::KVE* FlatMap::end() {
    return kve + _size - 1;
}

FlatMap::KVE* FlatMap::find(const string& key) {
    int kve_index = binSearch(kve, 0, _size - 1, key);

    if (kve_index < 0) {
        return kve + _size - 1;
    }
    else {
        return kve + kve_index;
    }
}

int FlatMap::binSearch(KVE arr[], int low, int high, string a) {

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].key == a) {
            return mid;
        }

        if (arr[mid].key < a) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return (-1 * low) - 1;
};

void FlatMap::shift(int border, int index, string mode) {
    if (mode == "r") {
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
}

void FlatMap::reCap() {
    KVE* new_kve = new KVE[static_cast<size_t>(_capacity) * 2];

    copy(kve, kve + _size, new_kve);

    delete[] kve;

    kve = new_kve;

    _capacity *= 2;
}
