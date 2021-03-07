//
// Created by junaid on 25/02/21.
//

#include "../include/FileWriter.h"


void FileWriter::write_ascii_file(FileData<char> f, const std::string &file_path){
    std::ofstream output_file(file_path, std::ios::out);
    output_file.write((const char *)&f.data[0], f.data.size());
    output_file.close();
}

void FileWriter::write_bin_file(FileData<uint16_t> f, const std::string &file_path){
    //TODO
    return;
}