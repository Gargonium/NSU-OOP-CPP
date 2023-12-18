#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>

template<typename... Args>
class CsvParser {
public:
    CsvParser(std::ifstream& stream, int skip_lines) : fileStream(stream), skipLines(skip_lines) {}

    class Iterator : public std::iterator<std::input_iterator_tag, std::tuple<Args...>> {
    public:
        explicit Iterator(std::ifstream& stream, int skip_lines) : fileStream(stream), skipLines(skip_lines) {
            skipHeader();
            readRow();
        }

        Iterator& operator++() {
            if (fileStream.eof()) {
                currentRow = std::make_tuple(Args{}...);
                return *this;
            }
            readRow();
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return &fileStream == &other.fileStream && fileStream.eof() && other.fileStream.eof();
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        std::tuple<Args...> operator*() {
            return currentRow;
        }

    private:
        std::ifstream& fileStream;
        int skipLines;
        std::tuple<Args...> currentRow;

        void skipHeader() {
            std::string line;
            for (int i = 0; i < skipLines; ++i) {
                std::getline(fileStream, line);
            }
        }

        template<typename T>
        void parseField(const std::string& field, T& value) {
            std::istringstream iss(field);
            iss >> value;
        }

        template<typename T>
        void readValue(std::istringstream& ss, T& value) {
            std::string token;
            std::getline(ss, token, ';');
            parseField(token, value);
        }

        template<std::size_t Index = 0>
        typename std::enable_if<Index == sizeof...(Args)>::type readRowFields(std::istringstream& ss, std::tuple<Args...>& row) {}

        template<std::size_t Index = 0>
        typename std::enable_if < Index < sizeof...(Args)>::type readRowFields(std::istringstream& ss, std::tuple<Args...>& row) {
            readValue(ss, std::get<Index>(row));
            readRowFields<Index + 1>(ss, row);
        }

        void readRow() {
            std::string line;
            if (std::getline(fileStream, line)) {
                std::istringstream ss(line);
                readRowFields(ss, currentRow);
            }
        }
    };

    Iterator begin() {
        return Iterator(fileStream, skipLines);
    }

    Iterator end() {
        return Iterator(fileStream, skipLines);
    }

private:
    std::ifstream& fileStream;
    int skipLines;
};

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
    std::ifstream csv_stream("test1.csv");
    if (!csv_stream.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    CsvParser<int, std::string, double> parser(csv_stream, 0);
    for (std::tuple<int, std::string, double> rs : parser) {
        std::cout << rs << std::endl;
    }   

    return 0;
}
