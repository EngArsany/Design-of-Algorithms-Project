#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main()
{
    int n;
    cout << "enter number of jobs: " << endl;
    cin >> n;
    cout << "enter: " << endl;
    cout << "(time) | (penalty) | (deadline) of each job " << endl;

    vector<int>
        t(n),
        p(n), d(n), result(n), job(n);
    int time = 0, total_penalties, min_penalties = INT_MAX;

    for (int i = 0; i < n; i++)
    {

        cin >> t[i] >> p[i] >> d[i];
        job[i] = i;
    }

    do
    {
        total_penalties = 0;
        time = 0;
        for (int i = 0; i < n; i++)
        {
            time += t[job[i]];
            if (time > d[job[i]])
                total_penalties += p[job[i]];
        }

        if (total_penalties < min_penalties)
        {
            min_penalties = total_penalties;
            for (int i = 0; i < n; i++)
                result[i] = job[i];
        }
    } while (next_permutation(job.begin(), job.end()));

    for (int i = 0; i < n; i++)
        cout << i + 1 << ". " << "(job number: " << result[i] + 1 << "), time: " << t[result[i]] << " penalty: " << p[result[i]] << "  deadline: " << d[result[i]] << endl;
    cout << "Minimum penalties could occur: " << min_penalties << endl;

    return 0;
}