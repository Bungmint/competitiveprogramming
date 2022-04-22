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
vector<int> idx;
string t, p;
int n;

bool good(int id)
{
    int cnt = 0;
    unordered_set<int> deleted;
    deleted.reserve(1024);
    deleted.max_load_factor(0.25);
    for (int i = 0; i <= id; i++)
    {
        deleted.insert(idx[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (deleted.count(i) != 0)
            continue;
        if (cnt == (int)p.length())
            return true;
        if (t[i] == p[cnt])
            cnt++;
    }
    if (cnt == (int)p.length())
        return true;
    return false;
}

void solve()
{
    cin >> t >> p;
    n = (int)t.length();
    idx.resize(n);
    for (int i = 0; i < (int)n; i++)
    {
        cin >> idx[i];
        idx[i]--;
    }
    int l = 0, r = n - 1, ans = -1;
    while (r >= l)
    {
        int m = l + (-l + r) / 2;
        if (good(m))
        {
            ans = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    cout << ans + 1 << "\n";
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