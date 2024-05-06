#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "fast_float.h"

inline float parse_float(const char *start, const char *end) {
  float result;
  fast_float::from_chars(start, end, result, fast_float::chars_format::fixed);
  // TODO: check for errors if (result.ec != std::errc())
  return result;
}

class Temperature {
  float min_ = 9999;
  float max_ = -9999;
  float sum_ = 0;
  int count_ = 0;

 public:
  void merge(const float value) {
    min_ = std::min(value, min_);
    max_ = std::max(value, max_);
    sum_ += value;
    count_ += 1;
  }

  float min() const { return min_; }
  float max() const { return max_; }
  float avg() const { return sum_ / count_; }
};

int main() {
  std::ios::sync_with_stdio(false);

  std::ifstream infile("measurements.txt");
  std::string line;
  std::unordered_map<std::string, Temperature> by_city;
  while (std::getline(infile, line)) {
    const std::size_t semicolon = line.find_first_of(';');
    if (semicolon != std::string::npos) {
      const std::string city = line.substr(0, semicolon);
      const float value =
          parse_float(line.data() + semicolon + 1, line.data() + line.size());
      by_city[city].merge(value);
    }
  }
  std::map<std::string, Temperature> sorted_by_city;
  for (const auto &[city, temperature] : by_city) {
    sorted_by_city[city] = temperature;
  }
  for (const auto &[city, temperature] : sorted_by_city) {
    std::cout << city << ";" << temperature.min() << ";" << temperature.max()
              << ";" << temperature.avg() << "\n";
  }
}
