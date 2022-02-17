// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "options_parser.h"
#include <filesystem>

int main(int argv, char* argc[]) {
    command_line_options_t command_line_options{argv, argc};

    bool soft = command_line_options.get_S_link();
    bool hard = command_line_options.get_H_link();
    std::vector<std::string> filenames = command_line_options.get_filenames();

    if(!(soft||hard)){
        std::cerr<<"No link mode specified"<<std::endl;
        return -1;
    }
    if(filenames.size() != 2){
        std::cerr<<"Invalid number of file paths, exactly 2 are required"<<std::endl;
        return -1;
    }
    if (std::filesystem::exists(filenames[1])) {
        throw std::invalid_argument("File " + filenames[1]+ " already exists!");
    }
    //Create link
    if(soft){
        std::filesystem::create_symlink(filenames[0],filenames[1]);
    }
    if(hard){
        if (!std::filesystem::exists(filenames[0])) {
            throw std::invalid_argument("File " + filenames[0]+ " not found!");
        }
        std::filesystem::create_hard_link(filenames[0],filenames[1]);
    }
    return 0;

}
