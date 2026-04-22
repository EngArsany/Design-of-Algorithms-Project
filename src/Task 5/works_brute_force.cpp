#include <iostream>
#include <vector>
using namespace std;

vector<int> generateSequence(int n)
{
    vector<int> sequence;

    // Forward: 2, 3, ..., N-1
    for (int i = 2; i <= n - 1; i++)
        sequence.push_back(i);

    // Backward: N-1, ..., 2
    for (int i = n - 1; i >= 2; i--)
        sequence.push_back(i);

    return sequence;
}

int main()
{
    int n;

    cout << "Enter number of holes (n >= 3): ";
    cin >> n;

    vector<int> sequence = generateSequence(n);

    cout << "Inspection sequence: { ";
    for (int i = 0; i < (int)sequence.size(); i++)
    {
        if (i > 0)
            cout << ", ";
        cout << sequence[i];
    }
    cout << " }" << endl;

    cout << "Max days needed: " << sequence.size() << endl;

    return 0;
}