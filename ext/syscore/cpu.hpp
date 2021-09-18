// ext/syscore/cpu.hpp
/* This file contains library functionality needed to access CPU information.
 * 
 */

// Include Ruby
#include <ruby.h>

// C++ includes
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// C++ Boost convenience libraries
#include <boost/algorithm/string.hpp>

// Local includes
#include "general.hpp"

// Defines
#define PROC_FILE "/proc/stat"
#define CPU_BUS_PATH "/sys/bus/cpu/devices/"

// Method macros
#define CPUI_INIT if (!method_syscore_cpuinfo_init()) { abort(); }

// Declarations
// Decs for the C component
extern "C" {
  bool method_syscore_cpuinfo_init(); // Init method
  VALUE method_syscore_cpu_count(VALUE); // Count CPUs
  VALUE method_syscore_procps_count(VALUE);
} // End C decs

// Namespaced C++ portion
namespace SysCorePlusPlus {
  // Typedef string-string map
  typedef std::map<std::string, std::string> str_map_t;
  
  // Typedef for what a logical core is
  typedef struct {
    int pindex; // Processor index
    std::string path; // Path in SysFs
    
    // Processor use stat fields
    double user;
    double nice;
    double system;
    double idle;
    double iowait;
    double irq;
    double softirq;
    double steal;
    double guest;
    double guest_nice;
  } lcore_t; // End logical processor struct
  
  std::string u_method_read_core_attrib_file(std::string); // Read an attribute
  str_map_t u_method_syscore_lcore_paths(VALUE, std::string); // List of paths
  void u_method_syscore_lcore_online(VALUE, str_map_t); // Whether CPU online
  void u_method_syscore_lcore_package(VALUE, str_map_t); // Package number
  void u_method_syscore_lcore_core_num(VALUE, str_map_t); // Core number 
  void u_method_syscore_lcore_core_freq(VALUE, str_map_t); // Frequencies
  void u_method_syscore_lcore_core_govs(VALUE, str_map_t); // Governor availability
  void u_method_syscore_lcore_info(VALUE, str_map_t); // All the info
  VALUE u_method_syscore_map_lcore(lcore_t); // Map the core data
  VALUE method_syscore_proc_stat(VALUE); // Read the /proc/stat file
} // End C++ decs