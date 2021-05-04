//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
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

void solve()
{
    int n;
    cin >> n;
    vector<ll> chain(n), a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> chain[i];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    ll maximum = 0, cur = 0;
    int i = 1;
    while (i < n)
    {
        if (a[i] == b[i])
        {
            cur = 1LL + chain[i];
        }
        else
        {
            if (cur == 0)
            {
                cur = llabs(a[i] - b[i]) + 1LL + chain[i];
            }
            else
            {
                cur = max(cur + chain[i] - (llabs(a[i] - b[i]) - 1), llabs(a[i] - b[i]) + 1LL + chain[i]);
            }
        }
        maximum = max(maximum, cur);
        i++;
    }
    cout << maximum << "\n";
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
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}