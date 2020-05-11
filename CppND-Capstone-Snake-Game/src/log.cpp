#include "log.h"

#include <iostream>
#include <sstream>
using namespace std;

Log::Log()
{
    OpenFile();

    log_file.seekg(0, ios::end);

    if (log_file.tellg() == 0)
        log_file << "Player-Score-Size" << endl;

    CloseFile();
}

void Log::WriteToLogFile(string name, int score, int siz)
{
    OpenFile();

    log_file << "Player name: " << name << ", Player score: " << score << " and snake size: " << siz << endl;

    CloseFile();
}

void Log::OpenFile() { log_file.open("../data/LOG_FILE.txt", fstream::in | fstream::out | fstream::app); }

void Log::CloseFile() { log_file.close(); }