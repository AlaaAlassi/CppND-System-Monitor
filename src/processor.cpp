#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
using LinuxParser::CPUStates;

float Processor::Utilization() {
  std::vector<long> CpuUtilizationL;
  std::vector<std::string> CpuUtilizationS = LinuxParser::CpuUtilization();

  for(auto i:CpuUtilizationS){
     CpuUtilizationL.push_back (std::stol(i));
  }

  long usertime = CpuUtilizationL[CPUStates::kUser_] - CpuUtilizationL[CPUStates::kGuest_];                     
  long nicetime = CpuUtilizationL[CPUStates::kNice_] - CpuUtilizationL[CPUStates::kGuestNice_];                 
  long idlealltime = CpuUtilizationL[CPUStates::kIdle_] + CpuUtilizationL[CPUStates::kIOwait_];                 
  long systemalltime = CpuUtilizationL[CPUStates::kSystem_] + CpuUtilizationL[CPUStates::kIRQ_ ]+ CpuUtilizationL[CPUStates::kSoftIRQ_];
  long virtalltime = CpuUtilizationL[CPUStates::kGuest_ ]+ CpuUtilizationL[CPUStates::kGuestNice_];
  long totaltime = usertime + nicetime + systemalltime + idlealltime + CpuUtilizationL[CPUStates::kSteal_]  + virtalltime;
  float totalTimeSeconds = totaltime*0.01;
  float utilization = totalTimeSeconds / LinuxParser::UpTime();
  return totalTimeSeconds;
}