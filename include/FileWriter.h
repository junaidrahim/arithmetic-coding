//
// Created by junaid on 25/02/21.
//

#pragma once

#include "common.hpp"

class FileWriter {
public :
    void write_ascii_file(FileData<char> f, std::string file_path);
    void write_bin_file(FileData<uint16_t> f, std::string file_path);

};
