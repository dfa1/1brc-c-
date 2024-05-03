#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

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
	for(const auto& [city, temps] : by_city) {
                const float max = *std::max_element(temps.cbegin(), temps.cend());
                const float min = *std::min_element(temps.cbegin(), temps.cend());
		const float avg = std::reduce(temps.cbegin(), temps.cend()) / temps.size();
		std::cout << city  << ";" << min << ";" << max  << ";" << avg << "\n";
	}
}
