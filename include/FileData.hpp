#pragma once

#include <unordered_map>
#include <vector>

template <typename T> struct FileData {
	std::unordered_map<char, double> probabilities;
	std::vector<T> data;

	void set_probabilities(std::string &text);
	void set_data(std::string &text);
	void set_probabilities(std::unordered_map<char, double> &p);
	void set_data(std::vector<T> &d);
};

template <typename T> void FileData<T>::set_data(std::string &text) {
	for (char c : text) {
		this->data.push_back(c);
	}
}

template <typename T> void FileData<T>::set_probabilities(std::string &text) {

	std::unordered_map<char, int> M;

	for (int i = 0; text[i]; i++) {
		if (M.find(text[i]) == M.end()) {
			M.insert(std::make_pair(text[i], 1));
		} else {
			M[text[i]]++;
		}
	}

	for (auto &it : M) {
		double pr = double(it.second) / double(text.length());
		this->probabilities.insert(std::make_pair(it.first, pr));
	}
}

template <typename T> void FileData<T>::set_probabilities(std::unordered_map<char, double> &p) {
	this->probabilities = p;
}

template <typename T> void FileData<T>::set_data(std::vector<T> &d) { this->data = d; }

