// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

#define USE_UNORDERED_MAP true   // set to true for unordered_map; comment out to use plain stl map.
#define STRICT_R_HEADERS
#include <Rcpp.h>

using namespace std;
using namespace Rcpp; 

class jacobi {  // a Jacobi bracket; [i,j] -> x_i*x_j - x_i*x_i
private:
    unsigned int i;
    unsigned int j;
    // constructor:
public:
    jacobi(unsigned int i, unsigned int j){
        if (i >= j){
            throw std::invalid_argument("error: first >= second");
        }
    }

    // Getter methods to access the values
    unsigned int geti() const {
        return i;
    }

    unsigned int getj() const {
        return j;
    }
};


// cij is a map from strictly positive integers to reals:
typedef map <unsigned int, double> cij;

// a 'structure' is a map from jacobi objects to cij:
typedef map <jacobi, cij> structure;  

structure makestructure(const List &SC){
    structure out;

    return out;
}

uea prepare(const List &SC, const List &terms, const NumericVector &coeffs){
    const structure o = makestructure(SC);
    // iterate through terms and coeffs: replace e2e1 with e1e2 +
    // SC[1,2]; then return it.

    uea out;

    // processing...

    return out;
}


uea sum(const uea x1, const uea x2){
    // easy: just concatenate terms and coeffs of x1 and x2.  Function
    // c_add() simplifies the result

    uea out;
    return out;
}
    
uea multiply(const uea x1, const uea x2){
    // slightly harder: effectively does a outer() operation on the
    // terms and coeffs of x1 and x2.  c_prod() simplifies the result.

    // blah blah blah
    uea out;
    return out;
}

List terms(const clifford &X){  // takes a ueaobject, returns a list
                                // of terms; used in retval()
    List out;

    for(auto ix=X.begin(); ix != X.end(); ++ix){
        out.push_back(which(ix->first));
    }
    return out;
}

NumericVector coeffs(const uea &X){  // takes a uea object, returns the coeffs
    NumericVector out(X.size());
    unsigned int i=0;

    for(auto ix=X.begin(); ix != X.end(); ++ix){
        out[i] = ix->second;
        i++;
    }
    return out;
}


List retval(const uea &X){  // used to return a list to R
        return List::create(Named("terms" ) =  Rterms(C),
                            Named("coeffs") =  coeffs(C)
                            );
}
