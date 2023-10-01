#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//KVE - Key-Value Element

class FlatMap {
private:
	int size;
	struct KVE{
		string key;
		string value;
	};
	KVE* kve;
	int capacity;
	//Add _capacity	

	int KVEIndex(string key) {
		sort();
		bool flag = false;
		int l = 0; 
		int r = size;
		int mid = -1;

		while ((l <= r) && (flag != true)) {
			mid = (l + r) / 2; 

			if (kve[mid].key == key) {
				flag = true;
			}
			if (kve[mid].key > key) {
				r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}

		if (flag) {
			return mid;
		}
		else {
			return -1;
		}
	}

	void Аppend(string key, string value) {
		KVE* new_kve = new KVE[capacity];

		copy(kve, kve + size, new_kve);

		delete[] kve;

		new_kve[size + 1].key = key;
		new_kve[size + 1].value = value;

		kve = new_kve;

		size++;
		if (size == capacity) {
			recap();
		}
	}

	void ChangeValue(int kve_index, string value) {
		kve[kve_index].value = value;
	}

	void DelKVE(string key) {
		int kve_index = KVEIndex(key);
		if (kve_index == -1) {
			cout << "This key is not existed" << endl;
			return;
		}

		KVE* new_kve = new KVE[capacity];
		for (int i = 0; i < size; i++) {
			if (i == kve_index) {
				continue;
			}

			new_kve[i].key = kve[i].key;
			new_kve[i].value = kve[i].value;
		}

		delete[] kve;

		kve = new_kve;
		size--;
	}

	void sort() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size - 1; j++) {
				if (kve[j].key > kve[j + 1].key) {
					string k = kve[j].key; // создали дополнительную переменную
					string v = kve[j].value;
					kve[j].key = kve[j+1].key; // меняем местами
					kve[j].value = kve[j + 1].value;
					kve[j+1].key = k; // значения элементов
					kve[j + 1].value = v;
				}
			}
		}
	}

	void recap() {
		capacity *= 2;
		KVE* new_kve = new KVE[capacity];

		copy(kve, kve + size, new_kve);
		delete[] kve;
		kve = new_kve;
	}

public:
	FlatMap() {
		size = 0;
		capacity = 10;
		kve = new KVE[size];
	}

	FlatMap(const FlatMap& other_map) {
		size = other_map.size;
		kve = other_map.kve;
		capacity = other_map.capacity;
		copy(kve, kve + size, other_map.kve);
	}

	~FlatMap() {
		delete[] kve;
	}

	FlatMap& FlatMap::operator=(const FlatMap& other_map) {
		if (this == &other_map) {
			return *this;
		}
		delete[] kve;
		kve = new KVE[other_map.capacity];

		copy(kve, kve + size, other_map.kve);

		size = other_map.size;
		capacity = other_map.capacity;
	}

	string& FlatMap::operator[] (const string& key) {
		int kve_index = KVEIndex(key);
		if (kve_index == -1) {
			this->Аppend(key, "");
		}
		return kve[kve_index].value;
	}
};

int main() {

	FlatMap a;

	a["Hello"] = "World";

	cout << a["Hello"] << endl;

	return 0;
}
