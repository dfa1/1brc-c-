#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

template <typename T>
struct xmax {
  constexpr T operator()(const T& x, const T& y) { return std::max(x, y); }
};

template <typename T>
struct xmin {
  constexpr T operator()(const T& x, const T& y) { return std::min(x, y); }
};

int main() {
  std::ios::sync_with_stdio(false);

  std::ifstream infile("measurements.txt");
  std::string line;
  std::map<std::string, std::vector<float>> by_city;
  while (std::getline(infile, line)) {
    std::size_t semicolon = line.find_first_of(';');
    if (semicolon != std::string::npos) {
      const std::string city = line.substr(0, semicolon);
      const float temp = std::stof(line.substr(semicolon + 1));
      by_city[city].push_back(temp);
    }
  }
  for (const auto& [city, temps] : by_city) {
    const float min =
        std::reduce(temps.cbegin(), temps.cend(), 10000, xmin<float>());
    const float max =
        std::reduce(temps.cbegin(), temps.cend(), -10000, xmax<float>());
    const float avg = std::reduce(temps.cbegin(), temps.cend()) / temps.size();
    std::cout << city << ";" << min << ";" << max << ";" << avg << "\n";
  }
}
