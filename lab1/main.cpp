#include <iostream>
#include <stdbool.h>
#include <string.h>
#include "flat_map_class.h"

using namespace std;

int main() {
    FlatMap car;

    car["brand"] = "toyota";
    car["model"] = "camry";
    car["engine_vol"] = "3.5";
    car["power"] = "249 h. p.";
    car["price"] = "2 mil rub";

    /*cout << "Price: " << car["price"] << endl;

    cout << "Begin: " << car.begin() << endl;

    cout << "Find model: " << car.find("model") << endl;

    cout << 3 / 2 << endl;*/

    for (auto it = car.begin(); it != car.end(); ++it) {
        std::cout << it->key << ": " << it->value << "\n";
    }
}
