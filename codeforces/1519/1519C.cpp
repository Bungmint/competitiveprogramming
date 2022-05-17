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
    vector<ll> ans(n);
    vector<pair<int, int>> stud(n);
    vector<vector<ll>> uni(n), pref(n);
    for (int i = 0; i < n; i++)
    {
        cin >> stud[i].second;
    }
    for (int i = 0; i < n; i++)
        cin >> stud[i].first;
    sort(all(stud), [](pair<int, int> x, pair<int, int> y) {
        return x.first > y.first;
    });
    for (int i = 0; i < n; i++)
    {
        uni[stud[i].second - 1].PB(stud[i].first);
    }
    for (int i = 0; i < n; i++)
    {
        pref[i].resize((int)uni[i].size());
        for (int j = 0; j < (int)uni[i].size(); j++)
        {
            if (j == 0)
                pref[i][j] = uni[i][j];
            else
                pref[i][j] = uni[i][j] + pref[i][j - 1];
        }
        for (int j = 1; j <= (int)uni[i].size(); j++)
        {
            ll val = pref[i][((int)uni[i].size() / j) * j - 1];
            ans[j - 1] += val;
        }
    }
    for (auto x : ans)
        cout << x << " ";
    cout << "\n";
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