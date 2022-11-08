#include <bits/stdc++.h>
using ll = long long;
const ll MAX = 1e5 + 5;

using namespace std;
bool visited[MAX];
int cash[MAX];
vector<ll> adjacent[MAX];

ll dfs(int num)
{
    if (visited[num])
        return cash[num];
    ll gold = cash[num];
    visited[num] = true;
    for (auto x : adjacent[num])
    {
        ll part = dfs(x);
        gold = min(gold, part);
    }
    return gold;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll n, m, temp;
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        cin >> temp;
        cash[i] = temp;
        visited[i] = false;
    }
    for (ll j = 0; j < m; j++)
    {
        ll a, b;
        cin >> a >> b;
        adjacent[a].push_back(b);
        adjacent[b].push_back(a);
    }

    ll total = 0;
    for (ll i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;
        if (adjacent[i].size() == 0)
        {
            total += cash[i];
            continue;
        }
        total += dfs(i);
    }
    cout << total << "\n";

    return 0;
}
