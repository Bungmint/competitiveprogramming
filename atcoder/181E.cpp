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
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n), forms(m), suffix(n);
    ll ans = LLONG_MAX;
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    for (int i = 0; i < m; i++)
        cin >> forms[i];
    sort(all(vec));
    sort(all(forms));
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            suffix[i] = vec[i];
        else
        {
            if (i % 2 == 0)
                suffix[i] = suffix[i - 1] + vec[i];
            else
                suffix[i] = suffix[i - 1] - vec[i];
        }
    }
    for (int i = 0; i < m; i++)
    {
        int idx = lower_bound(all(vec), forms[i]) - vec.begin();
        if (idx == 0)
            ans = min(ans, suffix[n - 1] - forms[i]);
        else
        {
            if (idx % 2 == 0)
            {
                ans = min(ans, suffix[n - 1] - 2 * suffix[idx - 1] - forms[i]);
            }
            else
            {
                ans = min(ans, suffix[n - 1] - 2 * suffix[idx - 1] + forms[i]);
            }
        }
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