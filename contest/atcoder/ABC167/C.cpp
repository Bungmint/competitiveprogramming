#include <bits/stdc++.h>

using namespace std;
const int MAX = 1e9 + 7;
int arr[14][14];
int total[14];
int cost[14];
int n, m, x;

int is_pos(int num)
{
    string binary = bitset<12>(num).to_string();
    int cost1 = 0;
    vector<int> skills(m + 1);
    for (int i = 0; i < n; i++)
    {
        if (binary[11 - i] == '1')
        {
            cost1 += cost[i + 1];
            for (int j = 1; j <= m; j++)
            {
                skills[j] += arr[i + 1][j];
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if (skills[i] < x)
            return MAX;
    }
    return cost1;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    bool is_val = true;
    cin >> n >> m >> x;
    for (int i = 1; i <= n; i++)
    {
        int c, a;
        cin >> c;
        cost[i] = c;
        for (int j = 1; j <= m; j++)
        {
            cin >> a;
            arr[i][j] = a;
            total[j] += a;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if (total[i] < x)
        {
            is_val = false;
            break;
        }
    }
    if (is_val)
    {
        int gold = MAX;
        for (int i = 1; i <= (1 << n); i++)
        {
            gold = min(is_pos(i), gold);
        }
        cout << gold << "\n";
    }
    else
    {
        cout << -1 << "\n";
    }
    return 0;
}