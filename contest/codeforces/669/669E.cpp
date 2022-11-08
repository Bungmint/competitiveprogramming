#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> timeline(n);
    vector<int> times(n);
    for (int i = 0; i < n; i++)
    {
        cin >> timeline[i].first >> timeline[i].second.first >> timeline[i].second.second;
        times[i] = timeline[i].second.first;
    }
    sort(times.begin(), times.end());
    vector<unordered_map<int, int>> pog(n + 1);
    for (int i = 0; i < n; i++)
    {
        int t1 = timeline[i].second.first;
        int task = timeline[i].first;
        int num = timeline[i].second.second;
        int idx = lower_bound(times.begin(), times.end(), t1) - times.begin();
        if (task == 3)
        {
            int ans = 0;
            int search = idx + 1;
            while (search)
            {
                ans += pog[search][num];
                search -= search & (-search);
            }
            cout << ans << "\n";
            continue;
        }
        switch (task)
        {
        case 1:
            for (int j = idx + 1; j <= n; j += (j & (-j)))
            {
                pog[j][num] += 1;
            }
            break;
        case 2:
            for (int j = idx + 1; j <= n; j += (j & (-j)))
            {
                pog[j][num] -= 1;
            }
            break;
        }
    }

    return 0;
}