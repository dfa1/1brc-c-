#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
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
	std::cout << "got " << by_city.size() << std::endl;
	for(const auto& [city, temps] : by_city) {
		float max = *std::max_element(temps.cbegin(), temps.cend());
		float min = *std::min_element(temps.cbegin(), temps.cend());
		std::cout << city  << "[" << min << ".." << max  << "]\n";
	}
	return 0;
}
