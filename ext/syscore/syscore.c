// ext/syscore/syscore.c

// Include Ruby
#include <ruby.h>

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Core module and class data
VALUE SysCore = Qnil;
VALUE CpuInfoInit = Qnil;
VALUE CpuInfoAbs = Qnil;

// Test method
VALUE method_syscore_procps_test(VALUE self) {
  return Qnil;
} // End test method

// Initialize the CPU info
VALUE method_syscore_cpuinfo_init(VALUE self) {
  if (!CpuInfoInit) {
    // Initialize the system. On success, store a Ruby true
    bool flag = cpuinfo_initialize();
    CpuInfoInit = flag ? Qtrue : Qfalse;
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

// Memory method
VALUE method_syscore_procps_memory(VALUE self) {
  meminfo(); // Initialize the memory info
  VALUE out = rb_hash_new(); // Initialize the storage struct
  
  // Main memory
  rb_hash_aset(out, ID2SYM(rb_intern("main_free")), LONG2NUM(kb_main_free));
  rb_hash_aset(out, ID2SYM(rb_intern("main_avail")), LONG2NUM(kb_main_available));
  rb_hash_aset(out, ID2SYM(rb_intern("main_cached")), LONG2NUM(kb_main_cached));
  rb_hash_aset(out, ID2SYM(rb_intern("main_buffers")), LONG2NUM(kb_main_buffers));
  rb_hash_aset(out, ID2SYM(rb_intern("main_used")), LONG2NUM(kb_main_used));
  rb_hash_aset(out, ID2SYM(rb_intern("main_total")), LONG2NUM(kb_main_total));
  
  // Swap data
  rb_hash_aset(out, ID2SYM(rb_intern("swap_free")), LONG2NUM(kb_swap_free));
  rb_hash_aset(out, ID2SYM(rb_intern("swap_used")), LONG2NUM(kb_swap_used));
  rb_hash_aset(out, ID2SYM(rb_intern("swap_total")), LONG2NUM(kb_swap_total));
  
  return out;
} // End memory method

// Return the boot time of the machine
VALUE method_syscore_procps_boot_time(VALUE self) {
  return INT2NUM(getbtime());
} // End boot time method

// Return the uptime of the machine
VALUE method_syscore_procps_uptime(VALUE self) {
  double upsecs, idlesecs;
  uptime(&upsecs, &idlesecs);
  
  VALUE out = rb_hash_new();
  rb_hash_aset(out, ID2SYM(rb_intern("up_s")), DBL2NUM(upsecs));
  rb_hash_aset(out, ID2SYM(rb_intern("idle_s")), DBL2NUM(idlesecs));
  
  return out;
} // End uptime method

// Probably remove this one...
// Average load
VALUE method_syscore_procps_load(VALUE self) {
  double a1, a5, a15;
  loadavg(&a1, &a5, &a15);
  
  VALUE out = rb_hash_new();
  rb_hash_aset(out, ID2SYM(rb_intern("av1")), DBL2NUM(a1));
  rb_hash_aset(out, ID2SYM(rb_intern("av5")), DBL2NUM(a5));
  rb_hash_aset(out, ID2SYM(rb_intern("av15")), DBL2NUM(a15));
  
  return out;
} // End load checker

// Get the cores and usages
VALUE method_syscore_cpuinfo_cpus(VALUE self) {
  // Return early, if the value cannot be initialized
  if (!method_syscore_cpuinfo_init(self)) { return CpuInfoInit; }
  
  // Otherwise get the processor list.
  const struct cpuinfo_processor *procs = cpuinfo_get_processors();
  
  int nr_procs = cpuinfo_get_processors_count();
  int nr_cores = cpuinfo_get_cores_count();
  int nr_clusters = cpuinfo_get_clusters_count();
  int nr_packages = cpuinfo_get_packages_count();
  int nr_uarchs = cpuinfo_get_uarchs_count();
  
  // Base processors information
  VALUE out = rb_hash_new();
  rb_hash_aset(out, ID2SYM(rb_intern("cpu_cnt")), INT2NUM(nr_procs));
  rb_hash_aset(out, ID2SYM(rb_intern("core_cnt")), INT2NUM(nr_cores));
  rb_hash_aset(out, ID2SYM(rb_intern("cluster_cnt")), INT2NUM(nr_clusters));
  rb_hash_aset(out, ID2SYM(rb_intern("pkg_cnt")), INT2NUM(nr_packages));
  rb_hash_aset(out, ID2SYM(rb_intern("uarch_cnt")), INT2NUM(nr_uarchs));
  
  return out;
} // End core usage method

// This is more of an overview
// Need method for all cores. If can find, delete this...
// Return the stat data
VALUE method_syscore_procps_stat(VALUE self) {
  // Pass everything by ref
  jiff cuse, cnic, csys, cidl, ciow, cxxx, cyyy, czzz;
  unsigned long pgpgin, pgpgout, pgswpin, pgswpout;
  unsigned intr, ctxt;
  unsigned int running, blocked, dummy1, dummy2;
  
  getstat(
    &cuse, &cnic, &csys, &cidl,
    &ciow, &cxxx, &cyyy, &czzz,
    
    &pgpgin, &pgpgout, &pgswpin, &pgswpout,
    &intr, &ctxt,
    &running, &blocked, &dummy1, &dummy2
  );
  
  VALUE out = rb_hash_new();
  rb_hash_aset(out, ID2SYM(rb_intern("count")), LONG2NUM(smp_num_cpus));
  rb_hash_aset(out, ID2SYM(rb_intern("cuse")), LONG2NUM(cuse));
  rb_hash_aset(out, ID2SYM(rb_intern("cnic")), LONG2NUM(cnic));
  rb_hash_aset(out, ID2SYM(rb_intern("csys")), LONG2NUM(csys));
  rb_hash_aset(out, ID2SYM(rb_intern("cidl")), LONG2NUM(cidl));
  rb_hash_aset(out, ID2SYM(rb_intern("ciow")), LONG2NUM(ciow));
  rb_hash_aset(out, ID2SYM(rb_intern("cxxx")), LONG2NUM(cxxx));
  rb_hash_aset(out, ID2SYM(rb_intern("cyyy")), LONG2NUM(cyyy));
  rb_hash_aset(out, ID2SYM(rb_intern("czzz")), LONG2NUM(czzz));
  
  rb_hash_aset(out, ID2SYM(rb_intern("pgpgin")), LONG2NUM(pgpgin));
  rb_hash_aset(out, ID2SYM(rb_intern("pgpgout")), LONG2NUM(pgpgout));
  rb_hash_aset(out, ID2SYM(rb_intern("pgswpin")), LONG2NUM(pgswpin));
  rb_hash_aset(out, ID2SYM(rb_intern("pgswpout")), LONG2NUM(pgswpout));
  
  rb_hash_aset(out, ID2SYM(rb_intern("intr")), INT2NUM(intr));
  rb_hash_aset(out, ID2SYM(rb_intern("ctxt")), INT2NUM(ctxt));
  
  rb_hash_aset(out, ID2SYM(rb_intern("running")), INT2NUM(running));
  rb_hash_aset(out, ID2SYM(rb_intern("blocked")), INT2NUM(blocked));
  rb_hash_aset(out, ID2SYM(rb_intern("dummy1")), INT2NUM(dummy1));
  rb_hash_aset(out, ID2SYM(rb_intern("dummy2")), INT2NUM(dummy2));
  
  return out;
} // End stat

// Init method
void Init_syscore() {
  // Define the module
  SysCore = rb_define_module("SysCore");
  
  // CpuInfoAbs class
  CpuInfoAbs = rb_define_class_under(SysCore, "CpuInfoAbs", rb_cObject);
  
  // CpuInfo readonly
  rb_define_readonly_variable("$CpuInfoInit", &CpuInfoInit);
  CpuInfoInit = Qfalse; // Give it a default non-init state
  
  // CpuInfo methods
  rb_define_module_function(SysCore, "init", method_syscore_cpuinfo_init, 0);
  rb_define_module_function(SysCore, "deinit", method_syscore_cpuinfo_deinit, 0);
  
  // Module methods
  // Time methods
  rb_define_module_function(SysCore, "boot_time", method_syscore_procps_boot_time, 0);
  rb_define_module_function(SysCore, "uptime", method_syscore_procps_uptime, 0);
  
  // Processor methods
  rb_define_module_function(SysCore, "stat", method_syscore_procps_stat, 0);
  rb_define_module_function(SysCore, "cpus", method_syscore_cpuinfo_cpus, 0);
  
  // Memory methods
  rb_define_module_function(SysCore, "mem", method_syscore_procps_memory, 0);
  
  // Other or marked for removal
  rb_define_module_function(SysCore, "load", method_syscore_procps_load, 0);
  
  // Test method
  rb_define_module_function(SysCore, "test", method_syscore_procps_test, 0);
} // end init