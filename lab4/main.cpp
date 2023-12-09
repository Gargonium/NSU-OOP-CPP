#include <iostream>

#include <tuple>

template<std::size_t index = 0, typename... Types>
typename std::enable_if<index == sizeof...(Types)>::type
printTuple(std::ostream&, const std::tuple<Types...>&) {

}

template<std::size_t index = 0, typename... Types>
typename std::enable_if<(index < sizeof...(Types))>::type
    printTuple(std::ostream& os, const std::tuple<Types...>& t) {
    if (index != 0) {
        os << ", ";
    }
    os << std::get<index>(t);
    printTuple<index + 1>(os, t);
}

template<typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& t) {
    printTuple(os, t);
    return os;
}

int main() {
    std::tuple<int, double, std::string> t(10, 3.14, "Hello");
    std::cout << t << std::endl;
    return 0;
}