#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
#include <stdexcept>
#include <cstring>
#include <string>

template <typename... Args>
class CsvParser {
public:
    CsvParser(std::istream& stream, int skipLines) : stream(stream), skipLines(skipLines) {}

    class Iterator {
    public:
        Iterator(std::istream& stream, int skipLines, bool isBegin) 
            : stream(stream)
            , skipLines(skipLines)
            , isBegin(isBegin)
            , Delim(';') {

            for (int i = 0; i < skipLines; ++i) {
                std::string line;
                std::getline(stream, line);
            }
            if (isBegin) {
                operator++();
            }
        }

        bool operator!=(const Iterator& other) const {
            return !eof;
        }

        std::tuple<Args...> operator*() const {
            return args;
        }

        const Iterator& operator++() {
            std::string line;
            if (std::getline(stream, line)) {
                std::stringstream ss(line);
                parseLine(ss, std::index_sequence_for<Args...>());
            }
            else {
                eof = true;
            }
            return *this;
        }

    private:
        bool isBegin;
        std::istream& stream;
        int skipLines;
        bool eof = false;
        std::tuple<Args...> args;
        char Delim;

        template<std::size_t I>
        void parseField(std::stringstream& ss) {
            if constexpr (std::is_same_v<std::tuple_element_t<I, std::tuple<Args...>>, int>) {
                std::string fieldStr;
                std::getline(ss, fieldStr, Delim);
                int field = std::stoi(fieldStr);
                std::get<I>(args) = field;
            }
            else if constexpr (std::is_same_v<std::tuple_element_t<I, std::tuple<Args...>>, double>) {
                std::string fieldStr;
                std::getline(ss, fieldStr, Delim);
                double field = std::stod(fieldStr);
                std::get<I>(args) = field;
            }
            else if constexpr (std::is_same_v<std::tuple_element_t<I, std::tuple<Args...>>, std::string>) {
                std::string field;
                std::getline(ss, field, Delim);
                std::get<I>(args) = field;
            }
            else {
                throw std::invalid_argument("Unsupported field type");
            }
        }

        template<std::size_t... Is>
        void parseLine(std::stringstream& ss, std::index_sequence<Is...>) {
            (parseField<Is>(ss), ...);
        }
    };

    Iterator begin() {
        return Iterator(stream, skipLines, true);
    }

    Iterator end() {
        return Iterator(stream, skipLines, false);
    }

private:
    std::istream& stream;
    int skipLines;
};