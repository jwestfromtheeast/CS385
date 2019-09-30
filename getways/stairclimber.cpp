/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Justin Westley
 * Date        : September 29, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> num_ways;
    if (num_stairs <= 0) {
        num_ways.push_back({});
    } else {
        for (int i = 1; i < 4; ++i){
            if (num_stairs >= i){
                vector<vector<int>> rest;
                rest = get_ways(num_stairs - i);
                for (auto &rest_result : rest){
                    rest_result.insert(rest_result.begin(), i);
                }
                num_ways.insert(num_ways.end(), rest.begin(), rest.end());
            }
        }
    }
    return num_ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int iterations = 1;
    int space = 0;
    if (ways.size() > 9) {
        space = 1;
    } else if (ways.size() > 99) {
        space = 2;
    }

    for (auto &way : ways){
        cout << setw(space + 1) << iterations << ". [";
        for (size_t j = 0 ; j < way.size()-1; ++j) {
            cout << way[j] << ", ";
        }
        if (iterations < static_cast<int>(ways.size())) {
            cout << way[way.size()-1] << "]" << endl;
        } else {
            cout << way[way.size()-1] << "]";
        }
        ++iterations;
        if ((iterations == 10 || iterations == 100) && space != 0) {
            space--;
        }
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number of stairs>"
             << endl;
        return 1;
    }

    for (size_t i = 0; i < strlen(argv[1]); i++) {
        if (!isdigit(argv[1][i])) {
            cerr << "Error: Number of stairs must be a positive integer." << endl;
            return 1;
        }
    }

    if (stoi(argv[1]) <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    else {
        int input = stoi(argv[1]);
        vector<vector<int>> ways = get_ways(input);
        
        if (ways.size() > 1) {
            cout << ways.size() << " ways to climb " << input << " stairs." << endl;
        }
        else {
            cout << 1 << " way to climb " << 1 << " stair." << endl;
        }
        display_ways(ways);
        return 0;
    }
}
