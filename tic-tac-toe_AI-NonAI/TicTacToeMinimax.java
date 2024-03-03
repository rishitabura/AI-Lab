import java.util.Scanner;

public class TicTacToeMinimax {

    public static void main(String[] args) {
        char[][] board = {
                {' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}
        };

        playGame(board);
    }

    static void printBoard(char[][] board) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                System.out.print(board[i][j]);
                if (j < 2) {
                    System.out.print(" | ");
                }
            }
            System.out.println();
            if (i < 2) {
                System.out.println("---------");
            }
        }
        System.out.println();
    }

    static boolean isMovesLeft(char[][] board) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return true;
                }
            }
        }
        return false;
    }

    static int evaluate(char[][] board) {
        // Check rows, columns, and diagonals for a win
        // Return +10 for player win, -10 for AI win, 0 for a draw
        // You can customize the evaluation based on your game's logic
        return 0;
    }

    static int minimax(char[][] board, int depth, boolean isMax) {
        int score = evaluate(board);

        if (score == 10) {
            return score;
        }
        if (score == -10) {
            return score;
        }
        if (!isMovesLeft(board)) {
            return 0;
        }

        if (isMax) {
            int best = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X';
                        best = Math.max(best, minimax(board, depth + 1, !isMax));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        best = Math.min(best, minimax(board, depth + 1, !isMax));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
    }

    static Move findBestMove(char[][] board) {
        int bestVal = -1000;
        Move bestMove = new Move(-1, -1);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int moveVal = minimax(board, 0, false);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        return bestMove;
    }

    static void playGame(char[][] board) {
        Scanner scanner = new Scanner(System.in);

        while (isMovesLeft(board)) {
            printBoard(board);

            Move bestMove = findBestMove(board);
            board[bestMove.row][bestMove.col] = 'X';

            if (evaluate(board) == 10) {
                printBoard(board);
                System.out.println("You lose!");
                break;
            }

            if (!isMovesLeft(board)) {
                printBoard(board);
                System.out.println("It's a draw!");
                break;
            }

            printBoard(board);
            System.out.println("Your move (row [0-2] and column [0-2]): ");
            int row = scanner.nextInt();
            int col = scanner.nextInt();

            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                board[row][col] = 'O';
            } else {
                System.out.println("Invalid move. Try again.");
                continue;
            }

            if (evaluate(board) == -10) {
                printBoard(board);
                System.out.println("You win!");
                break;
            }
        }

        scanner.close();
    }

    static class Move {
        int row, col;

        Move(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }
}