#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // Constructor
  Process(int pid);
  
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

 private:
    int _pid{0};
    float _cpu_utilization{0};
};

#endif