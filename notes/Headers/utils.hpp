#ifndef UTILS_HPP
#define UTILS_HPP
#include "json.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

using str = std::string;

namespace math {
double calc(str opp);
} // namespace math

namespace json {
nlohmann::json getJson(str fileName);
void writeJson(str fileName, nlohmann::json jsonEl);
bool isFileEmpty(const std::string& filename);
}

#endif // utils.hpp
