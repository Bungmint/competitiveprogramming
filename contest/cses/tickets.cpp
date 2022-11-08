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

void solve()
{
    int n, m;
    cin >> n >> m;
    map<int, int, greater<int>> map1;
    vector<int> cust(m);
    vector<int> ans(m);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        map1[tmp]++;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> cust[i];
    }
    for (int i = 0; i < m; i++)
    {
        auto it = map1.lower_bound(cust[i]);
        if (it == map1.end())
            ans[i] = -1;
        else
        {
            ans[i] = it->first;
            map1[it->first]--;
            if (it->second == 0)
                map1.erase(it);
        }
    }
    for (auto x : ans)
        cout << x << "\n";
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