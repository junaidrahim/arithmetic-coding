//
// Created by junaid on 25/02/21.
//

#include "../include/Decoder.h"
#include "../include/NumberLine.h"

#include <iostream>

FileData<char> Decoder::decode(FileData<uint16_t> f) {
	FileData<char> decompressed_text;
	std::string bitstring;

	for(uint16_t x: f.data) {
		std::bitset<16> bits(x);

		for(int i=15; i>=0; i--){
			if(bits[i])
				bitstring.push_back('1');
			else
				bitstring.push_back('0');
		}
	}

	NumberLine nl(f.probabilities);
	std::vector<char> x = nl.process(bitstring);

	for(char c: x)
		decompressed_text.data.push_back(c);

	return decompressed_text;
}