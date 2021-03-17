//
// Created by junaid on 25/02/21.
//

#include "../include/Decoder.h"
#include "../include/NumberLine.h"

#include <iostream>

FileData<char> Decoder::decode(FileData<uint8_t> f) {
	FileData<char> decompressed_text;
	NumberLine nl(f.probabilities);

	auto x = nl.process(f.data[0]);

	for(char c: x)
		std::cout << c;

	std::cout << std::endl;

	return decompressed_text;
}