#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>

int main() {

  System system;
  NCursesDisplay::Display(system);
  //std::cout << LinuxParser::Jiffies() << "\n";
  //std::cout << LinuxParser::UpTime()  << "\n";
  //std::cout << processor.Utilization()  << "\n";
  //std::cout << LinuxParser::MemoryUtilization();
  //LinuxParser::TotalProcesses()
  //std::cout << LinuxParser::TotalProcesses();

  
}