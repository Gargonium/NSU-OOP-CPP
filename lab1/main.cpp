
#include "task1.h"
#include <iostream>
#include <string>

//KVE - Key-Value Element

class FlatMap {
private:
	int size;
	string* keys;
	string* values;

	int KVEIndex(string key) {
		bool flag = false;
		int l = 0; 
		int r = size;
		int mid;

		while ((l <= r) && (flag != true)) {
			mid = (l + r) / 2; 

			if (keys[mid] == key) flag = true; 
			if (keys[mid] > key) r = mid - 1; 
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
		string* new_keys = new string[size + 1];
		string* new_values = new string[size + 1];
		for (int i = 0; i < size; i++) {
			new_keys[i] = keys[i];
			new_values[i] = values[i];
		}
		delete[] keys;
		delete[] values;

		new_keys[size + 1] = key;
		new_values[size + 1] = value;

		keys = new_keys;
		values = new_values;

		size++;
	}

	void ChangeValue(int kve_index, string value) {
		values[kve_index] = value;
	}

	void DelKVE(string key) {
		int kve_index = KVEIndex(key);
		if (kve_index == -1) {
			cout << "This key is not existed" << endl;
			return;
		}

		string* new_keys = new string[size - 1];
		string* new_values = new string[size - 1];
		for (int i = 0; i < size; i++) {
			if (i == kve_index) {
				continue;
			}

			new_keys[i] = keys[i];
			new_values[i] = values[i];
		}

		delete[] keys;
		delete[] values;

		keys = new_keys;
		values = new_values;

		size--;
	}

public:
	FlatMap() {
		size = 0;
		keys = new string[size];
		values = new string[size];
	}

	FlatMap(const FlatMap& other_map) {
		size = other_map.size;
		keys = other_map.keys;
		values = other_map.values;
	}

	~FlatMap() {
		delete[] keys;
		delete[] values;
	}

	FlatMap& FlatMap::operator=(const FlatMap& n) {
		if (this == &n) {
			return *this;
		}
		delete[] keys;
		delete[] values;
		keys = new string[n.size];
		values = new string[n.size];

		for (int i = 0; i < n.size; i++) {
			keys[i] = n.keys[i];
			values[i] = n.values[i];
		}

		size = n.size;
	}
};

int main() {
 
    return 0;
}
