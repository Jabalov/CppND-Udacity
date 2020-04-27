#ifndef PROCESS_H
#define PROCESS_H
#include "linux_parser.h"

#include <string>
#include <vector>
using std::string;
using std::vector;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process
{
public:
  Process(int process_id) : pid_(process_id)
  {
    cpu_ = LinuxParser::CPU_Usage(pid_);
    ram_ = LinuxParser::Ram(pid_);
  }

  int Pid();                              // Done: See src/process.cpp
  string User();                          // Done: See src/process.cpp
  string Command();                       // Done: See src/process.cpp
  float CpuUtilization();                 // Done: See src/process.cpp
  string Ram();                           // Done: See src/process.cpp
  long int UpTime();                      // Done: See src/process.cpp
  bool operator<(Process const &a) const; // Done: See src/process.cpp

  // Done: Declare any necessary private members
private:
  int pid_;
  float cpu_;
  string ram_;
};

#endif