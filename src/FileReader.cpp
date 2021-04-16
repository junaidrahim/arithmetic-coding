//
// Created by junaid on 25/02/21.
//

#include "../include/FileReader.h"
#include <iostream>

FileData<char> FileReader::read_ascii_file(const std::string &filename) {
	std::ifstream source;
	source.open(filename);

	std::string line, lines;

	while (std::getline(source, line)) {
		lines.append(line);
		lines.push_back('\n');
	}

	FileData<char> fd;
	fd.set_data(lines);
	fd.set_probabilities(lines);
	return fd;
}

FileData<uint16_t> FileReader::read_bin_file(const std::string &filename) {
	uint8_t n;
	std::ifstream source;
	source.open(filename);
	source.read((char *)&n, sizeof n);

	char ch_arr[int(n)];
	double prob_arr[int(n)];

	source.read((char *)&ch_arr, int(n));
	source.read((char *)&prob_arr, sizeof prob_arr);

	std::unordered_map<char, double> prob;
	std::vector<uint16_t> data;

	for (auto i = 0; i < int(n); i++) {
		prob.insert({ch_arr[i], prob_arr[i]});
	}

	while (!source.eof()) {
		uint16_t temp;
		source.read((char *) &temp, sizeof temp);
		if (source.eof()) break;
		data.push_back(temp);
	}

	FileData<uint16_t> fd;
	fd.set_probabilities(prob);
	fd.set_data(data);

	std::ofstream op;
	op.open("../tests/reader_output.txt");

	for (auto i : fd.data) {
		op << i << std::endl;
	}
	return fd;
}