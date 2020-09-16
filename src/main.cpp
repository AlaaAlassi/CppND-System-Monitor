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
  System system;
  system.SetProcesses(processes);
  NCursesDisplay::Display(system,100);

  //std::cout << LinuxParser::Jiffies() << "\n";
  //std::cout << LinuxParser::UpTime()  << "\n";
  //std::cout << processor.Utilization()  << "\n";
  //std::cout << LinuxParser::MemoryUtilization();
  //LinuxParser::TotalProcesses()
  //LinuxParser::User(9188);
  


  
}