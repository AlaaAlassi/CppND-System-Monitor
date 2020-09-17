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

  std::vector<Process>::const_iterator first = processes.begin() + 1000;
  std::vector<Process>::const_iterator last = processes.begin() + 1020;
  std::vector<Process> subProc(first, last);
  System system;
  system.SetProcesses(processes);
  NCursesDisplay::Display(system,100);

  //std::cout <<  LinuxParser::Command(2879)  << "\n";
  
}