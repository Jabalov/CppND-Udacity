#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

#define frequency sysconf(_SC_CLK_TCK)

using std::getline;
using std::ifstream;
using std::istringstream;
using std::stof;
using std::stoi;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
  string line, key, value;
  ifstream stream(kOSPath);
  if (stream.is_open())
  {
    while (getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "PRETTY_NAME")
        {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel()
{
  string os, version, kernel;
  string line;
  ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open())
  {
    getline(stream, line);
    istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids()
{
  vector<int> pids;
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
  while ((file = readdir(directory)) != nullptr)
  {
    // Is this a directory?
    if (file->d_type == DT_DIR)
    {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit))
      {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// return each process usage
float LinuxParser::CPU_Usage(int pid)
{
  float procces_Usage;

  long TotalTime = ActiveJiffies(pid);
  long process_upTime = UpTime(pid);

  procces_Usage = ((float)TotalTime / frequency) / process_upTime;
  return procces_Usage;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  float MemTotal, MemFree, Buffers, Cached;
  string line, key, value, t;
  ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open())
    while (getline(stream, line))
    {
      istringstream linestream(line);
      while (linestream >> key >> value >> t)
        if (key == "MemTotal:")
          MemTotal = stof(value);
        else if (key == "MemFree:")
          MemFree = stof(value);
        else if (key == "Buffers:")
          Buffers = stof(value);
        else if (key == "Cached:")
          Cached = stof(value);
    }

  return (MemTotal - (MemFree + Buffers + Cached)) / MemTotal;
}

// Done: Read and return the system uptime
long LinuxParser::UpTime()
{
  long uptime_system, uptime_idle;
  string line;

  ifstream stream(kProcDirectory + kUptimeFilename);

  if (stream.is_open())
  {
    getline(stream, line);
    istringstream linestream(line);
    linestream >> uptime_system >> uptime_idle;
  }
  return uptime_system;
}

// Done: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
  return ActiveJiffies() + IdleJiffies();
}

// Done: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{
  string line, value;
  long utime, stime, cutime, cstime;
  ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);

  if (stream.is_open())
  {
    getline(stream, line);
    istringstream linestream(line);
    std::istream_iterator<string> begin(linestream), end;
    vector<string> linecontent(begin, end);

    utime = stol(linecontent[13]);
    stime = stol(linecontent[14]);
    cutime = stol(linecontent[15]);
    cstime = stol(linecontent[16]);
  }
  return (utime + stime + cutime + cstime);
}
// Done: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
{
  vector<string> cpu = CpuUtilization();
  return stol(cpu[kUser_]) + stol(cpu[kNice_]) + stol(cpu[kSystem_]) + stol(cpu[kIRQ_]) + stol(cpu[kSoftIRQ_]) + stol(cpu[kSteal_]) + stol(cpu[kGuest_]) + stol(cpu[kGuestNice_]);
}

// Done: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
  vector<string> cpu = CpuUtilization();
  return stol(cpu[kIdle_]) + stol(cpu[kIOwait_]);
}

// Done: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{
  string line, value, cpu;
  vector<string> v_cpu;
  ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open())
  {
    getline(stream, line);
    istringstream linestream(line);
    linestream >> cpu;
    while (linestream >> value)
      v_cpu.push_back(value);
  }

  return v_cpu;
}

// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  string line, key;
  int value;
  ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
    while (getline(stream, line))
    {
      istringstream linestream(line);
      while (linestream >> key >> value)
        if (key == "processes")
          return value;
    }

  return value;
}

// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  string line, key;
  int value;
  ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open())
    while (getline(stream, line))
    {
      istringstream linestream(line);

      while (linestream >> key >> value)
        if (key == "procs_running")
          return value;
    }
  return value;
}

// Done: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid)
{
  string line, cmdline;
  ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);

  if (stream.is_open())
    getline(stream, cmdline);

  return cmdline;
}

// Done: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
{
  string line, key, value, pidstring = to_string(pid);
  ifstream stream(kProcDirectory + pidstring + kStatusFilename);

  if (stream.is_open())
    while (getline(stream, line))
    {
      istringstream linestream(line);

      while (linestream >> key >> value)
        if (key == "VmSize:")
          return to_string(stoi(value) / 1024);
    }

  return to_string(stoi(value) / 1024);
}

// Done: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid)
{
  string line, key, uid;
  ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);

  if (stream.is_open())
    while (getline(stream, line))
    {
      istringstream stringstream(line);
      stringstream >> key >> uid;
      if (key == "Uid:")
        return uid;
    }

  return string();
}
// Done: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{
  string line, key, user, x, suid, uid = LinuxParser::Uid(pid);
  ifstream stream(kPasswordPath);

  if (stream.is_open())
    while (getline(stream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      istringstream stringstream(line);
      stringstream >> user >> x >> suid;

      if (suid.compare(uid) == 0)
        return user;
    }
  return string();
}

// Done: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid)
{
  string line;
  long _sec, _clocks, process_upTime;
  long s_upTime = UpTime();

  ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);

  if (stream.is_open())
  {
    getline(stream, line);
    istringstream linestream(line);
    std::istream_iterator<string> begin(linestream), end;
    vector<string> linecontent(begin, end);

    _clocks = stol(linecontent[21]);
    _sec = _clocks / frequency;
    process_upTime = s_upTime - _sec;
  }
  return process_upTime;
}
