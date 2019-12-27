#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "linux_parser.h"
#include "processor.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


// Return the systems Linux OS:
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::OperatingSystem()" << std::endl;
  }
  filestream.close();
  return value;
}

// Return the systems Linux kernel:
string LinuxParser::Kernel() 
{
    std::string os, version, kernel, line;
    std::ifstream filestream{kProcDirectory + kVersionFilename};

    if (filestream.is_open())
    {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> os >> version >> kernel;
    }
    else
    {
      std::cerr << "File open error in LinuxParser::Kernel()" << std::endl;
    }
    filestream.close();
    return kernel;
}


// Parse /proc directory and return all PID directories:
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  for (const auto & entry : std::filesystem::directory_iterator(kProcDirectory))
  {
      std::string proc, temp;
      int pid;
      std::istringstream linestream{entry.path()};
      linestream >> proc;
      std::replace(proc.begin(), proc.end(), '/', ' ');
      std::istringstream validator{proc};
      if (validator >> temp >> pid)
      {
          pids.push_back(pid);
      }
  }
  return pids;
}

// Return calculated RAM utilization based on information contained in /proc/meminfo:
float LinuxParser::MemoryUtilization()
{ 
    std::string line{""}, key{""};
    float mem_total{0}, mem_avail{}, value{0}, mem_utilization{0};
    std::ifstream filestream{kProcDirectory + kMeminfoFilename};

    if (filestream.is_open())
    {
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            while (linestream >> key >> value)
            {
                if (key == "MemTotal:")
                     mem_total = value;
                if (key == "MemAvailable:")
                  mem_avail = value;
            }                   
        }
    }
    else
    {
      std::cerr << "File open error in LinuxParser::MemoryUtilization()" << std::endl;
    }
    
    filestream.close();

    // Calculation based off of MemAvailable relative to MemTotal and the percentage left over
    float mem_used = mem_total - mem_avail;
    mem_utilization = mem_used / mem_total;

    return mem_utilization;
}

// Return system uptime based on information from /proc/uptime:
long int LinuxParser::UpTime() 
{ 
    std::ifstream filestream{kProcDirectory + kUptimeFilename};
    long uptime{};
    std::string line;

    if (filestream.is_open())
    {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> uptime;
    }
    else
    {
      std::cerr << "File open error in LinuxParser::UpTime()" << std::endl;
    }

    filestream.close();
    return uptime; 
}


// Return system CPU utilization based on information from /proc/stat:
vector<string> LinuxParser::CpuUtilization() 
{ 
  std::string value, line, key;
  std::vector<std::string> cpu_values_list;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) 
  {
    std::getline(filestream, line);
  	std::istringstream linestream(line);
   	while (linestream >> key)
    	if (key != "cpu")
          cpu_values_list.push_back(key);
  }
  else
  {
    std::cerr << "File open error in LinuxParser::CpuUtilization()" << std::endl;
  }
  filestream.close();
  return cpu_values_list;
}


// Return total number of processes based on information from /proc/stat:
int LinuxParser::TotalProcesses() 
{
    std::ifstream filestream{kProcDirectory + kStatFilename};
    int processes{0}, temp{0};
    std::string key{""}, line{""};

    if (filestream.is_open())
    {    
        while ( std::getline(filestream, line) )
        {
            std::istringstream stat_stream(line);
            stat_stream >> key >> temp;
            if ( key == "processes")
            {
                processes = temp;
            }
        }
    }
    else
    {
      std::cerr << "File open error in LinuxParser::TotalProcesses()" << std::endl;
    }

    filestream.close();
    return processes;
}

// Return number of running processes based on information from /proc/stat:
int LinuxParser::RunningProcesses()
{
    std::ifstream filestream{kProcDirectory + kStatFilename};
    int procs_running{0}, temp{0};
    std::string key{""}, line{""};

    if (filestream.is_open())
    {    
        while ( std::getline(filestream, line) )
        {
            std::istringstream linestream(line);
            linestream >> key >> temp;
            if ( key == "procs_running")
            {
                procs_running = temp;
            }
        }
    }
    else
    {
      std::cerr << "File open error in LinuxParser::RunningProcesses()" << std::endl;
    }

    filestream.close();
    return procs_running;
}

// **** PID Helper Functions ****

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) 
{ 
  std::ifstream filestream{kProcDirectory + std::to_string(pid) + kStatFilename};
  std::vector<std::string> jiffy_list{};
  std::string entry{""}, line{""};
  // values taken from: 
  // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  long active_jiffies, utime, stime, cutime, cstime;

  if ( filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while ( linestream >> entry)
    {
      jiffy_list.push_back(entry);
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::ActiveJiffies()" << std::endl;
  }

  filestream.close();

  utime = std::stol(jiffy_list.at(14));
  stime = std::stol(jiffy_list.at(15));
  cutime = std::stol(jiffy_list.at(16));
  cstime = std::stol(jiffy_list.at(17));

  active_jiffies = utime + stime + cutime + cstime;

  return active_jiffies;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) 
{ 
  std::ifstream filestream{kProcDirectory + std::to_string(pid) + kCmdlineFilename};
  std::string line{""}, cmd{""};

  if (filestream.is_open())
  { 
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> cmd;
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::Command()" << std::endl;
  }

  filestream.close();

  return cmd; 
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{ 
  std::ifstream filestream{kProcDirectory + std::to_string(pid) + kStatusFilename};
  std::string line{""}, key{""};
  int value{0}, kB{0}, MB{0};

  if ( filestream.is_open())
  {
    while ( std::getline(filestream, line) )
    {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if ( key == "VmSize:")
      {
        kB = value;
      }
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::Ram()" << std::endl;
  }

  filestream.close();
  
  MB = kB / 1000;
  return std::to_string(MB); 
}

// Read and return the user ID associated with a process
std::string LinuxParser::Uid(int pid) 
{ 
  std::ifstream filestream{kProcDirectory + std::to_string(pid) + kStatusFilename};
  std::string line{""}, key{""};
  int value{0}, uid{0};

  if ( filestream.is_open())
  {
    while ( std::getline(filestream, line) )
    {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if ( key == "Uid:")
      {
        uid = value;
      }
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::Uid()" << std::endl;
  }

  filestream.close();
      
  return std::to_string(uid); 
}

// Read and return the user associated with a process
std::string LinuxParser::User(int pid) 
{ 
  std::string user_id = Uid(pid);
  std::string etc_passwd = "/etc/passwd";
  std::ifstream filestream{etc_passwd};
  std::string line{""}, user{""}, username{""}, encrpt_passwd{""}, uid{""};

  if ( filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> username >> encrpt_passwd >> uid;
      if ( uid == user_id)
      {
        user = username;
      }
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::User()" << std::endl;
  }

  filestream.close();
  return user; 
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid)
{
  std::ifstream filestream{kProcDirectory + std::to_string(pid) + kStatFilename};
  std::vector<std::string> jiffy_list{};
  std::string entry{""}, line{""};
  long pid_start, up_time;

  if ( filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while ( linestream >> entry)
    {
      jiffy_list.push_back(entry);
    }
  }
  else
  {
    std::cerr << "File open error in LinuxParser::UpTime()" << std::endl;
  }

  filestream.close();
  pid_start = std::stol(jiffy_list.at(21)) / sysconf(_SC_CLK_TCK);

  up_time = LinuxParser::UpTime() - pid_start;

  return up_time;
}

// **** End - PID Helper Functions ****