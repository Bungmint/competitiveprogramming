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
int c[100000], ans[100000];

void solve()
{
    int n;
    cin >> n;
    set<int> not_taken;
    vector<int> pivots;
    for (int i = 1; i <= n; i++)
        not_taken.insert(i);
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (c[i] == *not_taken.rbegin())
            pivots.PB(i);
        not_taken.erase(c[i]);
    }
    int prev = n, last = 0;
    for (int i = 0; i < (int)pivots.size(); i++)
    {
        for (int j = pivots[i]; j < prev; j++)
        {
            ans[last + j - pivots[i]] = c[j];
        }
        last += prev - pivots[i];
        prev = pivots[i];
    }

    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
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