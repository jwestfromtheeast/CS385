/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Justin Westley
 * Date        : September 11, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

/*
* Constructor. Instantiates a sieve up to a maximum limit. Runs the sieve and counts the primes.
*/
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    num_primes_ = count_num_primes();
}

/* 
* Prints all of the primes in the current sieve to the console using cout
*/
void PrimesSieve::display_primes() const {
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);
    int primes_left_in_row = primes_per_row;
    if (num_primes_ <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) {
            if (i == max_prime_) {
                cout << setw(max_prime_width) << i;
            } else if(is_prime_[i]) {
                if (primes_left_in_row == 0) {
                    cout << endl;
                    primes_left_in_row = primes_per_row;
                }
                cout << i;
                if (primes_left_in_row != 1) {
                    cout << " ";
                }
                primes_left_in_row--;
            }
        }
    } else {
        for (int i = 2; i <= limit_; i++) {
            if (i == max_prime_) {
                cout << setw(max_prime_width) << i;
                break;
            } else if(is_prime_[i]) {
                if (primes_left_in_row == 0) {
                    cout << endl;
                    primes_left_in_row = primes_per_row;
                }
                cout << setw(max_prime_width) << i;
                if (primes_left_in_row != 1) {
                    cout << " ";
                }
                primes_left_in_row--;
            }
        }
    }
}

/*
* Counts the number of primes in the current sieve
* Returns the number of primes in the current sieve
*/
int PrimesSieve::count_num_primes() const {
    int count = 0;
    for (int i = 2; i <= limit_; i++) {
        if(is_prime_[i]) {
            count++;
        }
    }
    return count;
}

/*
* Runs the sieve algorithm on the current sieve. Called from the constructor.
*/
void PrimesSieve::sieve() {
    is_prime_[0] = false;
    is_prime_[1] = false;
    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }
    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]) {
            for (int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }
    for (int i = limit_; i >= 2; i--) {
        if (is_prime_[i]) {
            max_prime_ = i;
            break;
        }
    }
}

/*
* Counts the number of digits in a given integer
* Returns the number of digits in a given integer
*/
int PrimesSieve::num_digits(int num) {
    int count = 0;
    num = abs(num);
    if (num == 0) {
        return 1;
    }
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve sieve(limit);
    cout << endl;
    cout << "Number of primes found: " << sieve.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    sieve.display_primes();

    return 0;
}
