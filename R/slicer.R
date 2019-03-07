is_bare_vector <- function(x) {
  is_vector(x) && !is.object(x) && is.null(attr(x, "class"))
}

#' slicer
#'
#' @param x A vector
#' @return a function
#'
#' @export
slicer <- function(x) {
  if (is_bare_vector(x)) {
    .subset
  } else {
    vec_slice
  }
}
