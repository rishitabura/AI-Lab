#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Define a state representation for the N-Queens problem
struct State {
    vector<int> queens; // queens[i] represents the column position of the queen in row i
    int cost; // Total cost from start to current state
    int heuristic; // Heuristic value (number of attacking queen pairs)

    State(const vector<int>& q, int c, int h) : queens(q), cost(c), heuristic(h) {}

    // Overload the less than operator for priority queue ordering
    bool operator<(const State& other) const {
        return cost + heuristic > other.cost + other.heuristic; // Total cost + heuristic
    }
};

// Calculate the heuristic value (number of attacking queen pairs)
int calculateHeuristic(const vector<int>& queens) {
    int heuristic = 0;
    int n = queens.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Check for attacking pairs in the same row or diagonally
            if (queens[i] == queens[j] || abs(queens[i] - queens[j]) == abs(i - j)) {
                heuristic++;
            }
        }
    }

    return heuristic;
}

// A* algorithm to solve N-Queens
bool solveNQueens(int n) {
    priority_queue<State> pq;
    vector<int> initialQueens(n, 0);
    pq.push(State(initialQueens, 0, calculateHeuristic(initialQueens)));

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.heuristic == 0) {
            // Solution found
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << (current.queens[i] == j ? "Q" : ".");
                }
                cout << endl;
            }
            return true;
        }

        // Generate next states by moving one queen at a time
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (current.queens[i] != j) {
                    vector<int> nextQueens = current.queens;
                    nextQueens[i] = j;
                    int cost = current.cost + 1; // Cost for moving one queen
                    int heuristic = calculateHeuristic(nextQueens);
                    pq.push(State(nextQueens, cost, heuristic));
                }
            }
        }
    }

    // No solution found
    return false;
}

int main() {
    int n;
    cout << "Enter the number of queens (N): ";
    cin >> n;

    if (solveNQueens(n)) {
        cout << "Solution found!" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
