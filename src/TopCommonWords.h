#ifndef TOPCOMMONWORDS_TOPCOMMONWORDS_H
#define TOPCOMMONWORDS_TOPCOMMONWORDS_H
# include <string>
# include <algorithm>
# include <ranges>
# include <vector>
# include <map>
#include <fstream>
#include <cctype>
#include <iostream>


std::vector< std::string > readFile(const std::string& filename);
bool shouldIgnore(const std::string& word);
std::vector< std::string > exclude(std::vector< std::string >& read);
std::map<std::string, int > countOcurr(std::vector<std::string> fileWords);
void printFormat(const std::vector<std::pair<std::string, int>>& vec, int N);
std::map<int, std::vector<std::string>, std::greater<int>> groupByCount(const std::map<std::string, int>& counts);
#endif //TOPCOMMONWORDS_TOPCOMMONWORDS_H
