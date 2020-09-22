#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid):PID_(pid){};

// TODO: Return this process's ID
int Process::Pid() { 
return PID_;
}
// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 
    float total_time;
    float Hertz;
    float seconds;
    float cpu_usage;
    float utime;
    float stime;
    float cutime;
    float cstime;
    float uptime;
    float starttime;
    std::string kprocessDirectory = "/"+std::to_string(this->PID_);
    std::ifstream fileBuffer(LinuxParser::kProcDirectory +kprocessDirectory+LinuxParser::kStatFilename);
    std::string line;
    std::string field;
    int const utimeIndex = 14-1;
    int const stimeIndex = 15-1;
    int const cutimeIndex = 16-1;
    int const cstimeIndex = 17-1;
    std::vector<std::string> statVector;
    if (fileBuffer.is_open())
  {
    std::getline(fileBuffer,line);
    std::istringstream linestream(line);
    for(int i=0; i<=cstimeIndex;i++)
    {
      linestream >> field;
      if(field.size() == 0){break;};
      statVector.push_back(field);
    }
  }
    Hertz = sysconf(_SC_CLK_TCK);
    utime = std::stof(statVector[utimeIndex]);
    stime = std::stof(statVector[stimeIndex]);
    cutime = std::stof(statVector[cutimeIndex]);
    cstime = std::stof(statVector[cstimeIndex]);
    uptime = LinuxParser::UpTime();
    starttime = LinuxParser::UpTime(this->PID_);
    total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    seconds = uptime - (starttime / Hertz);
    cpu_usage = ((total_time / Hertz) / seconds);
    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(this->PID_);
 }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(this->PID_); 
    }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(this->PID_); 
    }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(this->PID_) ;
     }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return this->CpuUtilization() < a.CpuUtilization(); 
    }