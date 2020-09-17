#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>

int main() {
  std::vector<Process> processes;
  std::vector<int> pidVector = LinuxParser::Pids();
        for (auto pid:pidVector){
         processes.push_back(Process(pid));
        }

  std::vector<Process>::const_iterator first = processes.begin() + 300;
  std::vector<Process>::const_iterator last = processes.begin() + 320;
  std::vector<Process> subProc(first, last);
  System system;
  system.SetProcesses(subProc);
  NCursesDisplay::Display(system,20);

  //std::cout <<  LinuxParser::Command(2879)  << "\n";
  
}