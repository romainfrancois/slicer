is_bare_vector <- function(x) {
  is_vector(x) && !is.object(x) && is.null(attr(x, "class"))
}

#' @export
slicer <- function(.) {
  if (is_bare_vector(.)) {
    .subset
  } else {
    vec_slice
  }
}
