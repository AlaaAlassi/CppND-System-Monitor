#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
using LinuxParser::CPUStates;

float Processor::Utilization() {
  long activeJiffies = LinuxParser::ActiveJiffies();
  float totalTimeSeconds = activeJiffies*0.01;
  float utilization = totalTimeSeconds / LinuxParser::UpTime();
  return utilization;
}