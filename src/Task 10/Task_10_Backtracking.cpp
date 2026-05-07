#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool solve(string &state, vector<int> &path, vector<bool> &removed, int coins_left)
{
    if (coins_left == 0)
        return true;

    int n = state.length();
    for (int i = 0; i < n; i++)
    {
        if (!removed[i] && state[i] == 'H')
        {
            // Remove the coin at position i
            removed[i] = true;
            path.push_back(i + 1);

            // Flip immediate left neighbor if it still exists
            if (i - 1 >= 0 && !removed[i - 1])
            {
                state[i - 1] = (state[i - 1] == 'H') ? 'T' : 'H';
            }

            // Flip immediate right neighbor if it still exists
            if (i + 1 < n && !removed[i + 1])
            {
                state[i + 1] = (state[i + 1] == 'H') ? 'T' : 'H';
            }

            // Recurse
            if (solve(state, path, removed, coins_left - 1))
                return true;

            // Backtrack
            if (i + 1 < n && !removed[i + 1])
            {
                state[i + 1] = (state[i + 1] == 'H') ? 'T' : 'H';
            }
            if (i - 1 >= 0 && !removed[i - 1])
            {
                state[i - 1] = (state[i - 1] == 'H') ? 'T' : 'H';
            }
            removed[i] = false;
            path.pop_back();
        }
    }
    return false;
}

int main()
{
    vector<string> test_cases = {"HTTHHTTHTHHHHTTTHHHHHTHHH"};
    for (size_t i = 0; i < test_cases.size(); i++)
    {
        string s = test_cases[i];
        vector<int> path;
        vector<bool> removed(s.length(), false);
        if (solve(s, path, removed, s.length()))
        {
            for (size_t i = 0; i < path.size(); i++)
            {
                cout << path[i] << (i == path.size() - 1 ? "" : " ");
            }
            cout << "\n";
        }
        else
        {
            cout << "Impossible\n";
        }
    }
    return 0;
}