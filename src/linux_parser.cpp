#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include"format.h"
#include <unistd.h>

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
  string os, version,kernel;
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float total;
  float free;
  std::string field;
  std::string line;
  std::ifstream fileBuffer(kProcDirectory + kMeminfoFilename);
  if(fileBuffer.is_open()){
    for(int i=0; i<2; i++){
      std::getline(fileBuffer, line);
      std::istringstream linestream(line);
      linestream >> field;
      if ( field == "MemTotal:"){
        linestream >> total;
      }
      if ( field == "MemFree:"){
        linestream >> free;
      }
    }
  }
  return (total - free)/total;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::string line;
  long uptime{0};
  std::ifstream fileBuffer(kProcDirectory + kUptimeFilename);
  if(fileBuffer.is_open()){
   std::getline(fileBuffer, line);
   std::istringstream linestream(line);
   linestream >> uptime;
  }

   return uptime; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long sum = 0;
  std::vector<std::string> CpuUtilizationS = LinuxParser::CpuUtilization();
  for(auto i:CpuUtilizationS){
     sum = sum + std::stol(i);
  }
  return sum;
 }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long activeJiffies;
  std::vector<long> CpuUtilizationL;
  std::vector<std::string> CpuUtilizationS = LinuxParser::CpuUtilization();
  for(auto i:CpuUtilizationS){
     CpuUtilizationL.push_back (std::stol(i));
  }
 activeJiffies = CpuUtilizationL[CPUStates::kUser_]+ CpuUtilizationL[CPUStates::kNice_]+
 CpuUtilizationL[CPUStates::kSystem_]+ CpuUtilizationL[CPUStates::kIRQ_]+
 CpuUtilizationL[CPUStates::kSoftIRQ_] + CpuUtilizationL[CPUStates::kSteal_]+
 CpuUtilizationL[CPUStates::kGuest_] + CpuUtilizationL[CPUStates::kGuestNice_];
   return activeJiffies; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
    std::vector<std::string> CpuUtilizationS = LinuxParser::CpuUtilization();
    long idle = std::stol(CpuUtilizationS[CPUStates::kIdle_]);
    long iowait = std::stol(CpuUtilizationS[CPUStates::kIOwait_]);
    long Idle = idle + iowait;
  return Idle;
   }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> CpuUtilizationVector;
  std::string line;
  std::string CPU;
  std::string temp;
  std::ifstream fileBuffer(kProcDirectory + kStatFilename);
  if(fileBuffer.is_open()){
  std::getline(fileBuffer, line);
  std::istringstream linestream(line);
  linestream >> CPU;
    for (int i=CPUStates::kUser_; i<= CPUStates::kGuestNice_; i++)
    {
      linestream >> temp;
      CpuUtilizationVector.push_back(temp);
    }

  }
  return CpuUtilizationVector; 
}



// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::ifstream fileBuffer(kProcDirectory + kStatFilename);
  std::string line;
  std::string field;
  int numberOfProcesses;
  int maxIterations = 100;
  if (fileBuffer.is_open())
  {
    for(int i=0; i<maxIterations;i++)
    {
      std::getline(fileBuffer,line);
      std::istringstream linestream(line);
      linestream >> field;
      if(field == "processes"){
        linestream >> numberOfProcesses;
        break;
      }
    }
  }
  
   return numberOfProcesses; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream fileBuffer(kProcDirectory + kStatFilename);
  std::string line;
  std::string field;
  int numberOfRunningProcesses;
  int maxIterations = 100;
  if (fileBuffer.is_open())
  {
    for(int i=0; i<maxIterations;i++)
    {
      std::getline(fileBuffer,line);
      std::istringstream linestream(line);
      linestream >> field;
      if(field == "procs_running"){
        linestream >> numberOfRunningProcesses;
        break;
      }
    }
  }
  
  return numberOfRunningProcesses; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::string kprocessDirectory = "/"+std::to_string(pid);
  std::ifstream fileBuffer(kProcDirectory +kprocessDirectory+kCmdlineFilename);
  std::string line;
  std::string field;
  if (fileBuffer.is_open())
  {
      std::getline(fileBuffer,line);
  }
  return line; 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::string kprocessDirectory = "/"+std::to_string(pid);
  std::ifstream fileBuffer(kProcDirectory+kprocessDirectory+kStatusFilename);
  std::string line;
  std::string field;
  float ramUsage;
  int maxIterations = 100;
  if (fileBuffer.is_open())
  {
    for(int i=0; i<maxIterations;i++)
    {
      std::getline(fileBuffer,line);
      std::istringstream linestream(line);
      linestream >> field;
      if(field == "VmSize:"){
        linestream >> ramUsage;
        break;
      }
    }
  }
  return (Format::Kb2Mb(ramUsage));
   }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::string kprocessDirectory = "/"+std::to_string(pid);
  std::ifstream fileBuffer(kProcDirectory +kprocessDirectory+kStatusFilename);
  std::string line;
  std::string field;
  int UID;
  int maxIterations = 100;
  if (fileBuffer.is_open())
  {
    for(int i=0; i<maxIterations;i++)
    {
      std::getline(fileBuffer,line);
      std::istringstream linestream(line);
      linestream >> field;
      if(field == "Uid:"){
        linestream >> UID;
        break;
      }
    }
  }
  
  return std::to_string(UID); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::ifstream fileBuffer(kPasswordPath);
  std::string line;
  std::string token;
  std::string delimiter = ":x:";
  std::string delimiter2 = ":";
  std::string Uid = LinuxParser::Uid(pid);
  std::string username = "non";
int maxIterations = 100;
  if (fileBuffer.is_open())
  {
    for(int i=0; i<maxIterations;i++)
    {
      std::getline(fileBuffer,line);
      std::istringstream linestream(line);
      if (line.size() == 0){break;}
      username = line.substr(0,line.find(delimiter));
      line.erase(0,username.length() + delimiter.length());
      token = line.substr(0,line.find(delimiter2));
      if (token == Uid){
       break;
        }
      }
    }
 return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::string kprocessDirectory = "/"+std::to_string(pid);
  std::ifstream fileBuffer(kProcDirectory +kprocessDirectory+kStatFilename);
  std::string line;
  std::string field;
  int maxIterations = 22;
  if (fileBuffer.is_open())
  {
    std::getline(fileBuffer,line);
    std::istringstream linestream(line);
    for(int i=0; i<maxIterations;i++)
    {
      linestream >> field;
    }
  }

  return UpTime() - (std::stol(field)/sysconf(_SC_CLK_TCK));
}