/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Anthony Orrico II && Justin Westley
 * Version     : 1.0
 * Date        : 12/1/19
 * Description : Finds the Shortest Path from each vertex to all other vertices
 *               using Floyds Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;
long double INF = std::numeric_limits<long double>::infinity();

// Find length of a long double (used below) for formatting table:
// uses simple conversion to string -> length() of string
int len(long double in) {
    return to_string(static_cast<long int>(in)).length();
}


// Displays the matrix on the screen formatted as a table.  
void display_table(vector< vector <long double> > matrix, int num_vertices, const string &label,const bool use_letters = false) {
    cout << label << endl;
    long double max_val = 0;
    for(int i = 0; i < num_vertices; i++) {
        for(int j = 0; j < num_vertices; j++) {
            long double cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];            
            }
        }     
    }

    int max_cell_width = use_letters ? len(max_val) :            
            len(max(static_cast<long double>(num_vertices), max_val));    
    
    cout << ' '; 
    for(int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');    
    }    
    cout << endl;
    for(int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A'); 
        for(int j = 0; j < num_vertices; j++) {            
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {                
                cout << "-";             
            } 
            else if (use_letters) {                
                cout << static_cast<char>(matrix[i][j] + 'A');            
            } 
            else{                 
                cout << static_cast<long int>(matrix[i][j]);            
            }
        } 
        cout << endl;    
    }    
    cout << endl;
}


void floyds (vector< vector<long double> > &dist_mat, vector< vector<long double> > &path_mat){
    size_t num_vert = dist_mat.size();
    for (size_t k = 0; k < num_vert; k++){
        for (size_t i = 0; i < num_vert; i++){
            for (size_t j = 0; j < num_vert; j++){
                if (min(dist_mat[i][j], dist_mat[i][k] + dist_mat[k][j]) == dist_mat[i][j])
                    dist_mat[i][j] = dist_mat[i][j];
                else {
                    dist_mat[i][j] = dist_mat[i][k] + dist_mat[k][j];
                    path_mat[i][j] = k;
                }
            }
        }
    }
}

int loadfile (string filename, vector < vector< long double >> &dist_mat, vector < vector< long double >> &path_mat){
    ifstream infile(filename);  // read in the dictionary to a vector of strings
    if(!infile){
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return -1;
    }

    string numstr;
    getline(infile, numstr);
    istringstream num;
    num.str (numstr);
    int num_vert;
    num >> num_vert;

    if (num_vert < 1 || num_vert > 26){
        cerr << "Error: Invalid number of vertices '" << numstr << "' on line 1.";
        return -1;
    }
        
    // initialize everything in dist_mat to INF = (-1) and diag to 0
    for (int i = 0; i < num_vert; i++){
        vector < long double > update;
        vector < long double > path_init;
        for (int j = 0; j < num_vert; j++) {
            if (i==j)
                update.push_back(0);
            else
                update.push_back(INF);
            path_init.push_back (INF);
        }
        dist_mat.push_back(update);
        path_mat.push_back(path_init);
    }
 
    string holder;
    int line_counter = 2;
    while (getline(infile, holder)){
        istringstream ss(holder);
        // Starting vertex
        string start_s;
        ss >> start_s;
        if (start_s.length() > 1){
            cerr << "Error: Starting vertex '" << start_s << "' on line " << line_counter
                << " is not among valid values A-" << char('A' + num_vert-1) << "."<< endl;
            return -1;
        }
        char start = start_s.at(0);
        if (start < 'A' || start >= 'A' + num_vert) {
            cerr << "Error: Starting vertex '" << start << "' on line " << line_counter
                << " is not among valid values A-" << char('A' + num_vert-1) << "."<< endl;
            return -1;
        }   

        // Ending vertex
        string end_s;
        ss >> end_s;
        if (end_s.length() > 1){
            cerr << "Error: Ending vertex '" << end_s << "' on line " << line_counter
                << " is not among valid values A-" << char('A' + num_vert-1) << "."<< endl;
            return -1;
        }
        char end = end_s.at(0);
        if (end < 'A' || end >= 'A' + num_vert || start == end){
            cerr << "Error: Ending vertex '" << end << "' on line " << line_counter
                << " is not among valid values A-" << char('A' + num_vert-1) << "."<< endl;
            return -1;
        }

        // Weight between Start and End Vertices
        string weight_s;
        ss >> weight_s;
        if (!ss){
            cerr << "Error: Invalid edge data '" << start << " "<< end << "' on line " << line_counter << "."<< endl;
            return -1;
        }
        for (size_t i = 0; i < weight_s.length(); i++){
            if (weight_s.at(i) < '0' || weight_s.at(i) > '9'){
                cerr << "Error: Invalid edge weight '" << weight_s << "' on line " << line_counter << "."<< endl;
                return -1;
            }
        }
        long weight = stol(weight_s);
        if (weight == 0){
            cerr << "Error: Invalid edge weight '" << weight << "' on line " << line_counter << "."<< endl;
            return -1;
        }

        dist_mat[start-'A'][end-'A'] = weight;  // passes error checks populate distance mat with weights
        line_counter++;
    }
    infile.close();
    return num_vert;
}

// Recursively track path taken to get from start to end
// Need to do this because of potential multiple intermediates 
// in one row
void printPath(vector < vector< long double >> path_mat, int i, int j){
    if (path_mat[i][j] == INF){
        // found next step in the path
        cout << " -> " << static_cast<char>(j + 'A');
        return;
    }
    else {
        // Tant to first check in the same row until hit INF meaning
        // thats where we go next
        printPath(path_mat, i, path_mat[i][j]);

        // Then move onto the next row. If traced recursively, backtracks
        // in order of path taken from start to destination
        printPath(path_mat, path_mat[i][j], j);
    }
}

// For printing every possible path through the graph
void display_paths(vector < vector< long double >> &dist_mat, vector < vector< long double >> &path_mat, int num_vert) {
    for (int i = 0; i < num_vert; i++) {
        for (int j = 0; j < num_vert; j++) {
            // First case: j is unreachable from i
            if (dist_mat[i][j] == INF) {
                cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", ";
                cout << "distance: infinity, path: none";
            // Second case: source and dest are the same (pointing to itself)
            } else if (i == j) {
                cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", ";
                cout << "distance: 0, path: " << static_cast<char>(i + 'A');
            // Third case: no intermediate vertices (source points to dest)
            } else if (path_mat[i][j] == INF) {
                cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", ";
                cout << "distance: " << static_cast<long int>(dist_mat[i][j]) << ", path: ";
                cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A');
            // Fourth case: there is at least one intermediate vertex between source and dest
            } else {
                // Cast as necessary, set up
                cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", ";
                cout << "distance: " << static_cast<long int>(dist_mat[i][j]) << ", path: ";
                // Path from vertex i to j (source to dest)
                cout << static_cast<char>(i + 'A');
                // Backtrack until we reach the destination
                printPath(path_mat, i, j);

            }
            cout << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    vector< vector<long double> > dist_mat;
    vector< vector<long double> > path_mat;
    // load initial distance matrix with file from input
    // and initialize the Intermediate Path matrix
    int num_vert = loadfile(argv[1], dist_mat, path_mat);
    if (num_vert == -1) {
        return 1;
    }

    // Passes error checking and dist_mat contains initial distance matrix
    // Can now begin Floyds Algorithm

    display_table(dist_mat, num_vert, "Distance matrix:");

    // turns dist mat into Floyds Mat all pairs shortest path
    floyds(dist_mat, path_mat);
    display_table(dist_mat, num_vert, "Path lengths:");
    display_table(path_mat, num_vert, "Intermediate vertices:", true);
    display_paths(dist_mat, path_mat, num_vert);

    return 0;
}
