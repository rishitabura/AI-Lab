#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <queue>
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

vector<State> bfs(State &InitialState, State &GoalState)
{
    if(!isValid(InitialState))
    {
        return {};
    }

    unordered_set<int> visited;
    queue<vector<State>> q;
    q.push({InitialState});

    while (!q.empty())
    {
        vector<State> path = q.front();
        q.pop();
        State currentState = path.back();

        // check for visited or not
        int hashValue = currentState[0][0] * 10000 + currentState[0][1] * 1000 + currentState[0][2] * 100 +
                        currentState[1][0] * 10 + currentState[1][1];
        if (visited.find(hashValue) != visited.end())
            continue;

        visited.insert(hashValue);

        // goal reached
        if (currentState[0][0] == 0 && currentState[0][1] == 0 && currentState[0][2] == 0)
        {
            return path;
        }

        for (auto &successor : getSuccessor(currentState))
        {
            vector<State> newPath = path;
            newPath.push_back(successor);
            q.push(newPath);
        }
    }

    return {};
}

void printSolution(vector<State>& solution) {

    for (size_t i = 0; i < solution.size(); ++i) {
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

    vector<State> solution = bfs(InitialState, GoalState);
    cout << "Missionaries and Cannibals Problem using BFS : " << endl;

    if (solution.empty())
    {
        cout << "No solution" << endl;
    }
    else
    {
        cout << "Solution found" << endl;
        printSolution(solution);
    }
    

    return 0;
}