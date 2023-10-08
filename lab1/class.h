#pragma once
#include <iostream>

using namespace std;

class FlatMap {
    struct KVE {
        string key;
        string name;
    };
    KVE* kve;

    int _capacity;
    int _size;

public:
    FlatMap();

    FlatMap(const FlatMap& other_map);

    ~FlatMap();

    FlatMap& operator=(const FlatMap& other_map);

    int size() const;

    string& operator[](const string& key);

    bool contains(const string& key);

    int erase(const string& key);

    void clear();

    string& begin();

    string& end();

    string& find(const string& key);

private:

    int binSearch(KVE arr[], int low, int high, string a);
    void shift(KVE* arr, int border, int index, string mode);
    void reCap();

};
