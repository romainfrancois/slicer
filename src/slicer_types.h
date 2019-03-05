// to manipulate R objects, aka SEXP
#include <Rcpp.h>

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

// disabling exception handling
// because this is all essentially safe C code here
//
// just using Rcpp for the attributes
#undef BEGIN_RCPP
#define BEGIN_RCPP

#undef END_RCPP
#define END_RCPP
