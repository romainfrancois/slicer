#include "slicer_types.h"

bool is_compact(SEXP idx) {
  static SEXP s_compact_intseq = Rf_install("compact_intseq");
  static SEXP s_compact_realseq = Rf_install("compact_realseq");

  if (!ALTREP(idx)) return false;
  SEXP klass = CAR(ATTRIB(ALTREP_CLASS(idx)));
  return Rf_ScalarLogical(klass == s_compact_intseq || klass == s_compact_realseq) ;
}

SEXP slicer_int_compact(SEXP x, SEXP idx) {
  return x;
}

SEXP slicer_int_abritrary(SEXP x, SEXP idx) {
  return x;
}

// [[Rcpp::export(rng = false)]]
SEXP slicer_int(SEXP x, SEXP idx){
  // if we are here, we know a few things
  // 1) x is a bare vector
  // 2) idx is an integer vector

  return is_compact(idx) ? slicer_int_compact(x, idx) : slicer_int_abritrary(x, idx);
}
