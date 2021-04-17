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
    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i].first;
        vec[i].second = i;
    }
    sort(all(vec));
    bool is_pos = false;
    for (int i = 0; i < n; i++)
    {
        if (vec[i].first > x / 2)
            break;
        auto idx = lower_bound(all(vec), make_pair(x - vec[i].first, -INF));
        if (idx->first != x - vec[i].first || idx->second == vec[i].second)
        {
            continue;
        }
        else
        {
            cout << vec[i].second + 1 << " " << idx->second + 1 << "\n";
            is_pos = true;
            break;
        }
    }
    if (!is_pos)
        cout << "IMPOSSIBLE"
             << "\n";
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