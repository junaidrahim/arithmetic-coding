//
// Created by junaid on 25/02/21.
//

#pragma once

#include <fstream>
#include <string>

#include "FileData.hpp"

class FileReader {
public:
	static FileData<char> read_ascii_file(const std::string &filename);
};
