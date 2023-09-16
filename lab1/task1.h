#pragma once

#include <string>
#include <string_view>

using namespace std;

class FlatMap {
public:
    FlatMap();

    FlatMap(const FlatMap& other_map); 

    ~FlatMap() {
        delete[] _arr;
    };
    
    size_t get_size();

private:
    int _size;
    string _arr[];
};