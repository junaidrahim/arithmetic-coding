//
// Created by junaid on 25/02/21.
//

#pragma once

#include <fstream>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>
#include <algorithm>
#include "common.hpp"

class FileWriter {
public :
    static void write_ascii_file(FileData<char> f, const std::string &file_path);
    static void write_bin_file(FileData<uint16_t> f, const std::string &file_path);

};
