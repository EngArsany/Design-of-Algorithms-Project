#include <iostream>
#include <vector>
using namespace std;

void buildForward(int lo, int hi, vector<int> &seq)
{
    if (lo > hi)
        return;
    if (lo == hi)
    {
        seq.push_back(lo);
        return;
    }

    int mid = (lo + hi) / 2;
    buildForward(lo, mid, seq);
    buildForward(mid + 1, hi, seq);
}

void buildBackward(int lo, int hi, vector<int> &seq)
{
    if (lo > hi)
        return;
    if (lo == hi)
    {
        seq.push_back(lo);
        return;
    }

    int mid = (lo + hi) / 2;
    buildBackward(mid + 1, hi, seq);
    buildBackward(lo, mid, seq);
}

int main()
{
    int n;
    cout << "Enter number of hiding spots (n > 1): ";
    cin >> n;

    vector<int> sequence;

    if (n > 2)
    {
        buildForward(2, n - 1, sequence);
        buildBackward(2, n - 1, sequence);
    }

    cout << "Inspection sequence: { ";
    for (int i = 0; i < sequence.size(); i++)
    {
        if (i > 0)
            cout << ", ";
        cout << sequence[i];
    }
    cout << " }" << endl;

    cout << "Max shots needed: " << sequence.size() << endl;

    return 0;
}