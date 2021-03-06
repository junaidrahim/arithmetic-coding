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
#include <algorithm>
#include "common.hpp"

class FileReader {
public:
	static FileData<char> read_ascii_file(const std::string &filename);
};
