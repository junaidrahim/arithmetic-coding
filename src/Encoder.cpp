//
// Created by junaid on 25/02/21.
//

#include "../include/Encoder.h"
#include "../include/common.h"
#include <iostream>
#include <vector>
#include <algorithm>

NumberLine::NumberLine(std::unordered_map<char, double> &probabilities) {
	this->probabilities = probabilities;

	uint16_t total = 0;
    double cumm_total = 0;

	for (auto &x : probabilities) {
        this->cumm_probabilities[x.first] = cumm_total;
        cumm_total += x.second;
		total += x.second * 65535;
    	this->line.insert(std::pair<uint16_t, char>{total, x.first});
	}

	this->lower_limit = 0;
	this->upper_limit = total;
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
        d = d*probability[ch]; 
    }
    final coded word for 5char word selected = lower_limit + d/2;
    */

}

FileData<uint16_t> Encoder::encode(FileData<char> f) {

}
