#include <iostream>
#include <vector>
using namespace std;

void hunt(int l, int h, vector<int> &fwd)
{
    if (l > h)
        return;
    if (l == h)
    {
        fwd.push_back(l);
        return;
    }

    int mid = (l + h) / 2;
    hunt(l, mid, fwd);     // conquer left
    hunt(mid + 1, h, fwd); // conquer right
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
    vector<int> backwardSequence(forwardSequence.rbegin(), forwardSequence.rend()); // backward = reverse of forward

    cout << "sequence:";
    for (int x : forwardSequence)
        cout << " " << x;
    for (int x : backwardSequence)
        cout << " " << x;
    cout << endl;

    cout << "Max shots needed: " << forwardSequence.size() * 2 << endl;
}