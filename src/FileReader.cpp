//
// Created by junaid on 25/02/21.
//

#include "../include/FileReader.h"


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
	// @Rohan Implement this
	return FileData<uint16_t>{};
}