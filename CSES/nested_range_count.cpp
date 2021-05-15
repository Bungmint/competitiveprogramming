#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,avx,fma")
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
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 2e5 + 100;
pair<int, int> ranges[N];
vector<int> st[2 * N], en[2 * N];
struct Fenwick
{
    int sz;
    vector<int> vec;
    void init(int n)
    {
        sz = n + 1;
        vec.resize(sz + 1);
    }
    void upd(int i, int v)
    {
        i++;
        for (int j = i; j <= sz; j += j & (-j))
        {
            vec[j] += v;
        }
    }
    int query(int i)
    {
        i++;
        int ans = 0LL;
        while (i > 0)
        {
            ans += vec[i];
            i -= i & (-i);
        }
        return ans;
    }
};

void solve()
{
    int n;
    cin >> n;
    Fenwick fw1, fw2;
    set<int> set1;
    unordered_map<int, int> m1;
    for (int i = 0; i < n; i++)
    {
        cin >> ranges[i].first >> ranges[i].second;
        set1.insert(ranges[i].first);
        set1.insert(ranges[i].second);
    }
    int cnt = 0;
    for (auto it = set1.begin(); it != set1.end(); it++)
    {
        m1[*it] = cnt;
        cnt++;
    }
    for (int i = 0; i < n; i++)
    {
        ranges[i].first = m1[ranges[i].first];
        st[ranges[i].first].PB(i);
        ranges[i].second = m1[ranges[i].second];
        en[ranges[i].second].PB(i);
    }
    vector<pair<int, int>> ans(n);
    fw1.init(cnt);
    fw2.init(cnt);
    for (int i = 0; i < cnt; i++)
    {
        for (auto e : en[i])
        {
            ans[e].first = (fw1.query(ranges[e].first) - 1);
        }
        for (auto e : en[i])
        {
            fw1.upd(ranges[e].first, -1);
        }
        fw1.upd(i, (int)st[i].size());
    }
    for (int i = 0; i < cnt; i++)
    {
        for (auto e : en[i])
        {
            fw2.upd(ranges[e].first, 1);
        }
        int cur = fw2.query(i);
        for (auto e : en[i])
        {
            ans[e].second = (cur - fw2.query(ranges[e].first - 1) - 1);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << ans[i].second << " ";
    }
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << ans[i].first << " ";
    }
    cout << "\n";
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