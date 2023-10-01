#include "task1.h"
using namespace std;

//size_t FlatMap::get_size() {
//    return size;
//};
//
//FlatMap::FlatMap(const FlatMap& other_map) {
//
//}
//
//FlatMap& FlatMap::operator=(const FlatMap& n) {
//    if (this == &n) {
//        return *this;
//    }
//    delete[] _arr;
//    _arr = new string[n.size];
//    copy(n._arr);
//    size = n.size;
//}
//
//FlatMap::FlatMap() {
//    size = 0;
//    string _arr = new string[size];
//}
//
//
//int binary_search(string* arr, string key, int size) {
//    bool flag = false;
//    int l = 0; // левая граница
//    int r = size; // правая граница
//    int mid;
//
//    while ((l <= r) && (flag != true)) {
//        mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]
//
//        if (arr[mid] == key) flag = true; //проверяем ключ со серединным элементом
//        if (arr[mid] > key) r = mid - 1; // проверяем, какую часть нужно отбросить
//        else l = mid + 1;
//    }
//    
//    if (flag) {
//        return mid;
//    }
//    else {
//        return -1;
//    }
//};