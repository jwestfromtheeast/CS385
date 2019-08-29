/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Justin Westley
 * Version : 1.0
 * Date    : August 29, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
using namespace std;

int gcd_iterative(int m, int n) {
    int minimum = min(m, n);
    while (minimum > 1) {
        if (m % minimum == 0 && n % minimum == 0) {
            return minimum;
        }
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
    return gcd_recursive_helper(m, n, min(m, n));
}

int main() {
    return 0;
}