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
    int n, k;
    cin >> n >> k;
    vector<ll> vec(n), pref(n - 1);

    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
        if (i == 1)
            pref[i - 1] = vec[i];
        else if (i > 1)
            pref[i - 1] = vec[i] + pref[i - 2];
    }
    ll cur_sum = 0, total = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            cur_sum += vec[i];
        else
        {
            if (cur_sum * k < vec[i] * 100)
            {
                if (i == 1)
                {
                    ll tmp = vec[0];
                    vec[0] = (100 * vec[i] + k - 1) / k;
                    total += vec[0] - tmp;
                    cur_sum += vec[0] - tmp;
                }
                else
                {
                    ll tmp = vec[0];
                    vec[0] = (100 * vec[i] + k - 1) / k - pref[i - 2];
                    total += vec[0] - tmp;
                    cur_sum += vec[0] - tmp;
                }
            }
            cur_sum += vec[i];
        }
    }
    cout << total << "\n";
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