//
// Created by junaid on 25/02/21.
//

#include"../include/Encoder.h"
#include "../include/common.h"
#include <iostream>
#include <vector>
#include <algorithm>

NumberLine::NumberLine(std::unordered_map<char, double> &probabilities) {
	std::vector<std::pair<char, double>> sorted_prob;

	std::for_each(probabilities.begin(), probabilities.end(), [&](auto& p){
		sorted_prob.push_back(p);
	});

	std::sort(sorted_prob.begin(), sorted_prob.end(), [](auto p1, auto p2){
		return p1.second < p2.second;
	});

	std::for_each(sorted_prob.begin(), sorted_prob.end(), [&](auto p){
		this->probabilities.insert(p);
	});

	uint16_t total = 0;
    double cumulative_total = 0;

	for (auto &x : probabilities) {
        this->cumm_probabilities[x.first] = cumulative_total;
        cumulative_total += x.second;
		total += x.second * 65535;
    	this->line.insert(std::pair<uint16_t, char>{total, x.first});
	}

	this->lower_limit = 0;
	this->upper_limit = total;

	std::cout << "Probabilities: \n";
	for(auto& x: this->probabilities) {
		std::cout << x.first << ' ' << x.second << '\n';
	}

	std::cout << "Cumulative Probabilities: \n";
	for(auto& x: this->cumm_probabilities) {
		std::cout << x.first << ' ' << x.second << '\n';
	}

	std::cout << "Line: \n";
	for(auto& x: this->line) {
		std::cout << x.first << ' ' << x.second << '\n';
	}
}

uint16_t NumberLine::process(std::array<char, 5> &word) {
	// First Number line is ready;
	char first = word[0];
    uint16_t d = 1;
	this->lower_limit = cumm_probabilities[first];


	// for(auto i=this->line.begin(); i<this->line.end(); i++) {

	// }

    /* by tathagata
    d=1; lower_limit=0; upper_limit=1;
    for(loops through the char in the 5char word selected){
        lower_limit += d * cumm_probability[ch];  //here cumm_probabitity and probability are in 0 to 1 range.
        upper_limit = lower_limit + d * probability[ch];
        d = upper_limit - lower_limit;
    }
    final coded word for 5char word selected = (upper_limit + lower_limit)/2 //upto as 
    */

}

FileData<uint16_t> Encoder::encode(FileData<char> f) {

}
