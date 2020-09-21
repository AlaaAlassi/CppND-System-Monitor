#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <iostream>
#include<algorithm>

int main() {
 std::vector<Process> processes;
 int n = 20;
 std::vector<int> pidVector = LinuxParser::Pids();
 for (auto pid:pidVector){
   processes.push_back(Process(pid));
  }
 std::sort(processes.begin(),processes.end());
 std::reverse(processes.begin(),processes.end());
 System system;
 system.SetProcesses(processes);
 NCursesDisplay::Display(system,n);

}