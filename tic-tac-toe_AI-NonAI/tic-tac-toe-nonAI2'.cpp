#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
using namespace std;

int board[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int track[10] = {-1, 8, 3, 4, 1, 5, 9, 6, 7, 2};
list<pair<char, int>> playedList;
int turn;

void GO(int n)
{
    if (turn % 2 == 0)
    {
        board[n] = 5;
        playedList.push_back(make_pair('O', track[n]));
    }
    else
    {
        board[n] = 3;
        playedList.push_back(make_pair('X', track[n]));
    }
    turn++;
}

int posswin(int p)
{
    for (auto it1 = playedList.begin(); it1 != playedList.end(); ++it1)
    {
        for (auto it2 = next(it1); it2 != playedList.end(); ++it2)
        {
            if (it1->first == it2->first)
            {
                // Check if the condition for player A or B is met
                if ((p == 1 && it1->first == 'A') || (p == 0 && it1->first == 'B'))
                {
                    int pairSum = it1->second + it2->second;
                    // cout << "Combination: " << it1->first << " + " << it2->first
                    //           << " = " << pairSum << endl;
                    int diff = 15 - pairSum;
                    if (pairSum > 0 || pairSum < 9)
                    {
                        break;
                    }
                    else
                    {
                        bool check = checkBlank(arr[6]);
                    }
                    
                }
            }
        }
    }
}

int main()
{

    return 0;
}