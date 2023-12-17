#pragma once

#include <iostream>
#include <type_traits>

template <typename... Ts>
class MyTuple;

template <>
class MyTuple<> {
public:
    static constexpr size_t size() noexcept {
        return 0;
    }
};

template <typename T, typename... Ts>
class MyTuple<T, Ts...> {
private:
    T value_;
    MyTuple<Ts...> rest_;

public:
    MyTuple() = default;

    MyTuple(const T& value, const Ts&... values)
        : value_(value), rest_(values...) {}

    template <size_t Index>
    decltype(auto) get() const noexcept {
        if constexpr (Index == 0) {
            return value_;
        }
        else {
            return rest_.template get<Index - 1>();
        }
    }

    static constexpr size_t size() noexcept {
        return sizeof...(Ts) + 1; // +1 за счет T
    }
};

template <size_t Index, typename... Ts>
void printTupleElement(std::ostream& os, const MyTuple<Ts...>& tuple) {
    if constexpr (Index < sizeof...(Ts)) {
        os << tuple.template get<Index>();
        if constexpr (Index + 1 < sizeof...(Ts)) {
            os << ", ";
        }
        printTupleElement<Index + 1>(os, tuple);
    }
}

template <typename... Ts>
std::ostream& operator<<(std::ostream& os, const MyTuple<Ts...>& tuple) {
    os << "(";
    printTupleElement<0>(os, tuple);
    os << ")";
    return os;
}

