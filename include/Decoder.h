//
// Created by junaid on 25/02/21.
//

#pragma once
#include "FileData.hpp"

class Decoder {
public:
	static FileData<char> decode(FileData<uint16_t> f);
};

