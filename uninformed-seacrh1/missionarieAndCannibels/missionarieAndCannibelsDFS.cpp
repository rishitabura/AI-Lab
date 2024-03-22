#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

using State = vector<vector<int>>;

bool isValid(State &state)
{
    int ml = state[0][0];
    int cl = state[0][1];
    int bl = state[0][2];

    int mr = state[1][0];
    int cr = state[1][1];
    int br = state[1][2];

    if (ml < 0 || cl < 0 || mr < 0 || cr < 0)
    {
        return false;
    }

    if (ml > 0 && ml < cl || mr > 0 && mr < cr)
    {
        return false;
    }

    return true;
}

vector<State> getSuccessor(State &state)
{
    vector<State> Successors;

    // boat on left
    if (state[0][2] == 1)
    {
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 2; ++j)
            {
                if (i + j > 0 && i + j <= 2)
                {
                    State successor = {
                        {state[0][0] - i, state[0][1] - j, 0},
                        {state[1][0] + i, state[1][1] + j, 1}};

                    if (isValid(successor))
                    {
                        Successors.push_back(successor);
                    }
                }
            }
        }
    }
    // boat on right
    else
    {
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 2; ++j)
            {
                if (i + j > 0 && i + j <= 2)
                {
                    State successor = {
                        {state[0][0] + i, state[0][1] + j, 1},
                        {state[1][0] - i, state[1][1] - j, 0}};

                    if (isValid(successor))
                    {
                        Successors.push_back(successor);
                    }
                }
            }
        }
    }

    return Successors;
}

bool dfs(State &currentState, State &GoalState, unordered_set<int> &visited, vector<State> &path)
{
    // goal reached
    if (currentState == GoalState)
    {
        // path.push_back(currentState);
        return true;
    }

    for (auto &successor : getSuccessor(currentState))
    {
        int hashValue = successor[0][0] * 10000 + successor[0][1] * 1000 + successor[0][2] * 100 +
                        successor[1][0] * 10 + successor[1][1];
        if (visited.find(hashValue) == visited.end())
        {
            visited.insert(hashValue);
            path.push_back(successor);

            if (dfs(successor, GoalState, visited, path))
                return true;

            path.pop_back();
        }
    }

    return false;
}

void printSolution(vector<State> &solution)
{
    for (size_t i = 0; i < solution.size(); ++i)
    {
        cout << "At depth " << i << ": Left Side: ("
             << solution[i][0][0] << ", " << solution[i][0][1] << ", " << solution[i][0][2]
             << "), Right Side: (" << solution[i][1][0] << ", " << solution[i][1][1] << ", "
             << solution[i][1][2] << ")" << endl;
    }
}

int main()
{
    State InitialState = {{3, 3, 1}, {0, 0, 0}};
    State GoalState = {{0, 0, 0}, {3, 3, 1}};

    vector<State> path;
    unordered_set<int> visited;
    path.push_back(InitialState);
    visited.insert(InitialState[0][0] * 10000 + InitialState[0][1] * 1000 + InitialState[0][2] * 100 +
                   InitialState[1][0] * 10 + InitialState[1][1]);

    cout << "Missionaries and Cannibals Problem using DFS : " << endl;
    if (dfs(InitialState, GoalState, visited, path))
    {
        cout << "Solution found" << endl;
        printSolution(path);
    }
    else
    {
        cout << "No solution" << endl;
    }

    return 0;
}

