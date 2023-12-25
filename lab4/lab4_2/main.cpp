#include "CSVParses.h"

int main() {

    std::string file1 = "../../../file1.csv";
    std::string file2 = "../../../file2.csv";
    std::string error_file1 = "../../../error_file1.csv";
    std::string error_file2 = "../../../error_file2.docx";

    std::ifstream csv_stream(file1);

    if (!csv_stream) {
        std::cout << "Error opening file";
        return 1;
    }

    CsvParser<int, std::string, double> fparser(csv_stream, 0);
    CsvParser<int, std::string, double> parser(std::cin, 0);

    for (std::tuple<int, std::string, double>& rs : fparser) {
        std::cout << std::get<0>(rs) << ", " << std::get<1>(rs) << ", " << std::get<2>(rs) << "\n";
    }

    std::cout << "\n\n";

    for (std::tuple<int, std::string, double>& rs : parser) {
        std::cout << std::get<0>(rs) << ", " << std::get<1>(rs) << ", " << std::get<2>(rs) << "\n";
    }

    return 0;
}
