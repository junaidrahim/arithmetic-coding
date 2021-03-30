//
// Created by junaid on 25/02/21.
//

#pragma once
#include "FileData.hpp"

class Encoder {
public:
    static FileData<uint16_t> encode(FileData<char> f);
};
