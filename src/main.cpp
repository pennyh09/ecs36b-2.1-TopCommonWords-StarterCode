#include <iostream>
# include "TopCommonWords.h"

int main(int argc, char** argv) {
    std::cout << "Usage: ./TopCommonWords path_to_file [num_words_to_find]" << std::endl;

    std::string filename = argv[1];

    int n = 10;
    if (argc == 3) {
        n = std::stoi(argv[2]);
    }

    auto words = readFile(filename);

    auto cleanedWords = exclude(words);

    auto counts = countOcurr(cleanedWords);

    auto grouped = groupByCount(counts);

    printFormat(grouped, n);

    return 0;
}
