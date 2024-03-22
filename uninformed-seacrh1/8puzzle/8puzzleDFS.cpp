#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cstring>
using namespace std;

void findEmpty(vector<vector<int>> board, int &x, int &y)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}

vector<vector<vector<int>>> adjacentFind(vector<vector<int>> &state)
{
    vector<vector<vector<int>>> neighbors;
    int x = -1;
    int y = -1;
    findEmpty(state, x, y);

    // right, left, up, down
    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < state.size() && newY >= 0 && newY < state.size())
        {
            vector<vector<int>> neighbourState = state;
            swap(neighbourState[x][y], neighbourState[newX][newY]);
            neighbors.push_back(neighbourState);
        }
    }
    return neighbors;
}

vector<vector<vector<int>>> solve(vector<vector<int>> &initalState, vector<vector<int>> &goal)
{
    unordered_set<string> visited;
    queue<vector<vector<int>>> q;
    q.push(initalState);

    queue<vector<vector<vector<int>>>> paths;
    paths.push({});

    while (!q.empty())
    {
        auto currentState = q.front();
        q.pop();

        auto path = paths.front();
        paths.pop();

        if (currentState == goal)
        {
            return path;
        }

        string check = "";
        for (auto &row : currentState)
        {
            for (int num : row)
            {
                check += to_string(num);
            }
        }
        if (visited.find(check) != visited.end())
        {
            continue;
        }
        visited.insert(check);

        for (auto neighbour : adjacentFind(currentState))
        {
            string neighbourNode = "";
            for (auto &row : neighbour)
            {
                for (int num : row)
                {
                    neighbourNode += to_string(num);
                }
            }

            if (visited.find(neighbourNode) == visited.end())
            {
                q.push(neighbour);
                auto newPath = path;
                newPath.push_back(neighbour);
                paths.push(newPath);
            }
        }
    }
    return {};
}

int main()
{
    vector<vector<int>> initial = {{2, 8, 3},
                                   {1, 6, 4},
                                   {7, 0, 5}};

    vector<vector<int>> goal = {{1, 2, 3},
                                {8, 0, 4},
                                {7, 6, 5}};

    auto solution = solve(initial, goal);
    if (!solution.empty())
    {
        cout << "Solution found:" << endl;
        for(auto &row :initial)
        {
            for(auto &num : row)
            {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << endl;
        for (auto &state : solution)
        {
            for (auto &row : state)
            {
                for (int num : row)
                {
                    cout << num << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution found." << endl;
    }

    return 0;
}