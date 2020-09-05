#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>

int main() {

  System system;
  Processor processor;
  //NCursesDisplay::Display(system);

  //std::cout << LinuxParser::Jiffies() << "\n";
  std::cout << LinuxParser::UpTime()  << "\n";
  std::cout << processor.Utilization()  << "\n";

  
  
}