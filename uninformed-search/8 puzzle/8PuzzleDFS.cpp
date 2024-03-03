// #include <iostream>
// #include <vector>
// #include <unordered_set>
// #include <stack>
// #include <cstring>

// using namespace std;

// // Function to find the position of the empty cell (0) in the board
// void findEmpty(vector<vector<int>>& board, int& x, int& y) {
//     for (int i = 0; i < board.size(); i++) {
//         for (int j = 0; j < board.size(); j++) {
//             if (board[i][j] == 0) {
//                 x = i;
//                 y = j;
//                 return;
//             }
//         }
//     }
// }

// // Function to find adjacent states by swapping the empty cell with its neighbors
// vector<vector<vector<int>>> adjacentFind(vector<vector<int>>& state) {
//     vector<vector<vector<int>>> neighbors;
//     int x = -1;
//     int y = -1;
//     findEmpty(state, x, y);

//     // Possible movements: right, left, up, down
//     int dx[] = {0, 0, -1, 1};
//     int dy[] = {1, -1, 0, 0};
//     for (int i = 0; i < 4; i++) {
//         int newX = x + dx[i];
//         int newY = y + dy[i];

//         if (newX >= 0 && newX < state.size() && newY >= 0 && newY < state.size()) {
//             vector<vector<int>> neighborState = state;
//             swap(neighborState[x][y], neighborState[newX][newY]);
//             neighbors.push_back(neighborState);
//         }
//     }
//     return neighbors;
// }

// // Function to solve the 8-puzzle problem using Depth-First Search (DFS)
// vector<vector<vector<int>>> solveDFS(vector<vector<int>>& initialState, vector<vector<int>>& goal) {
//     unordered_set<string> visited;
//     stack<vector<vector<int>>> stk;
//     stk.push(initialState);

//     stack<vector<vector<vector<int>>>> paths;
//     paths.push({});

//     while (!stk.empty()) {
//         auto currentState = stk.top();
//         stk.pop();

//         auto path = paths.top();
//         paths.pop();

//         if (currentState == goal) {
//             return path;
//         }

//         // Convert the current state to a string for visited set
//         string check = "";
//         for (auto& row : currentState) {
//             for (int num : row) {
//                 check += to_string(num);
//             }
//         }
//         if (visited.find(check) != visited.end()) {
//             continue;
//         }
//         visited.insert(check);

//         // Generate adjacent states and push to stack for DFS
//         for (auto& neighbor : adjacentFind(currentState)) {
//             string neighborNode = "";
//             for (auto& row : neighbor) {
//                 for (int num : row) {
//                     neighborNode += to_string(num);
//                 }
//             }

//             if (visited.find(neighborNode) == visited.end()) {
//                 stk.push(neighbor);
//                 auto newPath = path;
//                 newPath.push_back(neighbor);
//                 paths.push(newPath);
//             }
//         }
//     }
//     return {};
// }

// int main() {
//     vector<vector<int>> initial = {{2, 8, 3},
//                                    {1, 6, 4},
//                                    {7, 0, 5}};

//     vector<vector<int>> goal = {{1, 2, 3},
//                                 {8, 0, 4},
//                                 {7, 6, 5}};

//     auto solution = solveDFS(initial, goal);
//     if (!solution.empty()) {
//         cout << "Solution found:" << endl;
//         for(auto& row : initial) {
//             for(auto& num : row) {
//                 cout << num << " ";
//             }
//             cout << endl;
//         }
//         cout << endl;
//         for (auto& state : solution) {
//             for (auto& row : state) {
//                 for (int num : row) {
//                     cout << num << " ";
//                 }
//                 cout << endl;
//             }
//             cout << endl;
//         }
//     } else {
//         cout << "No solution found." << endl;
//     }

//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

const int N = 3;

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

bool isGoalState(vector<vector<int>>& board, vector<vector<int>>& goal) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void printBoard(vector<vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool dfs(vector<vector<int>>& board, vector<vector<int>>& goal, unordered_set<string>& visited, int x, int y, int prev_x, int prev_y, vector<pair<int, int>>& moves) {
    if (isGoalState(board, goal)) {
        return true;
    }

    string hash = "";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            hash += to_string(board[i][j]) + " ";
        }
    }
    if (visited.find(hash) != visited.end()) {
        return false;
    }

    visited.insert(hash);

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if (isSafe(new_x, new_y) && !(new_x == prev_x && new_y == prev_y)) {
            swap(board[x][y], board[new_x][new_y]);
            moves.push_back({new_x, new_y});
            if (dfs(board, goal, visited, new_x, new_y, x, y, moves)) {
                return true;
            }
            moves.pop_back();
            swap(board[x][y], board[new_x][new_y]);
        }
    }
    return false;
}

int main() {
    vector<vector<int>> initial = {{2, 8, 3},
                                   {1, 6, 4},
                                   {7, 0, 5}};

    vector<vector<int>> goal = {{1, 2, 3},
                                {8, 0, 4},
                                {7, 6, 5}};

    unordered_set<string> visited;
    vector<pair<int, int>> moves;
    int x, y;
    // Finding the position of the blank tile
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] == 0) {
                x = i;
                y = j;
                break;
            }
        }
    }

    if (dfs(initial, goal, visited, x, y, -1, -1, moves)) {
        cout << "Solution Found!\n";
        cout << "Initial Board:\n";
        printBoard(initial);
        cout << "Moves to reach the solution:\n";
        for (auto move : moves) {
            cout << "Move blank tile to (" << move.first << ", " << move.second << ")\n";
        }
    } else {
        cout << "No solution exists!\n";
    }

    return 0;
}
