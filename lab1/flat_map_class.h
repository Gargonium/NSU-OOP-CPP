#pragma once
#include <iostream>

using namespace std;

class FlatMap {
    struct KVE {
        string key;
        string value;
    };
    KVE* kve;

    int _capacity;
    int _size;

public:
    FlatMap();

    FlatMap(const FlatMap& other_map);

    ~FlatMap();

    FlatMap& operator=(const FlatMap& other_map);

    int getSize() const;

    string& operator[](const string& key);

    bool contains(const string& key);

    int erase(const string& key);

    void clear();

    KVE* begin();

    KVE* end();

    KVE* find(const string& key);

private:

    int binSearch(int low, int high, const string& a);
    void shift(int border, int index, char mode);
    void reCap();

};
