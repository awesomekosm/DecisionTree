#include "ReadFile.h"



ReadFile::ReadFile()
{
}
std::string ReadFile::readFile(const char * fileName)
{
    std::string str;
    std::ifstream file(fileName);
    std::string returnFile;
    while (!file.eof()) {
        while (std::getline(file, str)) {
            returnFile.append(str);
        }
    }
    file.close();
    return returnFile;
}



ReadFile::~ReadFile()
{
}
