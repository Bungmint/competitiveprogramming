#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> corners;
    vector<vector<char>> rec(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            rec[i].push_back(s[j]);
            if (s[j] == '*')
            {
                corners.push_back({i, j});
            }
        }
    }
    int a = corners[0].first, b = corners[0].second, c = corners[1].first, d = corners[1].second;
    rec[a][d] = '*';
    rec[c][b] = '*';
    if (a == c)
    {
        if (a < n - 1)
        {
            rec[a + 1][b] = '*';
            rec[c + 1][d] = '*';
        }
        else
        {
            rec[a - 1][b] = '*';
            rec[c - 1][d] = '*';
        }
    }
    else if (b == d)
    {
        if (b < n - 1)
        {
            rec[a][b + 1] = '*';
            rec[c][d + 1] = '*';
        }
        else
        {
            rec[a][d - 1] = '*';
            rec[c][b - 1] = '*';
        }
    }
    for (auto x : rec)
    {
        for (auto y : x)
        {
            cout << y;
        }
        cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}