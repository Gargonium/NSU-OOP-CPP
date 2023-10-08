#include <iostream>
#include <stdbool.h>
#include <string.h>
#include "class.h"

using namespace std;

int main() {
    FlatMap car;

    car["brand"] = "toyota";
    car["model"] = "camry";
    car["engine_vol"] = "3.5";
    car["power"] = "249";
    car["price"] = "2 mil rub";

    cout << "Price: " << car["price"] << endl;

    cout << "Begin: " << car.begin() << endl;

    cout << "Find model: " << car.find("model") << endl;

    cout << 3 / 2 << endl;
}
