#include "slicer_types.h"

template <typename value_type, int RTYPE>
struct SlicerCompactPlusOne {
  static R_altrep_class_t class_t;

  static SEXP Make(SEXP x, SEXP idx){
    return R_new_altrep(class_t, x, idx);
  }

  static R_xlen_t Length(SEXP vec){
    return COMPACT_LENGTH(R_altrep_data2(vec));
  }

  static R_xlen_t First(SEXP vec) {
    return COMPACT_FIRST(R_altrep_data2(vec));
  }

  static const value_type* Start(SEXP vec) {
    return static_cast<const value_type*>(DATAPTR(R_altrep_data1(vec))) + First(vec) - 1;
  }

  static Rboolean Inspect(SEXP vec, int pre, int deep, int pvec, void (*inspect_subtree)(SEXP, int, int, int)){
    SEXP x = R_altrep_data1(vec);
    SEXP idx = R_altrep_data2(vec);
    Rprintf("compact slice %d %s (len=%d)\n", TYPEOF(x), Rf_type2char(TYPEOF(x)), XLENGTH(idx) );
    return TRUE;
  }

  static const void* Dataptr_or_null(SEXP vec){
    return static_cast<const void*>(Start(vec));
  }

  static void* Dataptr(SEXP vec, Rboolean writeable){
    return const_cast<void*>(Dataptr_or_null(vec));
  }

  static value_type Elt(SEXP vec, R_xlen_t i) {
    return Start(vec)[i];
  }

  static void Init(DllInfo* dll) {
    class_t = Init_Class(dll);

    R_set_altrep_Length_method(class_t, Length);
    R_set_altrep_Inspect_method(class_t, Inspect);

    R_set_altvec_Dataptr_method(class_t, Dataptr);
    R_set_altvec_Dataptr_or_null_method(class_t, Dataptr_or_null);

    Init_Elt();
  }

  static R_altrep_class_t Init_Class(DllInfo* dll);
  static void Init_Elt();

};

template <typename value_type, int RTYPE>
R_altrep_class_t SlicerCompactPlusOne<value_type, RTYPE>::class_t;

template <>
R_altrep_class_t SlicerCompactPlusOne<double, REALSXP>::Init_Class(DllInfo* dll) {
  return R_make_altreal_class("slicer_compact_plus_one_REALSXP", "slicer", dll);
}

template <>
void SlicerCompactPlusOne<double, REALSXP>::Init_Elt() {
  R_set_altreal_Elt_method(class_t, Elt);
}

// [[Rcpp::init]]
void init_slicer_compact_plus_one(DllInfo* dll) {
  SlicerCompactPlusOne<double, REALSXP>::Init(dll);
}

// this is the dream:
// - idx is a positive sequence,
//   so we don't have to allocate anything, we can just create an altrep
//   view of a slice of the vector
SEXP slicer_int_compact_plus_one(SEXP x, SEXP idx){
  switch(TYPEOF(x)) {
  case REALSXP: return SlicerCompactPlusOne<double, REALSXP>::Make(x, idx);
  default:
    break;
  }

  return R_NilValue;
}
