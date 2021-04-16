//
// Created by junaid on 25/02/21.
//

#include "../include/Encoder.h"
#include "../include/NumberLine.h"

#include <fstream>
#include <vector>

FileData<uint16_t> Encoder::encode(FileData<char> f) {
	std::string bitstring;
	std::vector<uint16_t> codewords;

	for (auto itr = f.data.begin(); itr < f.data.end(); itr += 5) {
		std::array<char, 5> char_window{};
		for (int i = 0; i < 5; i++) {
			if (itr + i < f.data.end()) {
				char_window[i] = *(itr + i);
			} else
				break;
		}

		NumberLine nl(f.probabilities);
		bitstring.append(nl.process(char_window));
	}

	const size_t s = 16 - (bitstring.size() % 16);
	for (size_t i = 0; i < s; i++)
		bitstring.push_back('0');

	uint16_t tag = 0;
	int count = 0;

	for (char c : bitstring) {
		if (count == 16) {
			codewords.push_back(tag);
			tag = 0;
			count = 0;
		}

		tag = (tag << 1) | c - '0';
		count += 1;
	}

	codewords.push_back(tag);

	FileData<uint16_t> encoded;
	encoded.set_data(codewords);
	encoded.set_probabilities(f.probabilities);

	std::ofstream op;
	op.open("../tests/encoder_output.txt");

	for (auto i : encoded.data) {
		op << i << std::endl;
	}

	return encoded;
}
