#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
bool vis[101];

void scuff_dfs(const vector<pair<int, int>> &vec, int idx)
{
    if (vis[idx])
        return;
    vis[idx] = true;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].first == vec[idx].first)
            scuff_dfs(vec, i);
        if (vec[i].second == vec[idx].second)
            scuff_dfs(vec, i);
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
        cin >> points[i].first >> points[i].second;
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        scuff_dfs(points, i);
        counter++;
    }
    cout << counter - 1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}