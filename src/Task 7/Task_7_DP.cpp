#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main()
{
    cout << "enter number of jobs: " << endl;
    int n;
    cin >> n;
    int totalStates = 1 << n;
    cout << "enter: " << endl;
    cout << "(time) | (penalty) | (deadline) of each job " << endl;
    vector<int> t(n), p(n), d(n);
    vector<int> dp(totalStates, INT_MAX);
    vector<int> last_state(totalStates, -1);
    vector<int> last_Job(totalStates, -1);
    vector<int> timeUsed(totalStates, 0);

    for (int i = 0; i < n; i++)
        cin >> t[i] >> p[i] >> d[i];

    dp[0] = 0;

    for (int mask = 0; mask < totalStates; mask++)
    {
        if (dp[mask] == INT_MAX)
            continue;

        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
                continue;

            int newMask = mask | (1 << i);
            int newTime = timeUsed[mask] + t[i];
            int newPenalty = dp[mask];

            if (newTime > d[i])
                newPenalty += p[i];

            if (newPenalty < dp[newMask])
            {
                dp[newMask] = newPenalty;
                last_state[newMask] = mask;
                last_Job[newMask] = i;
                timeUsed[newMask] = newTime;
            }
        }
    }

    int allDone = totalStates - 1;
    vector<int> result;
    int current = allDone;

    while (current != 0)
    {
        result.push_back(last_Job[current]);
        current = last_state[current];
    }
    reverse(result.begin(), result.end());

    int currentTime = 0, minPenalties = 0;
    for (int i = 0; i < n; i++)
    {

        currentTime += t[result[i]];
        if (currentTime > d[result[i]])
            minPenalties += p[result[i]];

        cout << i + 1 << ". "
             << "(job number: " << result[i] + 1 << "), "
             << "time: " << t[result[i]] << " "
             << "penalty: " << p[result[i]] << "  "
             << "deadline: " << d[result[i]] << endl;
    }
    cout << "Minimum penalties could occur: " << minPenalties << endl;

    return 0;
}