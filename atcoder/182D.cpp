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
    vector<ll> suffix(n), ma(n);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (i == 0)
            suffix[i] = tmp;
        else
            suffix[i] = suffix[i - 1] + tmp;
    }
    ma[0] = suffix[0];
    for (int i = 1; i < n; i++)
    {
        ma[i] = max(ma[i - 1], suffix[i]);
    }
    ll ans = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, sum + ma[i]);
        sum += suffix[i];
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}