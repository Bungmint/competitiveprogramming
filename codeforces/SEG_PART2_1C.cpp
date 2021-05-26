#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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

struct segtree
{
    int size;
    ll NEUTRAL = LINF;
    vector<ll> vals;

    ll operation(ll a, ll b)
    {
        return ((b == LINF) ? a : b);
    }
    void opmod(ll &a, ll b)
    {
        a = operation(a, b);
    }

    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    void lazy_propagate(int x, int lx, int rx)
    {
        if (rx - lx == 1)
            return;
        opmod(vals[2 * x + 1], vals[x]);
        opmod(vals[2 * x + 2], vals[x]);
        vals[x] = NEUTRAL;
    }

    void modify(int l, int r, int v, int x, int lx, int rx)
    {
        lazy_propagate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (lx >= l && rx <= r)
        {
            vals[x] = operation(vals[x], v);
            return;
        }
        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
    }

    void modify(int l, int r, int v)
    {
        modify(l, r, v, 0, 0, size);
    }

    ll get(int i, int x, int lx, int rx)
    {
        lazy_propagate(x, lx, rx);
        if (rx - lx == 1)
        {
            return vals[x];
        }
        ll res;
        int mid = (lx + rx) / 2;
        if (i < mid)
            res = get(i, 2 * x + 1, lx, mid);
        else
            res = get(i, 2 * x + 2, mid, rx);
        return res;
    }

    ll get(int i)
    {
        return get(i, 0, 0, size);
    }
} st;

void solve()
{
    int n, m;
    cin >> n >> m;
    st.init(n);
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;
            st.modify(l, r, v);
        }
        else
        {
            int i;
            cin >> i;
            cout << st.get(i) << "\n";
        }
    }
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