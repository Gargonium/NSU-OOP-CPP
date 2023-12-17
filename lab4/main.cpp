#include <iostream>
#include <tuple>
#include <utility>


/* C ограничением С++11 */
template<std::size_t index = 0, typename... Types>
typename std::enable_if<index == sizeof...(Types)>::type
printTuple11(std::ostream&, const std::tuple<Types...>&) {

}

template<std::size_t index = 0, typename... Types>
typename std::enable_if<(index < sizeof...(Types))>::type
printTuple11(std::ostream& os, const std::tuple<Types...>& t) {
    if (index != 0) {
        os << ", ";
    }
    os << std::get<index>(t);
    printTuple11<index + 1>(os, t);
}

/* Без ограничения */
/* Используя constexpr */
template<std::size_t Index = 0, typename... Types>
std::ostream& printTupleConstExpr(std::ostream& os, const std::tuple<Types...>& t) {
    if constexpr (Index < sizeof...(Types)) {
        if (Index != 0)
            os << ", ";
        os << std::get<Index>(t);
        printTupleConstExpr<Index + 1>(os, t);
    }
    return os;
}

/* Используя fold expressions */
template<typename... Types, std::size_t... Indices>
void printTupleFold(std::ostream& os, const std::tuple<Types...>& t, std::index_sequence<Indices...>) {
    ((os << (Indices == 0 ? "" : ", ") << std::get<Indices>(t)), ...);
}


/* Перегрузка оператора << */
template<typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& t) {
    printTupleFold(os, t, std::make_index_sequence<sizeof... (Types)>());
    return os;
}

int main() {
    std::tuple<int, double, std::string> t(10, 3.14, "Hello");
    std::cout << t << std::endl;
    return 0;
}