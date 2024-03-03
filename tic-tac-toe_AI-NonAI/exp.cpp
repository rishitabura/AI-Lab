#include <bits/stdc++.h>
#include <vector>
using namespace std;

int board[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
int turn;

void GO(int n)
{
    // cout << "turn : " << turn << endl;
    if (turn % 2 == 0)
    {
        board[n] = 5;
    }
    else
    {
        board[n] = 3;
    }
    turn++;
}

void Make2()
{
    int move = 0;

    if (board[5] == 2)
    {
        move = 5;
    }
    else
    {
        for (int i = 2; i <= 8; i += 2)
        {
            if (board[i] == 2)
            {
                move = i;
                break;
            }
        }
    }
    if (move == 0)
    {
        for (int i = 1; i <= 9; i++)
        {
            if (board[i] == 2)
            {
                move = i;
                break;
            }
        }
    }

    GO(move);
}

int posswin(int p)
{
    int target;
    if (p == 1)
    {
        target = 18;
    }
    else if (p == 0)
    {
        target = 50;
    }
    // row check
    for (int i = 1; i <= 7; i += 3)
    {
        // cout << "ans row : " << board[i] * board[i + 1] * board[i + 2] << endl;
        if (board[i] * board[i + 1] * board[i + 2] == target)
        {
            if (board[i] == 2)
            {
                return i;
            }
            else if (board[i + 1] == 2)
            {
                return i + 1;
            }
            else
            {
                return i + 2;
            }
        }
    }
    // column check
    for (int i = 1; i <= 3; i++)
    {
        // cout << "ans col: " << board[i] * board[i + 3] * board[i + 6] << endl;

        if (board[i] * board[i + 3] * board[i + 6] == target)
        {
            if (board[i] == 2)
            {
                return i;
            }
            else if (board[i + 3] == 2)
            {
                return i + 3;
            }
            else
            {
                return i + 6;
            }
        }
    }
    // left diagonal
    if (board[1] * board[5] * board[9] == target)
    {
        if (board[1] == 2)
        {
            return 1;
        }
        if (board[5] == 2)
        {
            return 5;
        }
        else
        {
            return 9;
        }
    }
    // right diagonal
    if (board[3] * board[5] * board[7] == target)
    {
        if (board[3] == 2)
        {
            return 3;
        }
        if (board[5] == 2)
        {
            return 5;
        }
        else
        {
            return 7;
        }
    }
    return 0;
}

void printBoard()
{
    for (int i = 1; i <= 9; i++)
    {
        if (i % 3 != 0)
            cout << board[i] << " ";
        else
            cout << board[i] << endl;
    }
    cout << "______________\n";
}

void TicTacToe()
{
    while (turn <= 9)
    {
        cout << "Turn " << turn << endl;

        // X's turn
        if (turn % 2 == 1)
        {
            cout << "Player X turn - user " << endl;
            cout << "Make a move bet 1 to 9 : ";
            int hmove;
            cin >> hmove;
            GO(hmove);
        }
        // O's turn
        else
        {
            cout << "Player O turn - computer" << endl;
            Make2();
        }

        int winner = posswin((turn % 2 == 1) ? 1 : 0);
        
        if (winner != 0)
        {
            printBoard();
            if (turn % 2 == 1)
            {
                cout << "Player X-user wins" << endl;
                return;
            }
            else
            {
                cout << "Player O-computer wins" << endl;
                return;
            }
            
        }
        printBoard();
    }
}

int main()
{
    turn = 1;
    cout << "Before" << endl;
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << board[i] << " ";
    // }
    // cout << endl;
    printBoard();
    while (turn <= 9)
    {
        TicTacToe();
    }

    // for (int i = 1; i <= 10; i++)
    // {
    //     cout << board[i] << " ";
    // }

    return 0;
}