#include <bits/stdc++.h>
using namespace std;

int targetPosition = 0;

// bool DCAlgorithm(int spots, int currentPosition, bool left)
// {
//     if (spots == 1)
//         return true;

//     // Divide
//     do
//     {
//         DCAlgorithm();
//         DCAlgorithm();
//     } while (!found);

//     // Conquer

// }

bool shotAndFound(int position)
{
    return position == targetPosition;
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

    targetPosition = (moveRight) ? targetPosition + 1 : targetPosition - 1;
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

    // for (int i = 0; i < 10; i++)
    // {
    //     cout << targetPosition << endl;
    //     moveTarget(spots);
    // }

    int currentPosition = 2;
    int minimumPosition = 2;
    int maximumPosition = spots - 1;
    bool moveRight = true;
    vector<int> sequence;
    while (true)
    {
        targetFound = shotAndFound(currentPosition);
        sequence.push_back(currentPosition);

        if (currentPosition == maximumPosition)
        {
            targetFound = shotAndFound(currentPosition);

            moveRight = false;
        }
        else if (currentPosition == minimumPosition)
        {
            targetFound = shotAndFound(currentPosition);

            moveRight = true;
        }

        if (targetFound)
        {
            cout << "targetFound" << endl;
            break;
        }
        currentPosition = moveRight ? currentPosition + 1 : currentPosition - 1;
    }

    cout << "Sequence:" << endl;
    for (auto i : sequence)
        cout << i << endl;
}