#include <unistd.h>

#include "process.h"

using std::string;

// Constructor
Process::Process(int pid) 
  : _pid{pid}, _cpu_utilization{Process::CpuUtilization()} {}

// Return this process's ID
int Process::Pid() { return this->_pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() 
{
  long cycles = sysconf(_SC_CLK_TCK);
  float total_time = LinuxParser::ActiveJiffies(this->_pid) / cycles;
  float seconds = LinuxParser::UpTime(this->_pid);
  return total_time / seconds;
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->_pid); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->_pid); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->_pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->_pid); }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& other) const 
{ 
  return other._cpu_utilization < this->_cpu_utilization;
}