#include <bits/stdc++.h>
using namespace std;

int targetPosition = 0;

bool shoot(int spots, int currentPosition)
{
    if (spots == 1)
        return true;

    // Divide
    



    // Conquer
}

void moveTarget(int spots)
{
    bool moveRight = rand() % 2;
    // 0 : move left
    // 1 : move right

    // Edge cases (literally)
    if (targetPosition == 1)
        moveRight = true; // move right
    else if (targetPosition == spots)
        moveRight = false; // move left

    targetPosition = (moveRight) ? targetPosition+1 : targetPosition-1;
}

int main()
{
    bool targetFound = false;

    cout << "How many hiding spots? ";
    int spots;
    cin >> spots;

    targetPosition = rand() % spots;
    if (targetPosition == 0)
        targetPosition = 1;

    for (int i = 0; i < 10; i++)
    {
        cout << targetPosition << endl;
        moveTarget(spots);
    }

    // do
    // {
    //     targetFound = shoot();
    //     moveTarget(targetFound, spots);
    // } while (!targetFound);
}