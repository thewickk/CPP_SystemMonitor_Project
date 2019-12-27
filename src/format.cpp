#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// Helper function to turn seconds into a HH:MM:SS format:
string Format::ElapsedTime(long system_seconds) 
{ 
    const int sec_in_day = 86400;
    const int sec_in_hour = 3600;
    const int sec_in_min = 60;
    const int second = 1;

    int hours = system_seconds / sec_in_hour;
    int minutes = ((system_seconds % sec_in_day) % sec_in_hour) / sec_in_min;
    int seconds = (((system_seconds % sec_in_day) % sec_in_hour) % sec_in_min) / second;

    std::ostringstream oss{};
    oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    std::string formatted_uptime = oss.str();

    return formatted_uptime;

}