#include <string>
#include "linux_parser.h"
#include "format.h"
#include <sstream>
#include <iomanip>



using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
  int HH = seconds / 3600;
  int remainingTime  = seconds % 3600;
  int MM = remainingTime / 60;
  int SS = remainingTime % 60;

  std::stringstream ss;
  ss << std::setw(2);
  ss << std::setfill('0');
  ss << std::to_string(HH) << ":";
  
  ss << std::setw(2);
  ss << std::setfill('0');
  ss << std::to_string(MM) << ":";
  
  ss << std::setw(2);
  ss << std::setfill('0');
  ss << std::to_string(SS);

  return ss.str();
}

std::string Format::Kb2Mb(float kiloB) {
  
  float megaB = kiloB / 1024;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1) << megaB;

  return ss.str();
}