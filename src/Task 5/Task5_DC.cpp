#include <iostream>
using namespace std;

void shoot(int position)
{
    cout << "Shoot at position: " << position << endl;
}

void hunt(int l, int r)
{
    if (l == r)
    {
        shoot(l);
        return;
    }

    int mid = (l + r) / 2;

    hunt(l, mid);
    hunt(mid + 1, r);
    hunt(mid + 1, r);
    hunt(l, mid);
}

int main()
{
    int spots;
    cout << "Enter number of spots:" << endl;
    cin >> spots;

    if (spots <= 1)
    {
        cout << "Need at least 2 spots." << endl;
        return 0;
    }

    cout << "\nSequence of shots:\n";
    hunt(1, spots);
    return 0;
}