//
// Created by junaid on 25/02/21.
//

#include "../include/FileWriter.h"

void FileWriter::write_ascii_file(FileData<char> f, const std::string &file_path) {
	std::ofstream output_file(file_path, std::ios::out);
	output_file.write((const char *)&f.data[0], f.data.size());
	output_file.close();
}

void FileWriter::write_bin_file(FileData<uint16_t> f, const std::string &file_path) {
	std::ofstream output_file(file_path, std::ios::out | std::ios::binary);

	const uint8_t p_size = f.probabilities.size();
	const uint64_t d_size = f.data.size();

	char ch_arr[p_size];
	double prob_arr[p_size];
	uint16_t data_arr[d_size];

	int in = 0;
	for (auto &it : f.probabilities) {
		ch_arr[in] = it.first;
		prob_arr[in] = it.second;
		in++;
	}

	for (auto i = 0; i < d_size; i++) {
		data_arr[i] = f.data[i];
	}

	output_file.write((char *)(&p_size), sizeof(p_size));
	output_file.write((char *)(ch_arr), sizeof(ch_arr));
	output_file.write((char *)(prob_arr), sizeof(prob_arr));
	output_file.write((char *)(data_arr), sizeof(data_arr));
	output_file.close();
}