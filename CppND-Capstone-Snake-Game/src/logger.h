#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
using namespace std;

class Logger
{
public:
    Logger();
    void WriteToLogFile(int score, int sizes);
    void OpenFile();
    void CloseFile();

private:
    fstream file;
};

#endif