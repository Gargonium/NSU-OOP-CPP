#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// I want to recreate this, with Hash-array

//KVE - Key-Value Element

class FlatMap {
private:
	int _size;
	string* _keys;
	string* _values;
	//Add _capacity	

	int KVEIndex(string key) {
		// use sort array!!!!
		bool flag = false;
		int l = 0; 
		int r = _size;
		int mid;

		while ((l <= r) && (flag != true)) {
			mid = (l + r) / 2; 

			if (_keys[mid] == key) flag = true; 
			if (_keys[mid] > key) r = mid - 1; 
			else l = mid + 1;
		}

		if (flag) {
			return mid;
		}
		else {
			return -1;
		}
	}

	void Àppend(string key, string value) {
		string* new_keys = new string[_size + 1];
		string* new_values = new string[_size + 1];

		copy(_keys, _keys + _size, new_keys);
		copy(_values, _values + _size, new_values);

		delete[] _keys;
		delete[] _values;

		new_keys[_size + 1] = key;
		new_values[_size + 1] = value;

		_keys = new_keys;
		_values = new_values;

		_size++;
	}

	void ChangeValue(int kve_index, string value) {
		_values[kve_index] = value;
	}

	void DelKVE(string key) {
		int kve_index = KVEIndex(key);
		if (kve_index == -1) {
			cout << "This key is not existed" << endl;
			return;
		}

		string* new_keys = new string[_size - 1];
		string* new_values = new string[_size - 1];
		for (int i = 0; i < _size; i++) {
			if (i == kve_index) {
				continue;
			}

			new_keys[i] = _keys[i];
			new_values[i] = _values[i];
		}

		delete[] _keys;
		delete[] _values;

		_keys = new_keys;
		_values = new_values;

		_size--;
	}

public:
	FlatMap() {
		_size = 0;
		_keys = new string[_size];
		_values = new string[_size];
	}

	FlatMap(const FlatMap& other_map) {
		_size = other_map._size;
		_keys = other_map._keys;
		_values = other_map._values;
		copy(_keys, _keys + _size, other_map._keys);
		copy(_values, _values + _size, other_map._values);
	}

	~FlatMap() {
		delete[] _keys;
		delete[] _values;
	}

	FlatMap& FlatMap::operator=(const FlatMap& other_map) {
		if (this == &other_map) {
			return *this;
		}
		delete[] _keys;
		delete[] _values;
		_keys = new string[other_map._size];
		_values = new string[other_map._size];

		copy(_keys, _keys + _size, other_map._keys);
		copy(_values, _values + _size, other_map._values);

		_size = other_map._size;
	}

	string& operator[] (const string& key) {
		int kve_index = KVEIndex(key);
		if (kve_index == -1) {
			this->Àppend(key, "");
		}
		return _values[kve_index];
	}
};

int main() {

	FlatMap a;
	a["key"] = "value";

	string value = a["key"];
 
    return 0;
}
