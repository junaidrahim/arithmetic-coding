//
// Created by junaid on 25/02/21.
//

#pragma once

#include <fstream>
#include <iostream>
#include <limits.h>
#include <string>
#include <unordered_map>
#include <vector>

//template <typename T> struct FileData {
//	std::unordered_map<char, double> probabilities;
//	std::vector<T> data;
//
//	void set_probabilities(std::string text);
//	void set_data(std::string text);
//	void set_probabilities(std::vector<char> c, std::vector<double> p);
//	void set_data(std::vector<T> d)
//};

class FileReader {
public:
	void read_ascii_file(const std::string &filename) {
		std::ifstream source;
		source.open(filename);
		std::unordered_map<char, int> M;
		std::string line, lines;
		while (std::getline(source, line)) {
			lines.append(line);
		}
		for (int i = 0; lines[i]; i++) {
			if (M.find(lines[i]) == M.end()) {
				M.insert(std::make_pair(lines[i], 1));
			} else {
				M[lines[i]]++;
			}
		}
		for (auto& it : M) {
			std::cout << it.first << ' ' << it.second << '\n';
		}
	}
};
