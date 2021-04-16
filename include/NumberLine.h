#pragma once

#include <algorithm>
#include <array>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <bitset>
#include <cmath>
#include <string>

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

	std::string process(std::array<char, 5> &word);
	std::vector<char> process(std::string& bitstring);

	static rescale_output rescale(double ll, double ul);
	static double bitsToDouble(uint16_t bits);
	static uint16_t bitstringToInt(std::string::iterator i);
};