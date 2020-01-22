/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Justin Westley
 * Date        : November 4 2019
 * Description : Computes the anagram gropus for an input file and outputs the largest.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
const int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

// Prime sort: the prime factorization is unique for a given combination of chars, if each prime
// represents a char
unsigned long prime_sort(string s) {
    unsigned long mult = 1;
    for (char c : s) {
        int curr = c;
        if (curr >= 65 && curr <= 90) {
            curr += 32;
        }
        if (curr < 97 || curr > 122) {
            return 0;
        }
        mult *= PRIMES[curr - 97];
    }
    return mult;
}

// Finds all of the most popular anagrams in the given dictionary and outputs them
// ASCII int vals: Uppercase: 65-90, Lowercase: 97-122
vector<vector<string>> find_anagrams(vector<string> dict) {
    vector<vector<string>> anagrams;
    unordered_map<unsigned long, vector<string>> groups;
    for (string s : dict) {
        unsigned long curr = prime_sort(s);
        if (curr == 0) {
            continue;
        }
        groups[curr].push_back(s);
    }
    for (auto it : groups) {
        anagrams.push_back(it.second);
    }
    return anagrams;
}

// Filters out results of our anagram finder that we do not want, as well as sorts the output
// Pretty slow with sorting, but I can't think of a better way in the hour I spent on this
vector<vector<string>> filter_max(vector<vector<string>> in) {
    vector<vector<string>> out;
    size_t max = 2;
    for (size_t i = 0; i < in.size(); i++) {
        vector<string> curr = in.at(i);
        if (curr.size() > max) {
            max = curr.size();
            out.clear();
            out.push_back(curr);
        } else if (curr.size() == max) {
            out.push_back(curr);
        }
    }
    for (size_t i = 0; i < out.size(); i++) {
        sort(out.at(i).begin(), out.at(i).end());
    }
    sort(out.begin(), out.end());
    return out;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./anagramfinder <dictionary file>" << endl;
        return 1;
    }

    // Build dictionary from input file
    ifstream file(argv[1]);
    if (file.fail()) {
        cerr << "Error: File '" << argv[1] << "' not found." << endl;
        return 1;
    }

    vector<string> dictionary;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            dictionary.push_back(line);
        }
        file.close();
    }

    if (dictionary.size() == 0) {
        cout << "No anagrams found." << endl;
        return 0;
    }
    // Find all anagrams, but we need to sort them
    vector<vector<string>> anagrams = filter_max(find_anagrams(dictionary));
    if (anagrams.size() == 0) {
        cout << "No anagrams found." << endl;
        return 0;
    }
    cout << "Max anagrams: " << anagrams.at(0).size() << endl;
    for (size_t i = 0; i < anagrams.size(); i++) {
        vector<string> curr = anagrams.at(i);
        for (size_t j = 0; j < curr.size(); j++) {
            cout << curr.at(j) << endl;
        }
        cout << "" << endl;
    }

    return 0;
}