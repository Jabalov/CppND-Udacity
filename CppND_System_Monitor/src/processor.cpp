#include "processor.h"

#include <thread>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
  long before_idle = LinuxParser::IdleJiffies();
  long before_active = LinuxParser::ActiveJiffies();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  long idle = LinuxParser::IdleJiffies();
  long active = LinuxParser::ActiveJiffies();

  idle -= before_idle;
  active -= before_active;

  return (float)active / (float)(active + idle);
}
