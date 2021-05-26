//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353

void solve()
{
    int n, tm;
    cin >> n;
    vector<int> v(2 * n);
    map<int, int> s2;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> tm;
        v[i] = tm;
    }
    sort(all(v));
    int big = v[2 * n - 1];
    vector<pair<int, int>> op;
    for (int i = 0; i < 2 * n - 1; i++)
    {
        int ans = big + v[i], x = big + v[i];
        s2.clear();
        op.clear();
        bool ok = true;
        for (int j = 0; j < 2 * n; j++)
            s2[v[j]]++;
        while (!s2.empty())
        {
            pair<int, int> p1 = *--s2.end();
            int b = p1.first;
            s2[b]--;
            if (s2[b] == 0)
                s2.erase(b);
            int targ = x - b;
            if (s2.count(targ) == 0)
            {
                ok = false;
                break;
            }
            s2[targ]--;
            if (s2[targ] == 0)
                s2.erase(targ);
            op.PB({targ, b});
            x = b;
        }
        if (!ok)
            continue;
        cout << "YES\n";
        cout << ans << "\n";
        for (pair<int, int> p : op)
            cout << p.first << " " << p.second << "\n";
        return;
    }
    cout << "NO\n";
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