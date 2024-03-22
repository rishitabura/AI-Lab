#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;

void printSolution(map<pair<int, int>, pair<int, int>> mp, pair<int, int>u)
{
    if(u.first == 0 && u.second == 0)
    {
        cout << 0 << " " << 0 << endl;
        return;
    }
    printSolution(mp, mp[u]);
    cout << u.first << " " << u.second << endl;
}

void bfs(int a, int b, int target)
{
    map< pair<int, int>, bool> visited;
    bool canSolve = false;
    map<pair<int, int>, pair<int, int>> mp;
    queue<pair<int, int>> q;

    q.push({0, 0});
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();

        // if already visited skip it
        if (visited[u] == true)
        {
            continue;
        }

        // if out of range skip it
        if (u.first > a || u.second > b || u.first < 0 || u.second < 0)
        {
            continue;
        }

        visited[{u.first, u.second}] = true;

        // if solution found
        // if (u.first == target) // 2nd solution
        if (u.first == target || u.second == target)
        {
            canSolve = true;
            printSolution(mp, u);
            if (u.first == target)
            {
                if (u.second != 0)
                {
                    cout << u.first << " " << 0 << endl;
                }
            }
            else
            {
                if(u.first != 0)
                {
                    cout << 0 << " " << u.second << endl;
                }
                cout << u.second << " " << 0 << endl;
            }
            return;
            
        }
        // fill jug a
        if (visited[{a, u.second}] != true)
        {
            q.push({a, u.second});
            mp[{a, u.second}] = u;
        }

        // fill jug b
        if (visited[{u.first, b}] != true)
        {
            q.push({u.first, b});
            mp[{u.first, b}] = u;
        }

        // empty jug a
        if (visited[{0, u.second}] != true)
        {
            q.push({0, u.second});
            mp[{0, u.second}] = u;
        }

        // empty jug b
        if (visited[{u.first, 0}] != true)
        {
            q.push({u.first, 0});
            mp[{u.first, 0}] = u;
        }

        // transfer a to b
        int x = b - u.second;
        if (u.first >= x)
        {
            int c = u.first - x;
            if (visited[{c, b}] != true)
            {
                q.push({c, b});
                mp[{c, b}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (visited[{0, c}] != true)
            {
                q.push({0, c});
                mp[{0, c}] = u;
            }
        }

        // transfer b to a
        x = a - u.first;
        if (u.second >= x)
        {
            int c = u.second - x;
            if (visited[{a, c}] != true)
            {
                q.push({a, c});
                mp[{a, c}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (visited[{c, 0}] != true)
            {
                q.push({c, 0});
                mp[{c, 0}] = u;
            }
        }
    }
    if(!canSolve)
    {
        cout << "No solution";
    }
    return;
}

int main()
{
    int a = 4;
    int b = 3;
    int target = 2;
    cout << "Water jug problem using BFS :" << endl;
    bfs(a, b, target);

    return 0;
}
