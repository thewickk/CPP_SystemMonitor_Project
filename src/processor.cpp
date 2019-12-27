#include <string>

#include "processor.h"
#include "linux_parser.h"


const std::vector<std::string> cpu_values{LinuxParser::CpuUtilization()};

float Processor::User() { return std::stoi(cpu_values.at(0)); }
float Processor::Nice() { return std::stoi(cpu_values.at(1)); }
float Processor::System() { return std::stoi(cpu_values.at(2)); } 
float Processor::Idle() { return std::stoi(cpu_values.at(3)); }
float Processor::IOwait() { return std::stoi(cpu_values.at(4)); }
float Processor::IRQ() { return std::stoi(cpu_values.at(5)); }
float Processor::SoftIRQ() { return std::stoi(cpu_values.at(6)); }
float Processor::Steal() { return std::stoi(cpu_values.at(7)); }
float Processor::Guest() { return std::stoi(cpu_values.at(8)); }
float Processor::GuestNice() { return std::stoi(cpu_values.at(9)); }

// Return Total Jiffies
float Processor::TotalJiffies() 
{
    float total_jiffies{0};
    for ( const auto & jiffy : cpu_values)
    {
        total_jiffies += std::stof(jiffy);
    }
    return total_jiffies;
}

// Return Active Jiffies
float Processor::ActiveJiffies() 
{
    return (User() + Nice() + System() + IRQ() + SoftIRQ());
}

// Return Idle Jiffies
float Processor::IdleJiffies()
{
    return (IdleJiffies() + IOwait());
}


// Return the aggregate CPU utilization
float Processor::Utilization()
{
    float idle = Idle() + IOwait();
    float non_idle = User() + Nice() + System() + IRQ() + SoftIRQ() + Steal();
    float total = Idle() + non_idle;
    float cpu_percent = (total - idle) / total;
    return cpu_percent;
}