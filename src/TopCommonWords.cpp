# include "TopCommonWords.h"
# include <string>
# include <algorithm>
# include <ranges>
# include <vector>
# include <map>
#include <fstream>
#include <cctype>
#include <iostream>

const std::string SPECIAL = "\\,.:;\"|!@#$%^&*()_+-=[]{}<>?/~`'";

std::string lstrip(const std::string& str, const std::string& to_remove) {
    auto it = std::ranges::find_if(
      str,
        [&](char c) {
            return to_remove.find(c) == std::string::npos;
        }
    );

    return std::string(it, str.end());
}


    std::string rstrip(const std::string& str, const std::string& to_remove){
    auto result = str
    |std::views::reverse
    |std::ranges::views::drop_while([&](char c){
    return to_remove.find(c) != std::string::npos; }
    )
    |std::views::reverse
    |std::ranges::to<std::string>();

    return result;

    }

    std::string lower_str(std::string str) {
    std::ranges::transform(str, str.begin(), [](unsigned char c) {
      return std::tolower(c);
        });

    return str;
    }

    std::vector< std::string > readFile(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::string>read;

        std::string word;
        while(file >> word){
            read.push_back(word);
        }
        return read;
    }

    bool shouldIgnore(const std::string& word) {
        return word == "a" ||
               word == "an" ||
               word == "and" ||
               word == "in" ||
               word == "is" ||
               word == "it" ||
               word == "the";
    }


    std::vector< std::string > exclude(std::vector< std::string >& read){
        std::vector<std::string> clean;

        for (auto itr = read.begin() ; itr != read.end(); ++itr) {
            auto convertedWord = lower_str(read(*itr));
            auto convertedWord2 = rstrip(convertedWord,SPECIAL);
            auto convertedWord3 = lstrip(convertedWord2,SPECIAL);

            if (!convertedWord.empty() && !shouldIgnore(convertedWord)) {
                clean.push_back(convertedWord3);
            }
        }
    }


    std::map<std::string, int > countOcurr(std::vector<std::string> fileWords) {
        std::map<std::string, int> sortedValues;
        for (const std::string& word : fileWords) {
            sortedValues[word]++;
        }

        return sortedValues;

    }

void printFormat(const std::vector<std::pair<std::string, int>>& vec, int N) {
    int rank = 1;
    int i = 0;

    while (i < (int)vec.size() && rank <= N) {
        int currentCount = vec[i].second;

        std::vector<std::string> group;
        while (i < (int)vec.size() && vec[i].second == currentCount) {
            group.push_back(vec[i].first);
            i++;
        }


        std::cout << rank << ".) These words appeared "
                  << currentCount << " times: {";

        for (int j = 0; j < (int)group.size(); j++) {
            std::cout << group[j];
            if (j != (int)group.size() - 1) {
                std::cout << ", ";
            }
        }

        std::cout << "}" << std::endl;

        rank++;
    }
}

std::map<int, std::vector<std::string>, std::greater<int>>
groupByCount(const std::map<std::string, int>& counts) {

    std::map<int, std::vector<std::string>, std::greater<int>> grouped;

    for (const auto& [word, count] : counts) {
        grouped[count].push_back(word);
    }
    
    for (auto& [count, words] : grouped) {
        std::sort(words.begin(), words.end());
    }

    return grouped;
}