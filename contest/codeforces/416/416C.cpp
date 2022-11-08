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
    int n;
    cin >> n;
    vector<pair<int, int>> visit(n);
    vector<bool> used(n);
    for (int i = 0; i < n; i++)
    {
        int c, p;
        cin >> c >> p;
        visit[i] = {c, p};
    }
    int k;
    cin >> k;
    vector<pair<int, int>> tables(k), ans;
    int cnt = 0;
    for (int i = 0; i < k; i++)
    {
        cin >> tables[i].first;
        tables[i].second = i + 1;
    }
    sort(all(tables));
    for (int i = 0; i < k; i++)
    {
        int targ = tables[i].first, max_val = 0, idx = -1;
        for (int j = 0; j < n; j++)
        {
            if (used[j])
                continue;
            if (max_val < visit[j].second && visit[j].first <= targ)
            {
                max_val = visit[j].second;
                idx = j;
            }
        }
        if (idx == -1)
            continue;
        cnt += max_val;
        ans.PB({idx + 1, tables[i].second});
        used[idx] = true;
    }
    cout << ans.size() << " " << cnt << "\n";
    for (auto x : ans)
        cout << x.first << " " << x.second << "\n";
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