/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Justin Westley
 * Version : 1.0
 * Date    : August 29, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int gcd_iterative(int m, int n) {
    if (m == 0 && n == 0) {
        return 0;
    }
    m = abs(m);
    n = abs(n);
    int minimum = min(m, n);
    while (minimum > 1) {
        if (m % minimum == 0 && n % minimum == 0) {
            return minimum;
        }
        minimum--;
    }
    return 1;
}

int gcd_recursive_helper(int m, int n, int minimum) {
    if ((m % minimum == 0 && n % minimum == 0) || minimum == 1) {
        return minimum;
    }
    return gcd_recursive_helper(m, n, minimum - 1);
}

int gcd_recursive(int m, int n) {
    if (m == 0 || n == 0) {
        if (m == 0 && n == 0) {
            return 0;
        }
        if (m == 0) {
            return n;
        }
        return m;
    }
    return gcd_recursive_helper(abs(m), abs(n), min(abs(m), abs(n)));
}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }

    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) << endl;
    return 0;
}