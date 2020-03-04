#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float memTotal = 0.0;
  float memFree = 0.0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          memTotal = stof(value);
        }
        if (key == "MemFree") {
          memFree = stof(value);
        }
      }
      if (memTotal && memFree) {
        return (memTotal - memFree) / memTotal;
      }
    }
  }
  return memTotal;
}

long LinuxParser::UpTime() {
  string line;
  long uptime = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

long LinuxParser::Jiffies() {
  vector<string> cpu = LinuxParser::CpuUtilization();
  long totalTime = 0;
  for (unsigned int i = 0; i < cpu.size(); i++) {
    if (i == LinuxParser::CPUStates::kGuest_ ||
        i == LinuxParser::CPUStates::kGuestNice_) {
      totalTime -= stol(cpu[i]);
    } else {
      totalTime += stol(cpu[i]);
    }
  }
  return totalTime;
}

long LinuxParser::ActiveJiffies(int pid) {
  long activeJiffies = 0;
  string line;
  string key;
  string parsedPid, comm, state, ppid, pgrp, session, ttyNr, tpgid, flags;
  string minflt, cminflt, majflt, cmajflt, utime, stime, cutime, cstime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> parsedPid >> comm >> state >> ppid >> pgrp >> session >>
        ttyNr >> tpgid >> flags;
    linestream >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >>
        cutime >> cstime;
    activeJiffies = std::stol(utime) + std::stol(stime) + std::stol(cutime) +
                    std::stol(cstime);
  }
  return activeJiffies;
}

long LinuxParser::ActiveJiffies() {
  return LinuxParser::Jiffies() - LinuxParser::IdleJiffies();
}

long LinuxParser::IdleJiffies() {
  vector<string> cpu = LinuxParser::CpuUtilization();
  return stol(cpu[LinuxParser::CPUStates::kIdle_]) +
         stol(cpu[LinuxParser::CPUStates::kIOwait_]);
}

vector<string> LinuxParser::CpuUtilization() {
  string line;
  string key;
  string value;
  vector<string> cpuUtilization;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
        while (linestream >> value) {
          cpuUtilization.push_back(value);
        }
      }
    }
  }
  return cpuUtilization;
}

int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int totalProcesses = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "processes") {
        linestream >> totalProcesses;
      }
    }
  }
  return totalProcesses;
}

int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int runningProcesses = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "procs_running") {
        linestream >> runningProcesses;
      }
    }
  }
  return runningProcesses;
}

string LinuxParser::Command(int pid) {
  string line;
  string command;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, command);
  }
  return command;
}

string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string ram;
  int ramSize = 0;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "VmSize") {
        linestream >> ram;
        ramSize = std::stoi(ram);
        ramSize /= 1000;
        ram = to_string(ramSize);
      }
    }
  }
  return ram;
}

string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string uid;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "Uid") {
        linestream >> uid;
      }
    }
  }
  return uid;
}

string LinuxParser::User(int pid) {
  string line;
  string user;
  string passwd;
  string currentUid;
  string uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (uid.length() && filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> passwd >> currentUid;
      if (currentUid == uid) {
        return user;
      }
    }
  }
  return user;
}

long LinuxParser::UpTime(int pid) {
  long uptime = 0;
  string line;
  string key;
  string parsedPid, comm, state, ppid, pgrp, session, ttyNr, tpgid, flags;
  string minflt, cminflt, majflt, cmajflt, utime, stime, cutime, cstime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> parsedPid >> comm >> state >> ppid >> pgrp >> session >>
        ttyNr >> tpgid >> flags;
    linestream >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >>
        cutime >> cstime;
    uptime = std::stol(stime) / sysconf(_SC_CLK_TCK);
  }
  return uptime;
}

float LinuxParser::CpuUtilization(int pid) {
  float utilization = 0.0;
  long totalTime, processUptime = 0;
  string line;
  string key;
  string parsedPid, comm, state, ppid, pgrp, session, ttyNr, tpgid, flags;
  string minflt, cminflt, majflt, cmajflt, utime, stime, cutime, cstime;
  string priority, nice, numThreads, itrealvalue, starttime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> parsedPid >> comm >> state >> ppid >> pgrp >> session >>
        ttyNr >> tpgid >> flags;
    linestream >> minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >>
        cutime >> cstime;
    linestream >> priority >> nice >> numThreads >> itrealvalue >> starttime;
    totalTime = std::stol(utime) + std::stol(stime) + std::stol(cutime) +
                std::stol(cstime);
    processUptime =
        LinuxParser::UpTime() - stol(starttime) / sysconf(_SC_CLK_TCK);
    utilization =
        ((float)(totalTime / sysconf(_SC_CLK_TCK)) / (float)processUptime);
  }
  return utilization;
}