#pragma once

#include <algorithm>
#include <array>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <bitset>
#include <cmath>

struct NumberLine {
	struct rescale_output {
		std::pair<double, double> limits;
		char bit;
		rescale_output(std::pair<double, double> &l, char &b) : limits(l), bit(b) {}
	};

	std::vector<std::pair<char, double>> sorted_probabilities;
	std::map<double, char> line;

	double lower_limit;
	double upper_limit;

	NumberLine(std::unordered_map<char, double> &probabilities);
	std::pair<double, double> search_line(char c);
	char search_line(double ll);

	uint8_t process(std::array<char, 5> &word);
	std::array<char, 5> process(uint8_t &word);

	static rescale_output rescale(double ll, double ul);
	static double bitsToDouble(uint8_t bits);
};