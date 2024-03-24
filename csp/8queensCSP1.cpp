#include <iostream>
#include <vector>

using namespace std;

// const int N = 4;
int solutionCount = 0;


bool isSafe(int N, vector<vector<int>> &board, int row, int col)
{
    for (int x = 0; x < col; x++)
        if (board[row][x] == 1)
            return false;
    for (int x = row, y = col; x >= 0 && y >= 0; x--, y--)
        if (board[x][y] == 1)
            return false;
    for (int x = row, y = col; x < N && y >= 0; x++, y--)
        if (board[x][y] == 1)
            return false;
    return true;
}

printSolution(int N, vector<vector<int>> &board)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            if (board[i][j] == 1)
            {
                cout << "Q" << i << "\t";
            }
            else
            {
                cout  << ".\t";
            }
            
        cout << endl;
    }
    cout << endl;

}

void solveNQueens(int N, vector<vector<int>> &board, int col)
{
    if(col >= N) return;
   
    for (int i = 0; i < N; i++)
    {
        if (isSafe(N, board, i, col))
        {
            board[i][col] = 1;
            if (col == N-1)
            {
                cout << "Soultion " << solutionCount+1 << endl ;
                printSolution(N, board);
                solutionCount++;
            }
            solveNQueens(N, board, col+1);
            board[i][col] = 0;
        }
    }
}

int main()
{
    int N;
    cout << "Enter the number of queens : ";
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N, 0));
    solveNQueens(N,board,0);
    cout << "Total solutions : " << solutionCount;
    return 0;
}