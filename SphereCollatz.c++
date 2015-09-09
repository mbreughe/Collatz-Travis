
// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

int rec_cycle_length (int n){
    static std::vector<int> cache(40000, 0);

    if (n == 1){
        return 1;
    }
    
    if (n < cache.size() && cache[n] != 0){
        return cache[n];
    }

    else{
        if ((n % 2) == 0)
            n = (n / 2);
        else
            n = (3 * n) + 1;
        
        int next = rec_cycle_length(n);
        
        if (n < cache.size())
            cache[n] = next;
        
        return 1 + next;
    }
}
// ------------
// cycle_length
// ------------
//
int cycle_length (int n){
    assert(n > 0);
    int c = 1;
    while (n > 1) {
        if ((n % 2) == 0)
            n = (n / 2);
        else
            n = (3 * n) + 1;
        ++c;
    }
    return c;
}
// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    int min_val = min(i,j);
    int max_val = max(i,j);

    int max_cyc = 0;
    for (int n=min_val; n <= max_val; ++n){
        int cyc = rec_cycle_length(n);
        max_cyc = max(max_cyc, cyc);
    }
    return max_cyc;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}
