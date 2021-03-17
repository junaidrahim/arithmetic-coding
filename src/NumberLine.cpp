//
// Created by junaid on 17/03/21.
//

#include "../include/NumberLine.h"

#define NO_RESCALE 'N'


// Constructor
NumberLine::NumberLine(std::unordered_map<char, double> &probabilities) {
	std::for_each(probabilities.begin(), probabilities.end(), [&](auto &p) { this->sorted_probabilities.push_back(p); });

	std::sort(this->sorted_probabilities.begin(), this->sorted_probabilities.end(), [](auto p1, auto p2) { return p1.second > p2.second; });

	double total = 0;
	for (auto &x : this->sorted_probabilities) {
		total += x.second;
		this->line.insert(std::pair<double, char>{total, x.first});
	}

	this->lower_limit = 0;
	this->upper_limit = total;
}


// Search for character in the line and return upper and lower limits
std::pair<double, double> NumberLine::search_line(char c) {
	// search for c in this->line
	double ll = this->lower_limit;
	double ul;

	for (auto &x : this->line) {
		ul = x.first;

		if (c == x.second) break;

		ll = ul;
	}

	return std::pair<double, double>{ll, ul};
}


// Search for lower limit in the line and return the corresponding character
char NumberLine::search_line(double ll) {
	char c = this->line.lower_bound(ll)->second;
	return c;
}


// Encode 5 ASCII characters to 8 bits
uint8_t NumberLine::process(std::array<char, 5> &word) {
	std::string tag_bit_string;

	for (char c : word) {
		if (!c) break;

		auto limits = this->search_line(c);
		this->lower_limit = limits.first;
		this->upper_limit = limits.second;

		auto rescaled_limits = this->rescale(this->lower_limit, this->upper_limit);
		while (rescaled_limits.bit != NO_RESCALE) {
			tag_bit_string.push_back(rescaled_limits.bit);

			this->lower_limit = rescaled_limits.limits.first;
			this->upper_limit = rescaled_limits.limits.second;

			rescaled_limits = NumberLine::rescale(this->lower_limit, this->upper_limit);
		}

		this->line.clear();

		double d = this->upper_limit - this->lower_limit;
		double total = this->lower_limit;

		for (auto &x : this->sorted_probabilities) {
			total += d * x.second;
			this->line.insert(std::pair<double, char>{total, x.first});
		}
	}

	tag_bit_string.push_back('1');
	std::cout << "Tag String: " << tag_bit_string << std::endl;

	uint8_t tag = 0;
	for (int i = 0; i < 8; i++) {
		try {
			if (tag_bit_string.at(i)) {
				tag = (tag << 1) | tag_bit_string[i] - '0';
			}
		} catch (std::exception const &e) {
			tag = (tag << 1);
		}
	}

	return tag;
}


// Decode an 8 bit word to 5 ASCII Characters
std::array<char, 5> NumberLine::process(uint8_t &word) {
	std::array<char, 5> words{};
	uint8_t curr_word = word;

	for (int i = 0; i < 5; i++) {
		for (auto &x : this->line)
			std::cout << x.first << ' ' << x.second << std::endl;

		double p = bitsToDouble(curr_word);
		char w = this->search_line(p);
		words[i] = w;

		std::cout << "Tag: " << std::bitset<8>{curr_word} << ' ' << p << std::endl;

		auto limits = this->search_line(w);
		this->lower_limit = limits.first;
		this->upper_limit = limits.second;

		auto rescaled_limits = NumberLine::rescale(this->lower_limit, this->upper_limit);

		while(rescaled_limits.bit != NO_RESCALE) {
			curr_word = (curr_word << 1) | rescaled_limits.bit - '0';
			this->lower_limit = rescaled_limits.limits.first;
			this->upper_limit = rescaled_limits.limits.second;

			rescaled_limits = NumberLine::rescale(this->lower_limit, this->upper_limit);
		}

		this->line.clear();

		double d = this->upper_limit - this->lower_limit;
		double total = this->lower_limit;

		for (auto &x : this->sorted_probabilities) {
			total += d * x.second;
			this->line.insert(std::pair<double, char>{total, x.first});
		}
	}

	return words;
}


// Rescale the passed limits
NumberLine::rescale_output NumberLine::rescale(double ll, double ul) {
	std::pair<double, double> limits;
	char bit;
	if (ll >= 0.5 && ul >= 0.5) {
		limits = std::make_pair(2 * (ll - 0.5), 2 * (ul - 0.5));
		bit = '1';
		return NumberLine::rescale_output(limits, bit);
	} else if (ll < 0.5 && ul < 0.5) {
		limits = std::make_pair(2 * ll, 2 * ul);
		bit = '0';
		return NumberLine::rescale_output(limits, bit);
	}

	limits = std::make_pair(ll, ul);
	bit = NO_RESCALE;
	return NumberLine::rescale_output(limits, bit);
}


// Convert the bits to a float of form 0.... The supplied bits make up the decimal part
double NumberLine::bitsToDouble(uint8_t bits) {
	std::bitset<8> b(bits);
	double d = 0;

	for (int i = 0; i < 8; i++) {
		if (b[i]) {
			d += pow(2, -(i + 1));
		}
	}

	return d;
}
