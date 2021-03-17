//
// Created by junaid on 25/02/21.
//

#include "../include/Encoder.h"
#include "../include/NumberLine.h"

#include <vector>


FileData<uint8_t> Encoder::encode(FileData<char> f) {
	std::vector<uint8_t> codewords;

	for (auto itr = f.data.begin(); itr < f.data.end(); itr += 5) {
		std::array<char, 5> char_window{};
		for (int i = 0; i < 5; i++) {
			if(itr + i < f.data.end()){
				char_window[i] = *(itr + i);
			} else break;
		}

		NumberLine nl(f.probabilities);
		codewords.push_back(nl.process(char_window));
	}

	FileData<uint8_t> encoded;
	encoded.set_data(codewords);
	encoded.set_probabilities(f.probabilities);

	return encoded;
}
