#include <iostream>
#include <vector>
using namespace std;

pair<vector<int>, vector<int>> hunt(int L, int R)
{
    if (L > R)
        return {{}, {}};
    if (L == R)
        return {{L}, {L}};

    int mid = (L + R) / 2;

    auto [left_fwd, left_bwd] = hunt(L, mid);
    auto [right_fwd, right_bwd] = hunt(mid + 1, R);

    // Combine step
    vector<int> forward, backward;

    for (int x : left_fwd)
        forward.push_back(x);
    for (int x : right_fwd)
        forward.push_back(x);

    for (int x : right_bwd)
        backward.push_back(x);
    for (int x : left_bwd)
        backward.push_back(x);

    return {forward, backward};
}

vector<int> build_sequnce(int n)
{
    if (n <= 2)
        return vector<int>(n, 1);

    auto [fwd, bwd] = hunt(2, n - 1);

    vector<int> result;
    for (int x : fwd)
        result.push_back(x);
    for (int x : bwd)
        result.push_back(x);

    return result;
}

int main()
{
    int n;
    cout << "Enter number of holes (n > 1): ";
    cin >> n;

    vector<int> seq = build_sequnce(n);

    cout << "Inspection sequence: { ";
    for (int i = 0; i < (int)seq.size(); i++)
    {
        if (i > 0)
            cout << ", ";
        cout << seq[i];
    }
    cout << " }" << endl;

    cout << "Max shots needed: " << seq.size() << endl;

    return 0;
}