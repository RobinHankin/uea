// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

#include "uea.h"

// [[Rcpp::export]]
List c_identity(const List &SC       , // "SC" == "structure constants" 
                const List &terms    , 
                const NumericVector &coeffs
                ){
    return retval(prepare(SC,terms,coeffs));  // the meat
}

// [[Rcpp::export]]
List c_add(
           const List &SC,
           const List &terms1, const NumericVector &coeffs1,
           const List &terms2, const NumericVector &coeffs2
          ){
    return retval(c_add(prepare(SC,terms1,coeffs1),
                        prepare(SC,terms2,coeffs2)));
}

// [[Rcpp::export]]
List c_prod(
           const List &SC,
           const List &terms1, const NumericVector &coeffs1,
           const List &terms2, const NumericVector &coeffs2
          ){
    return retval(c_prod(prepare(SC,terms1,coeffs1),
                         prepare(SC,terms2,coeffs2)));
}


