
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string>
#include <vector>
#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif
#include <fstream>
#include <regex>

std::string getCWD();
std::string loadFile(std::string path);
std::vector<std::string> stringSplit(std::string& input, std::string& regex);
std::vector<std::string> stringSplitByLine(std::string& input);


#endif
