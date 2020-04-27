#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::string;
using std::vector;

class System
{
public:
  Processor &Cpu();             // Done: See src/system.cpp
  vector<Process> &Processes(); // Done: See src/system.cpp
  float MemoryUtilization();    // Done: See src/system.cpp
  long UpTime();                // Done: See src/system.cpp
  int TotalProcesses();         // Done: See src/system.cpp
  int RunningProcesses();       // Done: See src/system.cpp
  string Kernel();              // Done: See src/system.cpp
  string OperatingSystem();     // Done: See src/system.cpp

  // Done: Define any necessary private members
private:
  Processor cpu_ = {};
  vector<Process> processes_ = {};
};

#endif