#include <ruby.h>
#include <unistd.h>

VALUE Other = Qnil;

/* Although this does not functionally provide
 * the purpose I intended it to (acting as a callback
 * for the root function, I have included it anyway,
 * in case anyone wishes to use the id method unto itself.
 */
VALUE method_uid(VALUE self) {
  return UINT2NUM(getuid());
} // End uid

/* This method returns whether the user is
 * root or not -- in case whatever calling
 * function needs to know (such as access to
 * system files or driver APIs -- my own
 * specific use case for other projects).
 */
VALUE method_root(VALUE self) {
  return (getuid() == 0 ? Qtrue : Qfalse);
} // End root

// Initialize the extension and attach the functions
void Init_other() {
  Other = rb_define_module("Other");
  rb_define_module_function(Other, "uid", method_uid, 0);
  rb_define_module_function(Other, "root", method_root, 0);
} // End initialization