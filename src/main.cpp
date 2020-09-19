#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>

int main() {
 std::vector<Process> processes;
  int n = 10;
  std::vector<int> pidVector = LinuxParser::Pids();
        for (auto pid:pidVector){
         processes.push_back(Process(pid));
        }
  std::vector<Process>::const_iterator first = processes.end() -n ;
  std::vector<Process>::const_iterator last = processes.end();
  std::vector<Process> subProc(first, last);
  System system;
  std::vector<Process> testpro;
  testpro.push_back(3867);
  system.SetProcesses(subProc);
 NCursesDisplay::Display(system,n);

}