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
    int n;
    cout << "Enter no. of holes (n > 1): ";
    cin >> n;

    if (n == 2)
    {
        cout << "sequence: 1 1" << endl;
        cout << "Max shots needed : 2 " << endl;
        return 0;
    }

    vector<int> fwd;
    hunt(2, n - 1, fwd);

    vector<int> bwd(fwd.rbegin(), fwd.rend()); // backward = reverse of forward

    cout << "sequence: ";
    for (int x : fwd)
        cout << " " << x;

    for (int x : bwd)
        cout << " " << x;
    cout << endl;
    cout << "Max shots needed: " << fwd.size() * 2 << endl;

    return 0;
}