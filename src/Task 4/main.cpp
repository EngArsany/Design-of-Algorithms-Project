#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

static const int NUMBER_OF_ROWS = 4;
static const int NUMBER_OF_COLS = 3;
static const int EMPTY_CELL   = 0;
static const int WHITE_KNIGHT = 1;
static const int BLACK_KNIGHT = 2;

static const int ROW_CHANGE[8] = { -2, -2, -1, -1, +1, +1, +2, +2 };
static const int COL_CHANGE[8] = { -1, +1, -2, +2, -2, +2, -1, +1 };

struct BoardState {
    int cell[NUMBER_OF_ROWS][NUMBER_OF_COLS];

    long long encode() const {
        long long uniqueNumber = 0;
        for (int row = 0; row < NUMBER_OF_ROWS; row++)
            for (int col = 0; col < NUMBER_OF_COLS; col++)
                uniqueNumber = uniqueNumber * 3 + cell[row][col];
        return uniqueNumber;
    }

    bool operator==(const BoardState& other) const {
        for (int row = 0; row < NUMBER_OF_ROWS; row++)
            for (int col = 0; col < NUMBER_OF_COLS; col++)
                if (cell[row][col] != other.cell[row][col])
                    return false;
        return true;
    }
};

BoardState buildStartingBoard() {
    BoardState board;
    for (int row = 0; row < NUMBER_OF_ROWS; row++)
        for (int col = 0; col < NUMBER_OF_COLS; col++)
            board.cell[row][col] = EMPTY_CELL;
    board.cell[0][0] = BLACK_KNIGHT;
    board.cell[0][1] = BLACK_KNIGHT;
    board.cell[0][2] = BLACK_KNIGHT;
    board.cell[3][0] = WHITE_KNIGHT;
    board.cell[3][1] = WHITE_KNIGHT;
    board.cell[3][2] = WHITE_KNIGHT;
    return board;
}

BoardState buildGoalBoard() {
    BoardState board;
    for (int row = 0; row < NUMBER_OF_ROWS; row++)
        for (int col = 0; col < NUMBER_OF_COLS; col++)
            board.cell[row][col] = EMPTY_CELL;
    board.cell[0][0] = WHITE_KNIGHT;
    board.cell[0][1] = WHITE_KNIGHT;
    board.cell[0][2] = WHITE_KNIGHT;
    board.cell[3][0] = BLACK_KNIGHT;
    board.cell[3][1] = BLACK_KNIGHT;
    board.cell[3][2] = BLACK_KNIGHT;
    return board;
}

void printBoard(const BoardState& board, const std::string& label = "") {
    if (!label.empty())
        std::cout << "  " << label << "\n";
    std::cout << "    +---+---+---+\n";
    for (int row = 0; row < NUMBER_OF_ROWS; row++) {
        std::cout << "    |";
        for (int col = 0; col < NUMBER_OF_COLS; col++) {
            char symbol = ' ';
            if (board.cell[row][col] == WHITE_KNIGHT) symbol = 'W';
            if (board.cell[row][col] == BLACK_KNIGHT) symbol = 'B';
            std::cout << " " << symbol << " |";
        }
        std::cout << "\n    +---+---+---+\n";
    }
    std::cout << "\n";
}

std::vector<BoardState> findAllNextMoves(const BoardState& currentBoard) {
    std::vector<BoardState> possibleNextBoards;
    for (int row = 0; row < NUMBER_OF_ROWS; row++) {
        for (int col = 0; col < NUMBER_OF_COLS; col++) {
            if (currentBoard.cell[row][col] == EMPTY_CELL)
                continue;
            int thisKnight = currentBoard.cell[row][col];
            for (int moveIndex = 0; moveIndex < 8; moveIndex++) {
                int destinationRow = row + ROW_CHANGE[moveIndex];
                int destinationCol = col + COL_CHANGE[moveIndex];
                bool rowIsValid = (destinationRow >= 0 && destinationRow < NUMBER_OF_ROWS);
                bool colIsValid = (destinationCol >= 0 && destinationCol < NUMBER_OF_COLS);
                if (!rowIsValid || !colIsValid)
                    continue;
                bool destinationIsEmpty = (currentBoard.cell[destinationRow][destinationCol] == EMPTY_CELL);
                if (!destinationIsEmpty)
                    continue;
                BoardState boardAfterMove = currentBoard;
                boardAfterMove.cell[row][col] = EMPTY_CELL;
                boardAfterMove.cell[destinationRow][destinationCol] = thisKnight;
                possibleNextBoards.push_back(boardAfterMove);
            }
        }
    }
    return possibleNextBoards;
}

std::vector<BoardState> solveWithBFS(const BoardState& startBoard, const BoardState& goalBoard) {
    long long goalCode  = goalBoard.encode();
    long long startCode = startBoard.encode();

    std::unordered_map<long long, long long> parentOf;
    std::unordered_map<long long, BoardState> boardOf;

    parentOf[startCode] = -1;
    boardOf[startCode]  = startBoard;

    std::queue<BoardState> statesToExplore;
    statesToExplore.push(startBoard);

    while (!statesToExplore.empty()) {
        BoardState currentBoard = statesToExplore.front();
        statesToExplore.pop();
        long long currentCode = currentBoard.encode();

        if (currentCode == goalCode) {
            std::vector<BoardState> solutionPath;
            long long code = goalCode;
            while (code != -1) {
                solutionPath.push_back(boardOf[code]);
                code = parentOf[code];
            }
            std::reverse(solutionPath.begin(), solutionPath.end());
            return solutionPath;
        }

        for (const BoardState& nextBoard : findAllNextMoves(currentBoard)) {
            long long nextCode = nextBoard.encode();
            bool alreadyVisited = (parentOf.find(nextCode) != parentOf.end());
            if (!alreadyVisited) {
                parentOf[nextCode] = currentCode;
                boardOf[nextCode]  = nextBoard;
                statesToExplore.push(nextBoard);
            }
        }
    }

    return {};
}

int main() {
    BoardState startBoard = buildStartingBoard();
    BoardState goalBoard  = buildGoalBoard();

    std::vector<BoardState> solutionPath = solveWithBFS(startBoard, goalBoard);

    int totalMoves = (int)solutionPath.size() - 1;

    for (int step = 0; step < (int)solutionPath.size(); step++) {
        if (step == 0)
            std::cout << "  Initial\n";
        else
            std::cout << "  Move " << step << "\n";
        printBoard(solutionPath[step]);
    }

    std::cout << "Total moves: " << totalMoves << "\n";

    return 0;
}

