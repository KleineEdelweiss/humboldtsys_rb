// ext/syscore/memory.hpp 

// Include Ruby
#include <ruby.h>

// Library includes
#include <proc/sysinfo.h>

// Wrap in C block
extern "C" {
  // Declarations
  VALUE method_syscore_ram(VALUE); // RAM / physical mem
  VALUE method_syscore_swap(VALUE); // SWAP space only
} // End C block