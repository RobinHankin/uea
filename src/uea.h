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
    unsigned int geti() const { return i; }
    unsigned int getj() const { return j; }
};


// cij is a map from strictly positive integers to reals:
typedef map <unsigned int, double> cij;


// a 'structure' is a map from jacobi objects to cij:
typedef map <jacobi, cij> structure;  

typedef map<Rcpp::IntegerVector, double> uea;



/*

  If, for example,

  [x_1,x_2] = 9x_6
  [x_3,x_5] = 3x_1 -7x_5

  we would have

  o12[6] = +9;
  o35[1] = +3;
  o35[5] = -7;


  then

  SC[jacobi(1,2)] = o12;
  SC[jacobi(3,5)] = o35;

  or (probably better):

  const structure SC = {{jacobi(1,2),o12},{jacobi(3,4),o34}};
  

 */

// E -> 1 ; F -> 2 ; H -> 3


structure SC_temp;   // "SC" == "structure constants"
cij o12,o13,o23;
o12[3] = +1;  // [E,F] =   H
o13[1] = -2;  // [E,H] = -2E
o23[2] = +2;  // [F,H] =  2F

SC_temp[jacobi(1,2)] = o12;
SC_temp[jacobi(1,3)] = o13;
SC_temp[jacobi(2,3)] = o23;

const SC = SC_temp;

uea remove_zeros(uea &U){
   for(auto it=U.begin() ; it != C.end() ;){
        if(it->second == 0){
            it = U.erase(it); //increments pointer
        } else {
            ++it; // increment anyway
        }
    }
    return U;
}

uea throw(const List &terms, const NumericVector &coeffs){  // throw the terms together
    const size_t n=L.size();
    if(!(n == coeffs.length())){
        throw std::range_error("in prepare(), L must be the same length as 'coeffs'");
    }
    for(size_t i=0 ; i<n ; i++){
        if(coeffs[i] != 0){
            const Rcpp::IntegerVector term = as<Rcpp::IntegerVector> (L[i]);
            out[term] += coeffs[i];
        }
    }
}

uea prepare(const List &terms, const NumericVector &coeffs){

    // iterate through terms and coeffs: replace e2e1 with e1e2 -
    // [structure constants] do this recursively and return the result


    // First, throw everything together
    uea out = throw(terms, coeffs);
    return remove_zeros(out);
}


bool is_anything_increasing(const uea &x){
    if(x.size() > 1){throw std::invalid_argument("size should be 1"); }
        auto iu = U.begin(); 
        Rcpp::IntegerVector term = iu->second;
        const unsigned int n = term.length();

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

List terms(const clifford &X){  // takes a uea object, returns a list
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
        return List::create(Named("terms" ) = Rterms(C),
                            Named("coeffs") = coeffs(C)
                            );
}
