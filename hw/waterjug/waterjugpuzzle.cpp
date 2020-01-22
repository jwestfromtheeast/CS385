/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Anthony Orrico II and Justin Westley
 * Date        : October 6 2019
 * Description : Computes the output to the Water Jug math puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    bool equals(State other) {
        if (a == other.a && b == other.b && c == other.c) {
            return true;
        }
        return false;
    }
};

// Generate a solution through the linked visited array
vector<string> generate_solution(State &goal, State &start, vector<vector<State>> &visited) {
    vector<string> path;
    // Add current state, and go to parent until you reach the root (ie the start)
    if (start.equals(goal)){               // problem was we save all of the states with directions except goal so 
        path.push_back(goal.to_string());  // push goal from the bfs with saved directions before backtracking
        return path;
    }                       
    path.push_back(goal.directions);      
    while (!visited[goal.a][goal.b].equals(start)) {
        // Go to parent
        path.push_back(visited[goal.a][goal.b].directions);
        goal = visited[goal.a][goal.b];    
    }
    path.push_back(State(start.a, start.b, start.c).to_string());
    return path;
}

// Generate all possible options for what pours you can make given your current water levels
vector<State> generate_moves(State &curr, State &cap) {
    vector<State> moves;
    // If a jug has water, we can move that water to one of the other two jugs
    // However, we must make sure the jug we want to pour into is not full first
    // Create a new state to add to our move list and instantiate it with proper values
    /*** HAVE TO GO IN ORDER C->A, B->A, C->B, A->B, B->C, A->C ***/
    if (curr.c > 0) {   // C->A
        if (curr.a < cap.a) {
            int flow = min(cap.a - curr.a, curr.c);
            State *next = new State(curr.a + flow, curr.b, curr.c - flow);
            if (flow == 1)
                next->directions = "Pour " + to_string(flow) + " gallon from C to A. " + next->to_string();
            else
                next->directions = "Pour " + to_string(flow) + " gallons from C to A. " + next->to_string();
            moves.push_back(*next);
            delete next;
        }
    }
    if (curr.b > 0) {   // B->A
        if (curr.a < cap.a) {
            int flow = min(cap.a - curr.a, curr.b);
            State *next = new State(curr.a + flow, curr.b - flow, curr.c);
            if (flow == 1)
                next->directions = "Pour " + to_string(flow) + " gallon from B to A. " + next->to_string();
            else
                next->directions = "Pour " + to_string(flow) + " gallons from B to A. " + next->to_string();
            moves.push_back(*next);
            delete next;
        }
    }
    if (curr.c > 0){    // C->B
        if (curr.b < cap.b) {
            int flow = min(cap.b - curr.b, curr.c);
            State *next = new State(curr.a, curr.b + flow, curr.c - flow);
            if (flow == 1)
                next->directions = "Pour " + to_string(flow) + " gallon from C to B. " + next->to_string();
            else
                next->directions = "Pour " + to_string(flow) + " gallons from C to B. " + next->to_string();

            moves.push_back(*next);
            delete next;
        }
    }
    if (curr.a > 0) {   // A->B
        if (curr.b < cap.b) {
            int flow = min(cap.b - curr.b, curr.a);
            State *next = new State(curr.a - flow, curr.b + flow, curr.c);
            if (flow == 1)
                next->directions = "Pour " + to_string(flow) + " gallon from A to B. " + next->to_string();
            else
                next->directions = "Pour " + to_string(flow) + " gallons from A to B. " + next->to_string();

            moves.push_back(*next);
            delete next;
        }
    }
    if (curr.b > 0) {   // B->C
        if (curr.c < cap.c) {
            int flow = min(cap.c - curr.c, curr.b);
            State *next = new State(curr.a, curr.b - flow, curr.c + flow);
            if (flow == 1)
                next->directions = "Pour " + to_string(flow) + " gallon from B to C. " + next->to_string();
            else
                next->directions = "Pour " + to_string(flow) + " gallons from B to C. " + next->to_string();
            moves.push_back(*next);
            delete next;
        }
    }
    if (curr.a > 0){    // A->C
        if (curr.c < cap.c) {
            int flow = min(cap.c - curr.c, curr.a);
            State *next = new State(curr.a - flow, curr.b, curr.c + flow);
            if (flow == 1)
                next->directions = "Pour " + to_string(flow) + " gallon from A to C. " + next->to_string();
            else
                next->directions = "Pour " + to_string(flow) + " gallons from A to C. " + next->to_string();
            moves.push_back(*next);
            delete next;
        }
    }
    return moves;
}

// Main function of the puzzle
vector<string> waterjug(State &start, State &goal, State &cap) {
    // Queue to perform our bfs
    queue<State> bfs;
    bfs.push(start);
    State *nullState = new State(-1,-1,-1);
    // Visited array to track parents and avoid cycles
    vector<vector<State>> visited(cap.a+1, vector<State>(cap.b+1, *nullState));
    State curr = *nullState;
    while (!bfs.empty()) {
        // Get the next element in our bfs
        curr = bfs.front();
        bfs.pop();
        // If the current element is our solution, generate the path
        if (curr.equals(goal)) {
            vector<string> solution = generate_solution(curr, start, visited);
            delete nullState;
            return solution;
        }
        // Add all possible moves to the queue that have not yet been tried
        for (auto &next : generate_moves(curr, cap)) {
            if (visited[next.a][next.b].equals(*nullState)){
                bfs.push(next);
                visited[next.a][next.b] = curr;
            }
        }
    }
    // Return something empty here to indicate there is no possible solution, if the bfs fails
    delete nullState;
    vector<string> noSolution;
    noSolution.push_back("No solution.");
    return noSolution;
}

// Converts the shortest path of the tree to a vector of strings for printing the solution
vector<string> solution_to_string(vector<string> &solution) {
    vector<string> solution_string;
    if (solution[0] == "No solution.")
        solution_string.push_back("No solution.");
    else{
        if (solution.size() == 1)       // Start is goal
            solution_string.push_back("Initial state. " + solution[0]);
        else{
            reverse(solution.begin(), solution.end());  // pushing starting from goal makes it backwards
            solution_string.push_back("Initial state. " + solution[0]);
            for (size_t i = 1; i < solution.size(); i++) {
                solution_string.push_back(solution[i]);
            }
        }
    }
    return solution_string;
}

int isValidInput(char * const argv[]){
    // Checks if all inputs are numbers
    for (int i = 1; i < 7; i++){
        if (!isdigit(argv[i][0]))
            return i;
        else if (atoi(argv[i]) == 0 && i <= 3)
            return i;   // capacity cant be 0
    }
    // Checks if a goal is larger than capacity of corresponding jug
    for (int i = 1; i < 4; i++){
        if (atoi(argv[i]) < atoi(argv[i+3]))
            return i+10;
    }
    // Checks if goal total is greater than Jug C Capacity
    if(atoi(argv[3]) != (atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6])))
        return -1;
    return -2;
}

int main(int argc, char * const argv[]) {
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
             << endl;
        return 1;
    }
    int checker = isValidInput(argv);
    if (checker == -1){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C."
             << endl;
        return 1;
    }
    else if (checker >= 0 && checker < 4){
        cerr << "Error: Invalid capacity '" << argv[checker] << "' for jug " << char('A'+checker-1) << "."
             << endl;
        return 1;
    }
    else if (checker > 3 && checker < 10){
        cerr << "Error: Invalid goal '" << argv[checker] << "' for jug " << char('A'+checker-4) << "."
             << endl;
        return 1;
    }
    else if (checker > 10){
        checker = checker%10;
        cerr << "Error: Goal cannot exceed capacity of jug " << char('A'+checker-1) << "."
             << endl;
        return 1;
    } 
    else {
        State *start = new State(0, 0, stoi(argv[3]));
        State *cap = new State(stoi(argv[1]), stoi(argv[2]), stoi(argv[3]));
        State *goal = new State(stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
        vector<string> path = waterjug(*start, *goal, *cap);        // returns vector of string of path in reverse order
        vector<string> solution_string = solution_to_string(path);  // creates printable vector<string>
        if (solution_string.size() == 1){   // if no solution or start == goal no endl
            cout << solution_string[0];
        }
        else{
            for (size_t i = 0; i < solution_string.size()-1; i++){
                cout << solution_string[i]
                     << endl;
            }
            cout << solution_string[solution_string.size()-1];
        }
        delete start; delete cap; delete goal;
    }
    return 0;
}