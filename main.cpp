#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "fast_float.h"

constexpr auto execution_policy = std::execution::par_unseq;

inline float parse_float(const char *start, const char *end) {
  float result;
  fast_float::from_chars(start, end, result, fast_float::chars_format::fixed);
  // TODO: check for errors if (result.ec != std::errc())
  return result;
}

struct Result {
  std::string city;
  float min;
  float max;
  float avg;

  bool operator<(const Result &that) { return this->city < that.city; }
};

int main() {
  std::ios::sync_with_stdio(false);

  std::ifstream infile("measurements.txt");
  std::string line;
  std::unordered_map<std::string, std::vector<float>> by_city;
  while (std::getline(infile, line)) {
    std::size_t semicolon = line.find_first_of(';');
    if (semicolon != std::string::npos) {
      const std::string city = line.substr(0, semicolon);
      const float temp =
          parse_float(line.data() + semicolon + 1, line.data() + line.size());

      by_city[city].push_back(temp);
    }
  }
  std::vector<Result> sorted_by_city;
  sorted_by_city.reserve(by_city.size());
  for (const auto &[city, temps] : by_city) {
    Result result;

    result.city = city;
    // it is ok to use * without checking as iterator is scanning over city with
    // at least 1 value
    result.min = *std::min_element(execution_policy, temps.cbegin(), temps.cend());
    result.max = *std::max_element(execution_policy, temps.cbegin(), temps.cend());
    result.avg = std::reduce(execution_policy, temps.cbegin(), temps.cend()) / temps.size();

    sorted_by_city.push_back(result);
  }

  std::sort(sorted_by_city.begin(), sorted_by_city.end());

  for (const Result &result : sorted_by_city) {
    std::cout << result.city << ";" << result.min << ";" << result.max << ";"
              << result.avg << "\n";
  }
}
