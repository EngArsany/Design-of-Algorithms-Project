#include <iostream>
#include <vector>
using namespace std;

void sweepDouble(int l, int r, vector<int> &shots)
{
    if (l > r)
        return;

    if (l == r)
    {
        shots.push_back(l);
        shots.push_back(l);
        return;
    }

    int mid = (l + r) / 2;
    sweepDouble(l, mid, shots);
    sweepDouble(mid + 1, r, shots);
}

int main()
{
    int n;
    cin >> n;

    vector<int> shots;

    sweepDouble(2, n - 1, shots);

    for (int x : shots)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}