#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
const int MAX = 1e7;
ll pre[MAX + 1];
ll ans[MAX + 1];
const int N = 1e7; // Only advised to use it under 1e7 (More Memory)
ll lp[N + 1];
vector<int> pr;

void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}
ll pow(ll p, ll exp)
{
    if (exp == 1)
        return p;
    ll m = pow(p, exp / 2);
    ll ans = m * m;
    if (exp % 2 == 0)
        return ans;
    else
        return ans * p;
}

void precalc()
{
    memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= MAX; i++)
    {
        ll val = 1, cur = i;
        while (cur > 1)
        {
            ll fc = lp[cur];
            ll cnt = 0;
            while (cur % fc == 0)
            {
                cnt++;
                cur /= fc;
            }
            val *= (pow(fc, cnt + 1) - 1) / (fc - 1);
        }
        pre[i] = val;
    }
    for (int i = 1; i <= MAX; i++)
    {
        if (pre[i] > MAX || ans[pre[i]] != -1)
            continue;
        ans[pre[i]] = i;
    }
}

void solve()
{
    int n;
    cin >> n;
    cout << ans[n] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    precalc();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}