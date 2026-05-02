#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MISSING_SQUARE = -1;
const int EMPTY_SQUARE = 0;

void solveDivideAndConquer(vector<vector<int>>& board, int startRow, int startCol, int boardSize, int missRow, int missCol, int& currentId) {
    // base case which is 2x2
    if (boardSize == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                // fill last 3 squares without missing
                if (!(startRow + i == missRow && startCol + j == missCol)) {
                    board[startRow + i][startCol + j] = currentId;
                }
            }
        }
        currentId++;
        return;
    }

    int half = boardSize / 2;
    int centerRow = startRow + half;
    int centerCol = startCol + half;
    int myTrominoId = currentId++;

    // missing square for each quarter
    int nextMissRowTL, nextMissColTL;
    int nextMissRowTR, nextMissColTR;
    int nextMissRowBL, nextMissColBL;
    int nextMissRowBR, nextMissColBR;

    // top left
    if (missRow < centerRow && missCol < centerCol) {
        nextMissRowTL = missRow; nextMissColTL = missCol;
    } else {
        board[centerRow - 1][centerCol - 1] = myTrominoId;
        nextMissRowTL = centerRow - 1; nextMissColTL = centerCol - 1;
    }

    // top right
    if (missRow < centerRow && missCol >= centerCol) {
        nextMissRowTR = missRow; nextMissColTR = missCol;
    } else {
        board[centerRow - 1][centerCol] = myTrominoId;
        nextMissRowTR = centerRow - 1; nextMissColTR = centerCol;
    }

    // bottom left
    if (missRow >= centerRow && missCol < centerCol) {
        nextMissRowBL = missRow; nextMissColBL = missCol;
    } else {
        board[centerRow][centerCol - 1] = myTrominoId;
        nextMissRowBL = centerRow; nextMissColBL = centerCol - 1;
    }

    // bottom right
    if (missRow >= centerRow && missCol >= centerCol) {
        nextMissRowBR = missRow; nextMissColBR = missCol;
    } else {
        board[centerRow][centerCol] = myTrominoId;
        nextMissRowBR = centerRow; nextMissColBR = centerCol;
    }

    // recursion does the job
    solveDivideAndConquer(board, startRow, startCol, half, nextMissRowTL, nextMissColTL, currentId);
    solveDivideAndConquer(board, startRow, centerCol, half, nextMissRowTR, nextMissColTR, currentId);
    solveDivideAndConquer(board, centerRow, startCol, half, nextMissRowBL, nextMissColBL, currentId);
    solveDivideAndConquer(board, centerRow, centerCol, half, nextMissRowBR, nextMissColBR, currentId);
}

bool colorBoardRecursive(vector<vector<int>>& board, vector<int>& assignedColors, int currentTromino, int totalTrominoes) {
    if (currentTromino > totalTrominoes) return true;

    for (int color = 1; color <= 3; color++) {
        bool isSafe = true;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] == currentTromino) {
                    if ((i > 0 && assignedColors[board[i-1][j]] == color) ||
                        (i < board.size()-1 && assignedColors[board[i+1][j]] == color) ||
                        (j > 0 && assignedColors[board[i][j-1]] == color) ||
                        (j < board.size()-1 && assignedColors[board[i][j+1]] == color)) {
                        isSafe = false;
                        break;
                    }
                }
            }
            if (!isSafe) break;
        }

        if (isSafe) {
            assignedColors[currentTromino] = color;
            if (colorBoardRecursive(board, assignedColors, currentTromino + 1, totalTrominoes)) return true;
            assignedColors[currentTromino] = 0;
        }
    }
    return false;
}

void applyColorsToDC(vector<vector<int>>& board, int maxId) {
    vector<int> assignedColors(maxId + 1, 0);
    colorBoardRecursive(board, assignedColors, 1, maxId);
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] != MISSING_SQUARE) {
                board[i][j] = assignedColors[board[i][j]];
            }
        }
    }
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

    // dac
    vector<vector<int>> dcBoard = startGrid;
    int trominoCounter = 1;
    solveDivideAndConquer(dcBoard, 0, 0, boardSize, missR, missC, trominoCounter);
    applyColorsToDC(dcBoard, trominoCounter - 1);
    cout << "Divide and Conquer Result (" << boardSize << "x" << boardSize << ")" << endl;
    printBoard(dcBoard);

    return 0;
}