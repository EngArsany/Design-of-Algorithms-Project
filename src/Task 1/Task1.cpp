#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const int MISSING_SQUARE = -1;
const int EMPTY_SQUARE = 0;

void solveDivideAndConquer(vector<vector<int>>& board, int startRow, int startCol, int boardSize, int missRow, int missCol, int& currentId) {
    // base case which is 2x2
    if (boardSize == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                // Fill the 3 squares that aren't the missing square
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

    // missing close to center
    int missR = boardSize / 2 - 1;
    int missC = boardSize / 2 - 1;

    vector<vector<int>> startGrid(boardSize, vector<int>(boardSize, EMPTY_SQUARE));
    startGrid[missR][missC] = MISSING_SQUARE;

    // dac
    vector<vector<int>> dcBoard = startGrid;
    int trominoCounter = 1;
    solveDivideAndConquer(dcBoard, 0, 0, boardSize, missR, missC, trominoCounter);
    applyColorsToDC(dcBoard, trominoCounter - 1);
    cout << "Divide and Conquer Result (" << boardSize << "x" << boardSize << ")" << endl;
    printBoard(dcBoard);

    // bf
    vector<vector<int>> bfBoard = startGrid;
    cout << endl << "Brute Force Result (" << boardSize << "x" << boardSize << ")" << endl;
    if (solveBruteForce(bfBoard)) {
        printBoard(bfBoard);
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}