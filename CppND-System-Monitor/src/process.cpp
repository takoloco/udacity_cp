#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {
    user_ = LinuxParser::User(Pid());
    command_ = LinuxParser::Command(Pid());
    cpuUtilization_ = LinuxParser::CpuUtilization(Pid());
}

int Process::Pid() { return pid_; }

float Process::CpuUtilization() {
    cpuUtilization_ = LinuxParser::CpuUtilization(Pid());
    return cpuUtilization_;
}

string Process::Command() { return command_; }

string Process::Ram() { return LinuxParser::Ram(Pid()); }

string Process::User() { return user_; }

long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

bool Process::operator<(Process const& a) const {
    return a.cpuUtilization_ < this->cpuUtilization_;
}