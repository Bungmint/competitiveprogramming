#include <bits/stdc++.h>

using ll = long long;
const ll MAX = 2e5 + 5;
bool visited1[MAX];
bool visited2[MAX];
ll adj[MAX];
ll rep;
ll big_counter = 0;
ll loop_counter = 0;

void trav_til_rep(ll x)
{
    if (visited1[x])
    {
        rep = x;
        return;
    }
    visited1[x] = true;
    big_counter++;
    trav_til_rep(adj[x]);
}

void rep_til_rep(ll x)
{
    if (visited2[x])
        return;
    visited2[x] = true;
    loop_counter++;
    rep_til_rep(adj[x]);
}

ll count_dfs(ll num, ll a, ll count)
{
    if (count == a)
        return num;
    return count_dfs(adj[num], a, count + 1);
}

using namespace std;
int main()
{
    ll n, k;
    cin >> n >> k;
    for (ll i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        adj[i] = tmp;
    }
    trav_til_rep(1ll);
    rep_til_rep(rep);
    ll a = big_counter - loop_counter;
    if (k <= a)
    {
        cout << count_dfs(1, k, 0) << "\n";
    }
    else
    {
        ll b = (k - a) % loop_counter;
        cout << count_dfs(rep, b, 0) << "\n";
    }
}