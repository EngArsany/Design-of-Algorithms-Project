#include <iostream>
#include <vector>
using namespace std;

void hunt(int lowerLimit, int higherLimit, vector<int> &forwardSequence)
{
    // Base cases
    if (lowerLimit > higherLimit)
        return;
    if (lowerLimit == higherLimit)
    {
        forwardSequence.push_back(lowerLimit);
        return;
    }

    int mid = (lowerLimit + higherLimit) / 2;
    hunt(lowerLimit, mid, forwardSequence);      // conquer left
    hunt(mid + 1, higherLimit, forwardSequence); // conquer right

    // combine: left result + right result (already in order)
}

int main()
{
    cout << "Enter no. of spots (n > 1): ";
    int spots;
    cin >> spots;

    if (spots == 2)
    {
        cout << "sequence: 1 1" << endl;
        cout << "Max shots needed : 2 " << endl;
        return 0;
    }

    vector<int> forwardSequence;
    hunt(2, spots - 1, forwardSequence);
    vector<int> backwardSequence(forwardSequence.rbegin(), forwardSequence.rend());

    cout << "sequence:";
    for (int x : forwardSequence)
        cout << " " << x;
    for (int x : backwardSequence)
        cout << " " << x;
    cout << endl;

    cout << "Max shots needed: " << forwardSequence.size() * 2 << endl;
}