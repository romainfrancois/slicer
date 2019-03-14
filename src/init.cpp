#include "slicer.h"

static const R_CallMethodDef CallEntries[] = {
  {"slicer_int", (DL_FUNC) &slicer_int, 2},
  {NULL, NULL, 0}
};

void init_slicer_compact_plus_one(DllInfo* dll);

extern "C" void R_init_slicer(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  init_slicer_compact_plus_one(dll);
}
