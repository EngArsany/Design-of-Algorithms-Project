#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MISSING_SQUARE = -1;
const int EMPTY_SQUARE = 0;

// for adjacent color validation
bool isColorValid(const vector<vector<int>>& board, int r, int c, int colorChoice) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < board.size() && nc >= 0 && nc < board.size()) {
            if (board[nr][nc] == colorChoice) return false;
        }
    }
    return true;
}

bool solveBruteForce(vector<vector<int>>& board) {
    int boardSize = board.size();
    int targetRow = -1, targetCol = -1;

    // looking for first empty
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == EMPTY_SQUARE) {
                targetRow = i; targetCol = j;
                break;
            }
        }
        if (targetRow != -1) break;
    }

    if (targetRow == -1) return true;

    // tromino orient
    int shapes[4][2][2] = {
        {{0, 1}, {1, 0}}, {{0, 1}, {1, 1}}, 
        {{1, 0}, {1, 1}}, {{1, 0}, {1, -1}}
    };

    for (int i = 0; i < 4; i++) {
        int r2 = targetRow + shapes[i][0][0], c2 = targetCol + shapes[i][0][1];
        int r3 = targetRow + shapes[i][1][0], c3 = targetCol + shapes[i][1][1];

        if (r2 >= 0 && r2 < boardSize && c2 >= 0 && c2 < boardSize && board[r2][c2] == EMPTY_SQUARE &&
            r3 >= 0 && r3 < boardSize && c3 >= 0 && c3 < boardSize && board[r3][c3] == EMPTY_SQUARE) {
            
            // test all 3 colors
            for (int color = 1; color <= 3; color++) {
                if (isColorValid(board, targetRow, targetCol, color) && 
                    isColorValid(board, r2, c2, color) && 
                    isColorValid(board, r3, c3, color)) {
                    
                    board[targetRow][targetCol] = board[r2][c2] = board[r3][c3] = color;
                    if (solveBruteForce(board)) return true;
                    board[targetRow][targetCol] = board[r2][c2] = board[r3][c3] = EMPTY_SQUARE; // backtracking
                }
            }
        }
    }
    return false;
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int val : row) {
            if (val == MISSING_SQUARE) cout << setw(4) << "X";
            else cout << setw(4) << val;
        }
        cout << endl;
    }
}

int main() {
    int n = 4; // change this, 5 will probably not even finish for bf
    int boardSize = pow(2, n);
    int missR, missC;

    bool randomizeMissing = true; // set to true to randomize missing coord

    if (randomizeMissing) {
        srand(time(0));
        missR = rand() % boardSize;
        missC = rand() % boardSize;
    } else {
        // missing close to center
        missR = boardSize / 2 - 1;
        missC = boardSize / 2 - 1;
    }

    vector<vector<int>> startGrid(boardSize, vector<int>(boardSize, EMPTY_SQUARE));
    startGrid[missR][missC] = MISSING_SQUARE;

    // bf
    vector<vector<int>> bfBoard = startGrid;
    cout << "Brute Force Result (" << boardSize << "x" << boardSize << ")" << endl;
    if (solveBruteForce(bfBoard)) {
        printBoard(bfBoard);
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}