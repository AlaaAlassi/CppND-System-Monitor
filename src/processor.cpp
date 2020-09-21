#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
using LinuxParser::CPUStates;

float Processor::Utilization() {
  long idleJiffies = LinuxParser::IdleJiffies();
  long total = LinuxParser::Jiffies();
  long deltaIdle = idleJiffies - this->idleJiffiesOld_;
  long deltaTotal = total - this->totalOld_;
  float utilization = ((float)(deltaTotal - deltaIdle)/(float)deltaTotal);
  this->idleJiffiesOld_ = idleJiffies;
  this->totalOld_ = total;
  return utilization;
}