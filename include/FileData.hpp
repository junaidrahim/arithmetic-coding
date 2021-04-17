#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

template <typename T> struct FileData {
	std::unordered_map<char, double> probabilities;
	std::vector<char> order;
	std::vector<T> data;

	void set_probabilities(std::string &text);
	void set_data(std::string &text);
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

	std::vector<std::pair<char, double>> sorted_probabilities;

	for (auto &it : M) {
		double pr = double(it.second) / double(text.length());
		sorted_probabilities.push_back(std::make_pair(it.first, pr));
	}

	std::sort(sorted_probabilities.begin(), sorted_probabilities.end(), [](auto p1, auto p2) { return p1.second > p2.second; });

	this->probabilities.clear();
	this->order.clear();
	for (auto &it : sorted_probabilities) {
		this->order.push_back(it.first);
		this->probabilities.insert(it);
	}
}

template <typename T> void FileData<T>::set_data(std::vector<T> &d) { this->data = d; }
