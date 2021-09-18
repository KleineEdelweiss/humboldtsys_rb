// ext/syscore/syscore.c

// Include Ruby
#include <ruby.h>

// Core function libraries
#include <cpuinfo.h>

// Local includes
#include "cpu.hpp"
#include "memory.hpp"
#include "unix.hpp"

// Defines

// Core Ruby methods in C
extern "C" {
  // Core module and class data
  VALUE SysCore = Qnil;

  // Init method
  void Init_syscore() {
    // Define the module
    SysCore = rb_define_module("SysCore");
    
    // CpuInfo read-only
    //rb_define_readonly_variable("$CpuInfoInit", &cpu_info_init);
    //CpuInfoInit = Qfalse; // Give it a default non-init state
    
    // Module methods
    // Extraneous / general accessors
    rb_define_module_function(SysCore, "uid", method_misc_uid, 0);
    rb_define_module_function(SysCore, "root?", method_misc_root, 0);
    
    // Time methods
    rb_define_module_function(SysCore, "boot_time", method_syscore_boot_time, 0);
    rb_define_module_function(SysCore, "btime", method_syscore_boot_time, 0);
    rb_define_module_function(SysCore, "uptime", method_syscore_uptime, 0);
    
    // Host access methods
    rb_define_module_function(SysCore, "uname", method_host_uname, 0);
    rb_define_module_function(SysCore, "hostname", method_host_hostname, 0);
    rb_define_module_function(SysCore, "domainname", method_host_domainname, 0);
    
    // CpuInfo methods
    //rb_define_module_function(SysCore, "init", method_syscore_cpuinfo_init, 0);
    //rb_define_module_function(SysCore, "deinit", method_syscore_cpuinfo_deinit, 0);
    rb_define_module_function(SysCore, "cpu_count", method_syscore_cpu_count, 0);
    
    // Other CPU methods
    // Stat the processor cores
    rb_define_module_function(SysCore, "pstat",
      SysCorePlusPlus::method_syscore_proc_stat, 0);
    
    // Memory methods
    rb_define_module_function(SysCore, "mem", method_syscore_ram, 0);
    rb_define_module_function(SysCore, "swap", method_syscore_swap, 0);
    
    // Processes
    rb_define_module_function(SysCore, "pcount", method_syscore_procps_count, 0);
    
    // De-initialize libraries
    atexit(cpuinfo_deinitialize);
  } // End init
}