#define R_NOREMAP
#include <R.h>
#include <Rinternals.h>
#include <Rversion.h>

// because we need to initialize the altrep class
#include <R_ext/Rdynload.h>

#if R_VERSION < R_Version(3, 6, 0)

// workaround because R's <R_ext/Altrep.h> not so conveniently uses `class`
// as a variable name, and C++ is not happy about that
//
// SEXP R_new_altrep(R_altrep_class_t class, SEXP data1, SEXP data2);
//
#define class klass

// Because functions declared in <R_ext/Altrep.h> have C linkage
extern "C" {
#include <R_ext/Altrep.h>
}

// undo the workaround
#undef class

#else
#include <R_ext/Altrep.h>
#endif

#define COMPACT_SEQ_INFO(x) R_altrep_data1(x)
#define COMPACT_SEQ_EXPANDED(x) R_altrep_data2(x)

#define COMPACT_LENGTH(info) REAL0(info)[0]
#define COMPACT_FIRST(info) REAL0(info)[1]
#define COMPACT_INCR(info) REAL0(info)[2]

SEXP slicer_int_compact_plus_one(SEXP x, SEXP idx);
SEXP slicer_int_compact_minus_one(SEXP x, SEXP idx);
SEXP slicer_int_abritrary(SEXP x, SEXP idx);

SEXP slicer_int(SEXP x, SEXP idx);
