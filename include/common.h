#pragma once

#include <array>
#include <map>
#include <unordered_map>
#include <vector>

template <typename T> struct FileData {
	std::unordered_map<char, double> probabilities;
	std::vector<T> data;

	void set_probabilities(std::string text);
	void set_data(std::string text);
	void set_probabilities(std::vector<char> c, std::vector<double> p);
	void set_data(std::vector<T> d);
};

struct NumberLine {
    std::unordered_map<char, double> probabilities;
    std::unordered_map<char, double> cumm_probabilities;
	std::map<uint16_t, char> line; // 0 to 65535
	uint16_t lower_limit;
	uint16_t upper_limit;

	NumberLine(std::unordered_map<char, double>& probabilities);
	std::array<char, 5> process(const uint16_t codeword);
    uint16_t process(std::array<char, 5>& word);

};

