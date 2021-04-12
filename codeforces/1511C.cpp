#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
    int n, q;
    cin >> n >> q;
    vector<int> colors(n);
    unordered_map<int, int> num_col;
    num_col.reserve(1024);
    num_col.max_load_factor(0.25);
    vector<int> queries(n);
    for (int i = 0; i < n; i++)
    {
        cin >> colors[i];
        if (num_col.count(colors[i]) == 0)
        {
            num_col[colors[i]] = i + 1;
        }
    }
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i];
    }
    for (int i = 0; i < q; i++)
    {
        int cur_quer = queries[i];
        int idx = num_col[cur_quer];
        num_col[cur_quer] = 1;
        for (int j = 1; j <= 50; j++)
        {
            if (num_col.count(j) == 0)
                continue;
            if (num_col[j] <= idx - 1 && j != cur_quer)
            {
                num_col[j]++;
            }
        }
        cout << idx << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}