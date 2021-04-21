### OVERVIEW ###
HumboldtSys is a genericized access library for Linux systems that follow the normal Linux filesystem arrangement (e.g.: may _not_ work on systems like NixOS or GUIX). This is a project I started, because I realized a couple others I was working on (and/or was planning to work on) were either too specific, such that using them as a dependency would result in inclusion of arbitrary and irrelevant code, or duplicating code from other projects.

This gem will aim to clear that up and provide a concrete interface for otherwise abstract processing elsewhere.

### TO-DO ###
1) [always] Copy functions, classes, and methods I see that are duplicating across other Ruby projects, and then make them operate in a way that can be used across all of them (with or without modification)
1) [always] Clean up code, as I go
1) Possibly bring in FFI code or extensions, if it makes sense and justifiably speeds up the library operations.

### INSTALLATION ###
