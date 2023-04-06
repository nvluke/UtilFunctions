#include <RcppEigen.h>
#include <string>
#include <vector>
#include <chrono>

// [[Rcpp::plugins(cpp17)]] 

using namespace Rcpp;
using namespace Eigen;
using namespace std;

// [[Rcpp::depends(RcppEigen)]]

// [[Rcpp::export]]
List ReadGeno(const string & filename){
  ifstream infile(filename);
  string   line;
  string   delim = " ";
  string   nameid;
  string   mij; 
  int      pos1;
  int      pos2;
  int      posn;
  int      i = 0;
  int      j = 0;
  int      k = 0;
  size_t   start;
  size_t   end;
  size_t   nump;
  /*
   * Return a list with genotypes in a matrix, and a vector of IDs
   */
  List Out;
  /*
   * Find dimensions first
   */
  int n = 0;
  int m = 0;
  auto t1 = chrono::steady_clock::now();
  while(getline(infile, line)){
    if(n == 0){
      start = line.find(delim);
      end   = line.size();
      nump  = line.find_first_of("0123456789", start);
      pos1  = start + delim.size();
      pos2  = end;
      posn  = nump;
      if(pos1 < posn){
        pos1 = posn;
      }
      m     = pos2 - pos1;
    }
    n++;
  }
  Rcpp::Rcout << "----------------------------------------------------------------------------\n";
  Rcpp::Rcout << "Genotype file:            " << filename << "\n";
  Rcpp::Rcout << "Number of individuals:    " << n << "\n";
  Rcpp::Rcout << "Number of markers:        " << m << "\n";
  /*
   * Go back to beginning of file and process genotypes
   */
  infile.clear();
  infile.seekg(0);
  MatrixXi M = MatrixXi::Zero(n, m);
  vector<string> ID(n);
  i = 0;
  while(getline(infile, line)){
    start  = line.find(delim);
    end    = line.size();
    nump   = line.find_first_of("0123456789", start);
    nameid = line.substr(0, start);
    ID[i]  = nameid; // Save animal ID in vector
    k      = 0;
    for(j = nump; j < end; j++){
      // Saving genotypes into matrix
      mij     = line[j];
      M(i, k) = stoi(mij);
      k++;
    }
    i++;
  }
  auto t2 = chrono::steady_clock::now();
  chrono::duration<double> ttime = t2 - t1;
  Rcpp::Rcout << "Genotypes read in:        " << ttime.count() << " seconds\n";
  Rcpp::Rcout << "----------------------------------------------------------------------------\n";
  Out["Genotypes"] = M;
  Out["ID"] = ID;
  return(Out);
}