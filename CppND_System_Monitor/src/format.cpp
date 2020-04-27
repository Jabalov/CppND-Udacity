#include "format.h"

#include <string>

using std::string;
using std::to_string;

// Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{
  long hour = 0, min = 0, sec = 0;

  hour = seconds / 3600;
  min = (seconds % 3600) / 60;
  sec = (seconds % 3600) % 60;
  return (hour < 10 ? "0" + to_string(hour) : to_string(hour)) + ":" + (min < 10 ? "0" + to_string(min) : to_string(min)) + ":" + (sec < 10 ? "0" + to_string(sec) : to_string(sec));
}