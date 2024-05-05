#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <numeric>
#include <string>
#include <vector>

#include "fast_float.h"

inline float parse_float(const char *start, const char *end) {
  float result;
  fast_float::from_chars(start, end, result, fast_float::chars_format::fixed);
  // TODO: check for errors if (result.ec != std::errc())
  return result;
}

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
  for (const auto &[city, temps] : by_city) {
    // it is ok to use * without checking as iterator is scanning over city with
    // at least 1 value
    const float min = *std::min_element(temps.cbegin(), temps.cend());
    const float max = *std::max_element(temps.cbegin(), temps.cend());
    const float avg = std::reduce(temps.cbegin(), temps.cend()) / temps.size();
    std::cout << city << ";" << min << ";" << max << ";" << avg << "\n";
  }
}
