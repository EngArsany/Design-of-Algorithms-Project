#include <bits/stdc++.h>
using namespace std;

void hunt(int L, int R, vector<int> &sequence)
{
    if (L > R)
        return;

    if (L == R)
    {
        sequence.push_back(L);
        return;
    }

    // DIVIDE
    int mid = (L + R) / 2;

    // CONQUER LEFT: Sweep [L, mid]
    for (int i = L; i <= mid; i++)
        sequence.push_back(i);

    // CONQUER RIGHT: Recurse
    hunt(mid + 1, R, sequence);
}

vector<int> buildSequence(int spots)
{
    vector<int> seq;

    // BASE CASE: n = 2
    if (spots == 2)
    {
        seq = {1, 1};
        return seq;
    }

    // PHASE 1: Covers one parity
    hunt(2, spots - 1, seq);

    // DUMMY SHOT: Shift parity for even n
    if (spots % 2 == 0)
        seq.push_back(1);

    // PHASE 2: Covers other parity
    vector<int> phase2;
    hunt(2, spots - 1, phase2);
    seq.insert(seq.end(), phase2.begin(), phase2.end());

    return seq;
}

// ===== EXHAUSTIVE TESTER =====
bool testFromStart(int start, int spots, vector<int> &sequence)
{
    set<int> possible;
    possible.insert(start);

    for (int t = 0; t < (int)sequence.size(); t++)
    {
        possible.erase(sequence[t]);

        if (possible.empty())
            return true;

        set<int> next;
        for (int p : possible)
        {
            if (p - 1 >= 1)
                next.insert(p - 1);
            if (p + 1 <= spots)
                next.insert(p + 1);
        }
        possible = next;
    }
    return false;
}

bool exhaustiveTest(int spots, vector<int> &sequence)
{
    bool allPass = true;
    for (int start = 1; start <= spots; start++)
    {
        if (!testFromStart(start, spots, sequence))
        {
            cout << "  FAILED for start=" << start << endl;
            allPass = false;
        }
    }
    return allPass;
}

int main()
{
    cout << "===== EXHAUSTIVE TESTING n=2 to n=10 =====" << endl;
    cout << endl;

    for (int spots = 2; spots <= 10; spots++)
    {
        vector<int> seq = buildSequence(spots);

        cout << "n=" << spots << "  Shots=" << seq.size()
             << "  Seq: ";
        for (int s : seq)
            cout << s << " ";
        cout << endl;

        if (exhaustiveTest(spots, seq))
            cout << "  -> ALL STARTING POSITIONS PASS ✅"
                 << endl;
        else
            cout << "  -> FAIL ❌" << endl;

        cout << endl;
    }

    return 0;
}