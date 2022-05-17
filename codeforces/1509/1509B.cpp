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
    int n, ts = 0, ms = 0;
    vector<int> t_idx, m_idx;
    cin >> n;
    string s;
    cin >> s;
    bool is_pos = true;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'T')
        {
            t_idx.PB(i);
            ts++;
        }
        else
        {
            ms++;
            m_idx.PB(i);
        }
    }
    if (ts != ms * 2)
        is_pos = false;
    else
    {
        for (int i = 0; i < n / 3; i++)
        {
            if (t_idx[i] > m_idx[i])
                is_pos = false;
            if (t_idx[n / 3 + i] < m_idx[i])
                is_pos = false;
        }
    }
    if (is_pos)
        cout << "YES"
             << "\n";
    else
        cout << "NO"
             << "\n";
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