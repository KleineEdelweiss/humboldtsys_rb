// ext/syscore/memory.cpp

// Include Ruby
#include <ruby.h>

// Library includes
#include <proc/sysinfo.h>

// Include header
#include "memory.hpp"

// Block should operate as C code
extern "C" {
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
} // End C block