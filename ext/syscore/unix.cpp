// ext/syscore/unix.cpp

// Include Ruby
#include <ruby.h>

// Function includes
#include <proc/procps.h>
#include <proc/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>

// Include header
#include "unix.hpp"

// C-style block
extern "C" {
  // --------- //
  // Miscellaneous user methods
  // --------- //
  
  // Return the user's ID
  VALUE method_misc_uid(VALUE self) { return UINT2NUM(getuid()); }
  
  // Returns if the current user is root or not
  VALUE method_misc_root(VALUE self) { return (getuid() == 0 ? Qtrue : Qfalse); }

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
} // End C block