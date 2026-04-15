#include <iostream>
#include <vector>
using namespace std;

void sweep(int l, int r, vector<int> &shots)
{
    if (l > r)
        return;

    if (l == r)
    {
        shots.push_back(l);
        return;
    }

    int mid = (l + r) / 2;
    sweep(l, mid, shots);
    sweep(mid + 1, r, shots);
}

int main()
{
    int n;
    cout << "Enter number of spots:" << endl;
    cin >> n;

    vector<int> shots;

    // Repeat sweep (n-1) times
    for (int i = 0; i < n - 1; i++)
    {
        if (n % 2 == 0)
            sweep(2, n, shots);
        else
            sweep(2, n - 1, shots);
    }
    cout << "Sequence of shots: " << endl;
    for (int x : shots)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}