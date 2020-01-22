// Bitshifting operators
// Bitwise operators
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    cout << (a << 2); // 20

    int b = 13;
    cout << ( b >> 1);

    // and, or, xor, not
    5 & 7; // 5
    5 | 7; // 
    5 ^ 7; // 2
    ~5; // Signed int becomes negative number
    // When shifting right, the msb (twos comp) will stay where it is for signed ints (NOT unsigned)
    // In Java, we have the >>> unsigned right shift, which saves the msb instead

    cout << (~5);

    // For the hw: have a single unsigned int to work as a "char array" to keep track of characters seen
    // If we are doing all lowercase characters, can subtract 'a' to give a 0-25 index array of alphabet
    // Something like: vector is our unsigned int, loop thru characters of our input. For each, subtract
    // 'a', curr = 1 << difference, if (vector & curr != 0) return false, vector |= curr, repeat until done

    return 0;
}