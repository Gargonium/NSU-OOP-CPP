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

    string& begin();

    string& end();

    string& find(const string& key);

private:

    int binSearch(KVE arr[], int low, int high, string a);
    void shift(int border, int index, string mode);
    void reCap();

};
