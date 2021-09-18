// ext/syscore/general.hpp
/* This file largely contains macros and defines for the other files.
 * Unto itself, it does not implement anything in particular.
 */

// Defines

// Pairing macro
#define MK_SSP(k, v) std::make_pair(std::string(k), std::string(v))