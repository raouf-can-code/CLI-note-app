#include "json.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>

using str = std::string;

namespace math {

double calc(str opp) {
  opp.erase(remove_if(opp.begin(), opp.end(), isspace), opp.end());
  str num1;
  str num2;
  char oppm;
  double resault;
  int size = opp.size();
  for (int i = 0; i < size - 1; i++) {
    if (opp[i] == '+' || opp[i] == '-' || opp[i] == '/' || opp[i] == '*') {
      oppm = opp[i];
      num1 = opp.substr(0, i);
      num2 = opp.substr(i + 1, size - i);
      break;
    }
  }
  switch (oppm) {
  case '+':
    resault = std::stod(num1) + std::stod(num2);
    break;
  case '-':
    resault = std::stod(num1) - std::stod(num2);
    break;
  case '/':
    resault = std::stod(num1) / std::stod(num2);
    break;
  case '*':
    resault = std::stod(num1) * std::stod(num2);
    break;
  default:
    std::cout << "enter a valid operation\n";
    break;
  }
  return resault;
}

} // namespace math

namespace json {
nlohmann::json getJson(str fileName) {
  std::ifstream iFile(fileName);
  if (!iFile) {
    std::cout << "failed to open this file\n";
  }
  nlohmann::json dataJson;
  iFile >> dataJson;
  iFile.close();
  return dataJson;
}

void writeJson(str fileName, nlohmann::json jsonEl) {
  std::ofstream oFile(fileName);
  if (!oFile) {
    std::cout << "operation failed\n";
  }
  oFile << std::setw(4) << jsonEl << std::endl;
  oFile.close();
}

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate);
    return file.tellg() == 0;
}
} // namespace json
