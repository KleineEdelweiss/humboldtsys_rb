#include <ruby.h>
#include <unistd.h>
#include <sys/utsname.h>

#define MAXSTR 255

VALUE HostData = Qnil;

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
VALUE method_uname(VALUE self) {
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
VALUE method_hostname(VALUE self) {
  char name[MAXSTR];
  gethostname(name, MAXSTR);
  
  return rb_str_new2(name);
} // End host name

// Return the domain name
VALUE method_domainname(VALUE self) {
  char name[MAXSTR];
  getdomainname(name, MAXSTR);
  
  return rb_str_new2(name);
} // End domain name

// Initialize the extension and attach the functions
void Init_host_data() {
  HostData = rb_define_module("HostData");
  rb_define_module_function(HostData, "uname", method_uname, 0);
  rb_define_module_function(HostData, "hostname", method_hostname, 0);
  rb_define_module_function(HostData, "domainname", method_domainname, 0);
} // End initialization