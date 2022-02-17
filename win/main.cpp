// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "options_parser.h"
#include "winbase.h"

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
    //Create link
    if(soft){
        CreateSymbolicLinkA(filenames[0].c_str(),filenames[1].c_str(),0);
    }
    if(hard){
        DWORD dwAttrib = GetFileAttributesA(filenames[0].c_str())
        if (dwAttrib == INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)){
            throw std::invalid_argument("File " + filenames[0]+ " not found!");
        }
        CreateHardLinkA(filenames[0].c_str(),filenames[1].c_str(),0);
    }
    return 0;

}
