#include "logger.h"

#include <iostream>
#include <sstream>
using namespace std;

Logger::Logger()
{
    OpenFile();

    file.seekg(0, ios::end);

    if (file.tellg() == 0)
        file << "Score _ Size" << endl;

    CloseFile();
}

void Logger::WriteToLogFile(int score, int siz)
{
    OpenFile();

    file << "Player score: " << score << ", Snake size: " << siz << endl;

    CloseFile();
}

void Logger::OpenFile() { file.open("../logger_file/LOG.txt", fstream::in | fstream::out | fstream::app); }

void Logger::CloseFile() { file.close(); }