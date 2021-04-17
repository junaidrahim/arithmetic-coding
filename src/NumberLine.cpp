//
// Created by junaid on 17/03/21.
//

#include "../include/NumberLine.h"

#define NO_RESCALE 'N'

// Constructor
NumberLine::NumberLine(std::unordered_map<char, double> &probabilities, std::vector<char> &order) {
	std::for_each(order.begin(), order.end(), [&](char &c) { this->sorted_probabilities.emplace_back(std::make_pair(c, probabilities[c])); });

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
	if (c == 0) c = ',';
	return c;
}

// Encode 5 ASCII characters to a string
std::string NumberLine::process(std::array<char, 5> &words) {
	std::string tag_bit_string;

	for (char c : words) {
		if (!c) break;

		auto limits = this->search_line(c);
		this->lower_limit = limits.first;
		this->upper_limit = limits.second;

		auto rescaled_limits = NumberLine::rescale(this->lower_limit, this->upper_limit);
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

	tag_bit_string.append("1000000000000000");
	return tag_bit_string;
}

// Decode an 16 bit word to 5 ASCII Characters
std::vector<char> NumberLine::process(std::string &bitstring) {
	std::vector<char> decompressed_text;
	std::string::iterator bitstring_itr = bitstring.begin();
	uint16_t curr_word = NumberLine::bitstringToInt(bitstring_itr);

	while (bitstring_itr < bitstring.end()) {
		for (int i = 0; i < 5; i++) {
			double p = bitsToDouble(curr_word);

			char w = this->search_line(p);
			decompressed_text.push_back(w);

			auto limits = this->search_line(w);
			this->lower_limit = limits.first;
			this->upper_limit = limits.second;

			auto rescaled_limits = NumberLine::rescale(this->lower_limit, this->upper_limit);

			while (rescaled_limits.bit != NO_RESCALE) {
				curr_word = NumberLine::bitstringToInt(++bitstring_itr);

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

		bitstring_itr += 16;
		curr_word = NumberLine::bitstringToInt(bitstring_itr);

		this->line.clear();

		double total = 0;
		for (auto &x : this->sorted_probabilities) {
			total += x.second;
			this->line.insert(std::pair<double, char>{total, x.first});
		}

		this->lower_limit = 0;
		this->upper_limit = total;
	}

	return decompressed_text;
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
double NumberLine::bitsToDouble(uint16_t bits) {
	std::bitset<16> b(bits);
	double d = 0;

	for (int i = 0; i < 16; i++) {
		if (b[15 - i]) {
			d += pow(2, -(i + 1));
		}
	}

	return d;
}

uint16_t NumberLine::bitstringToInt(std::string::iterator i) {
	uint16_t val;

	for (auto x = i; x < i + 16; x++) {
		val = (val << 1) | *(x) - '0';
	}

	return val;
}
