#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
using LinuxParser::CPUStates;

float Processor::Utilization() {
  long activeJiffies= LinuxParser::ActiveJiffies();
  long total = LinuxParser::Jiffies();
   float utilization = ((float)activeJiffies/(float)total);
  return utilization;
}