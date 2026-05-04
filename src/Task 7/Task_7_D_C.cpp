#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;
vector<int> t(n), p(n), d(n);

bool firstJob(int job_1, int job_2)
{
    int penalty_1 = (t[job_1] > d[job_1] ? p[job_1] : 0) + (t[job_1] + t[job_2] > d[job_2] ? p[job_2] : 0);
    int penalty_2 = (t[job_2] > d[job_2] ? p[job_2] : 0) + (t[job_1] + t[job_2] > d[job_1] ? p[job_1] : 0);

    return penalty_1 <= penalty_2;
}

void mergeSort(vector<int> &job, int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;
    mergeSort(job, l, mid);
    mergeSort(job, mid + 1, r);

    vector<int> temp;
    int i = l, j = mid + 1;

    while (i <= mid && j <= r)
    {
        if (firstJob(job[i], job[j]))
            temp.push_back(job[i++]);
        else
            temp.push_back(job[j++]);
    }
    while (i <= mid)
        temp.push_back(job[i++]);
    while (j <= r)
        temp.push_back(job[j++]);

    for (int k = l; k <= r; k++)
        job[k] = temp[k - l];
}

int main()
{
    cout << "enter number of jobs: " << endl;
    cin >> n;

    t.resize(n);
    p.resize(n);
    d.resize(n);
    vector<int> result(n);
    int time = 0, minPenalties = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> t[i] >> p[i] >> d[i];
        result[i] = i;
    }

    mergeSort(result, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        time += t[result[i]];
        if (time > d[result[i]])
            minPenalties += p[result[i]];

        cout << i + 1 << ". " << "(job number: " << result[i] + 1 << "), time: " << t[result[i]] << " penalty: " << p[result[i]] << "  deadline: " << d[result[i]] << endl;
    }
    cout << "Minimum penalties could occur: " << minPenalties << endl;

    return 0;
}