#include <unistd.h>
#include <string>
#include <vector>
#include <thread>

#include "linux_parser.h"
#include "processor.h"

using std::stol;
using std::string;
using std::vector;

float Processor::Utilization() {
  long prevTotalTime = LinuxParser::Jiffies();
  long prevIdle = LinuxParser::IdleJiffies();
  std::this_thread::sleep_for (std::chrono::seconds(1));
  long totalTime = LinuxParser::Jiffies() - prevTotalTime;
  long idle = LinuxParser::IdleJiffies() - prevIdle;
  return (float)(totalTime-idle) / (float)totalTime;
}