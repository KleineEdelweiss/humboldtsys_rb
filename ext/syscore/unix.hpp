// ext/syscore/unix.hpp
/* This file focuses on functionality that is generic to Unix-like
 * systems. They are mostly one-off, short methods.
 */

// Defines
#define MAXSTR 255
#define HOSTSTR char name[MAXSTR]

// Include Ruby
#include <ruby.h>

// Function includes
#include <proc/procps.h>
#include <sys/utsname.h>
#include <unistd.h>

// C-type behavior methods
extern "C" {
  VALUE method_misc_uid(VALUE); // Get the user's ID
  VALUE method_misc_root(VALUE); // Confirm user root or not
  VALUE method_syscore_boot_time(VALUE); // Get boot time
  VALUE method_syscore_uptime(VALUE); // Get uptime (delta)
  VALUE method_host_uname(VALUE); // Full uname struct wrap
  VALUE method_host_hostname(VALUE); // Hostname shortcut
  VALUE method_host_domainname(VALUE); // Domainname shortcut
} // End C-type wrapper