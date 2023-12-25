#include <iostream>
#include <stdbool.h>
#include <string>
#include "template_flatMap.h"

using namespace std;

int main() {
    FlatMap<std::string, std::string> car;

    FlatMap<int, double> fmid;

    car["brand"] = "toyota";
    car["model"] = "camry";
    car["engine_vol"] = "3.5";
    car["power"] = "249 h. p.";
    car["price"] = "2 mil rub";

    fmid[1] = 3.45;
    fmid[2] = 4.56;
    fmid[3] = 5.23;

    for (auto it = car.begin(); it != car.end(); ++it) {
        std::cout << it->key << ": " << it->value << "\n";
    }
    std::cout << "\n";

    for (auto it = fmid.begin(); it != fmid.end(); ++it) {
        std::cout << it->key << ": " << it->value << "\n";
    }
}
