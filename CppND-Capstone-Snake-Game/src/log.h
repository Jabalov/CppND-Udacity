#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
using namespace std;

class Log
{
public:
    Log();
    void WriteToLogFile(string name, int score, int siz);
    void OpenFile();
    void CloseFile();

private:
    fstream log_file;
};

#endif