#include <iostream>
using namespace std;

int n;
int board[100][100];

int dx[8] = {2, 1, -1, -2, -2, -1,  1,  2};
int dy[8] = {1, 2,  2,  1, -1, -2, -2, -1};

bool isValid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

int countOnward(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(x + dx[i], y + dy[i]))
            count++;
    }
    return count;
}

int GreedyAlgo(int startX, int startY) {

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = -1;

    int x = startX;
    int y = startY;
    board[x][y] = 0;

    int moves = 0;

    for (int step = 1; step < n * n; step++) {

        int minDegree = 9;
        int nextX = -1;
        int nextY = -1;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny)) {
                int degree = countOnward(nx, ny);
                if (degree < minDegree) {
                    minDegree = degree;
                    nextX = nx;
                    nextY = ny;
                }
            }
        }

        if (nextX == -1)
            return moves;   // return moves done so far

        x = nextX;
        y = nextY;
        board[x][y] = step;
        moves++;
    }

    return moves;   // should be n*n - 1 if full tour
}

int main() {
    cout << "Enter board size n: ";
    cin >> n;

    int startX, startY;
    cout << "Enter start row (0 to " << n-1 << "): ";
        cin >> startX;

    cout << "Enter start col (0 to " << n-1 << "): ";

    cin >> startY;

    // Closed tour condition
    if (n >= 6 && n % 2 == 0)
        cout << "Closed Tour: YES\n";
    else
        cout << "Closed Tour: NO\n";

    int moves = GreedyAlgo(startX, startY);

    cout << "Minimum Moves: " << moves << endl;

    return 0;
}
