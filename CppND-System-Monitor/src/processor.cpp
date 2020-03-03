#include <string>
#include <unistd.h>
#include <vector>

#include "linux_parser.h"
#include "processor.h"

using std::stol;
using std::string;
using std::vector;

float Processor::Utilization() {
    vector<string> cpu = LinuxParser::CpuUtilization();
    long totalTime = 0;
    long idle = stol(cpu[LinuxParser::CPUStates::kIdle_]) + stol(cpu[LinuxParser::CPUStates::kIOwait_]);
    for(unsigned int i=0; i<cpu.size(); i++) {
        if(i == LinuxParser::CPUStates::kGuest_ || i == LinuxParser::CPUStates::kGuestNice_) {
            totalTime -= stol(cpu[i]);
        } else {
            totalTime += stol(cpu[i]);
        }
    }
    return (float)(totalTime - idle)/totalTime;
}