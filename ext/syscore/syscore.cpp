// ext/syscore/syscore.c

// Include Ruby
#include <ruby.h>

// Core function libraries
#include <cpufreq.h>
#include <cpuinfo.h>
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>

// C++ includes
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// Local includes
//#include ""

// Defines
#define MAXSTR 255
#define HOSTSTR char name[MAXSTR]
#define PROC_FILE "/proc/stat"

// Typedef for what a logical core is
typedef struct {
  int pindex; // Processor index
  
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
} lcore_t; // End logical processor struct wrapper

// Read in a single logical processor and map it
// Not exported, because takes non-Ruby values
VALUE u_method_syscore_map_lcore() {
  
} // End CPU logical core wrapper

// Processor usage stat method
VALUE method_syscore_proc_stat(VALUE self) {
  // Optimizations
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  
  // File
  std::ifstream fd;
  
  // Data components
  std::string sub, name;
  double user, nice, system, idle, iowait, irq, softirq,
    steal, guest, guest_nice;
  double total, avg;
  int pindex;
  
  // Logical processor core
  lcore_t lc;
  
  // Counter
  int count = 0;
  
  // Stream read loop
  fd.open(PROC_FILE);
  while (fd >> name >> lc.user >> lc.nice >> lc.system >> lc.idle
    >> lc.iowait >> lc.irq >> lc.softirq >> lc.steal >> lc.guest
    >> lc.guest_nice
  ) {
    //std::cout << std::fixed << std::setprecision(0);
    avg = 0.0; // Reset the average
    sub = name.substr(0,3);
    if (sub != "cpu") { break; }
    
    // Generate the total value of this parse timings
    //total = user + nice + system + idle + iowait + irq + softirq
    //  + steal + guest + guest_nice;
      
    // DEBUG
    /*std::cout << "ROW : " << name << " " << user << " " << nice << " "
      << system << " " << idle << " " << iowait << " " << irq << " "
      << softirq << " " << steal << " " << guest << " " << guest_nice << "\n"
      << " total: " << total << "\n---\n";*/
    
    // Set the index of the processor
    if (name.length() > 3) { pindex = std::stoi(name.substr(3)); }
    else { pindex = -1; } // -1 will be used for the average
    //std::cout << "Index for this processor will be: " << pindex << "\n";
    
    // See if there was a previous entry with this key
    // Change this to use the pindex, later...
    /*auto old = stat_data.find(pindex);
    if (old != stat_data.end()) {
      std::cout << std::fixed << std::setprecision(2);
      auto odat = old->second;
      long otot = std::get<1>(odat);
      long oidl = std::get<2>(odat);
      long deltot = total - otot;
      long delidl = idle - oidl;
      //std::cout << "(total, idle, deltot, delidl) = "
        << total << ", " << idle << ", " << deltot << ", "
        << delidl << "\n";
      avg = ((double(deltot) - double(delidl)) / double(deltot)) * 100;
      //std::cout << "Average use: " << avg << "%\n";
    }*/
    //stat_data.emplace(pindex, std::make_tuple(name, total, idle, avg));
    count++;
  }
  fd.close(); // Clean up file descriptor
  //std::cout << "Total lines with core data in proc file: " << count << "\n";
  //end_of_cores = count;
  return Qtrue;
} // End processor usage stat method

extern "C" {
  // Core module and class data
  VALUE SysCore = Qnil;
  VALUE CpuInfoInit = Qnil;

  // --------- //
  // Miscellaneous access methods
  // --------- //

  // Return the user's ID
  VALUE method_misc_uid(VALUE self) { return UINT2NUM(getuid()); }

  // Returns if the current user is root or not
  VALUE method_misc_root(VALUE self) { return (getuid() == 0 ? Qtrue : Qfalse); }

  // --------- //
  // Host information access methods
  // --------- //

  /* Return data from the uname system call.
    * 
    * The nodename field was not included (currently), because it becomes redundant
    * with the gethostname() function. Using the nodename field adds in an extra
    * instance of the hostname, which, if not updated in both calls, results in 
    * inconsistent values. This has 2 potential side effects:
    * 
    * 1) The library MUST update both EVERY time (despite nodename being the only
    *      value that can generally change without a system reboot...)
    * 2) The user of the extension potentially having erroneous data
    * 
    * Will decide at a later time whether to add it back in or not, but I will
    * leave it commented out, for now.
    */
  VALUE method_host_uname(VALUE self) {
    // Initialize a sysinfo struct and populate it
    struct utsname sysinfo;
    uname(&sysinfo);
    
    // Generate a hash to return to Ruby
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, rb_id2sym(rb_intern("sysname")), rb_str_new2(sysinfo.sysname));
    //rb_hash_aset(hash, rb_id2sym(rb_intern("nodename")), rb_str_new2(sysinfo.nodename));
    rb_hash_aset(hash, rb_id2sym(rb_intern("release")), rb_str_new2(sysinfo.release));
    rb_hash_aset(hash, rb_id2sym(rb_intern("version")), rb_str_new2(sysinfo.version));
    rb_hash_aset(hash, rb_id2sym(rb_intern("machine")), rb_str_new2(sysinfo.machine));
    
    return hash;
  } // End uname

  // Return the host name
  VALUE method_host_hostname(VALUE self) {
    HOSTSTR;
    gethostname(name, MAXSTR);
    return rb_str_new2(name);
  } // End host name

  // Return the domain name
  VALUE method_host_domainname(VALUE self) {
    HOSTSTR;
    getdomainname(name, MAXSTR);
    return rb_str_new2(name);
  } // End domain name

  // --------- //
  // Base system time monitoring methods
  // --------- //

  // Return the boot time of the machine
  VALUE method_syscore_boot_time(VALUE self) {
    return INT2NUM(getbtime());
  } // End boot time method

  // Return the uptime of the machine
  VALUE method_syscore_uptime(VALUE self) {
    double upsecs, idlesecs;
    uptime(&upsecs, &idlesecs);
    
    VALUE out = rb_hash_new();
    rb_hash_aset(out, ID2SYM(rb_intern("up")), DBL2NUM(upsecs));
    rb_hash_aset(out, ID2SYM(rb_intern("idle")), DBL2NUM(idlesecs));
    
    return out;
  } // End uptime method

  // --------- //
  // Resource management methods
  // --------- //

  // Initialize the CPU info
  VALUE method_syscore_cpuinfo_init(VALUE self) {
    if (!CpuInfoInit) {
      // Initialize the system. On success, store a Ruby version of true
      CpuInfoInit = cpuinfo_initialize() ? Qtrue : Qfalse;
    }
    return CpuInfoInit; // Return current state of the flag
  } // End CPU info init

  // Deinitialize the CPU info
  VALUE method_syscore_cpuinfo_deinit(VALUE self) {
    if (CpuInfoInit) {
      // If the flag is initialized, run the cleanup
      cpuinfo_deinitialize();
      CpuInfoInit = Qfalse; // Then set the flag to Ruby false
    }
    return CpuInfoInit; // Return the flag
  } // End CPU info deinit

  // --------- //
  // Memory monitoring methods
  // --------- //

  // RAM method
  VALUE method_syscore_ram(VALUE self) {
    meminfo(); // Initialize the memory info
    VALUE out = rb_hash_new(); // Initialize the storage struct
    
    // Main memory
    rb_hash_aset(out, ID2SYM(rb_intern("free")), LONG2NUM(kb_main_free));
    rb_hash_aset(out, ID2SYM(rb_intern("avail")), LONG2NUM(kb_main_available));
    rb_hash_aset(out, ID2SYM(rb_intern("cached")), LONG2NUM(kb_main_cached));
    rb_hash_aset(out, ID2SYM(rb_intern("buffers")), LONG2NUM(kb_main_buffers));
    rb_hash_aset(out, ID2SYM(rb_intern("used")), LONG2NUM(kb_main_used));
    rb_hash_aset(out, ID2SYM(rb_intern("total")), LONG2NUM(kb_main_total));
    
    return out;
  } // End RAM method

    // SWAP method
  VALUE method_syscore_swap(VALUE self) {
    meminfo(); // Initialize the memory info
    VALUE out = rb_hash_new(); // Initialize the storage struct
    
    // Swap data
    rb_hash_aset(out, ID2SYM(rb_intern("free")), LONG2NUM(kb_swap_free));
    rb_hash_aset(out, ID2SYM(rb_intern("used")), LONG2NUM(kb_swap_used));
    rb_hash_aset(out, ID2SYM(rb_intern("total")), LONG2NUM(kb_swap_total));
    
    return out;
  } // End SWAP method

  // --------- //
  // Processor monitoring methods
  // --------- //

  // --------- //
  // End of monitoring and resource section
  // --------- //

  // Init method
  void Init_syscore() {
    // Define the module
    SysCore = rb_define_module("SysCore");
    
    // CpuInfo read-only
    rb_define_readonly_variable("$CpuInfoInit", &CpuInfoInit);
    CpuInfoInit = Qfalse; // Give it a default non-init state
    
    // Module methods
    // Extraneous / general accessors
    rb_define_module_function(SysCore, "uid", method_misc_uid, 0);
    rb_define_module_function(SysCore, "root", method_misc_root, 0);
    
    // Time methods
    rb_define_module_function(SysCore, "boot_time", method_syscore_boot_time, 0);
    rb_define_module_function(SysCore, "uptime", method_syscore_uptime, 0);
    
    // Host access methods
    rb_define_module_function(SysCore, "uname", method_host_uname, 0);
    rb_define_module_function(SysCore, "hostname", method_host_hostname, 0);
    rb_define_module_function(SysCore, "domainname", method_host_domainname, 0);
    
    // CpuInfo methods
    rb_define_module_function(SysCore, "init", method_syscore_cpuinfo_init, 0);
    rb_define_module_function(SysCore, "deinit", method_syscore_cpuinfo_deinit, 0);
    
    // Other CPU methods
    // Stat the processor cores
    rb_define_module_function(SysCore, "pstat", method_syscore_proc_stat, 0);
    
    // Memory methods
    rb_define_module_function(SysCore, "mem", method_syscore_ram, 0);
    rb_define_module_function(SysCore, "swap", method_syscore_swap, 0);
  } // End init
}