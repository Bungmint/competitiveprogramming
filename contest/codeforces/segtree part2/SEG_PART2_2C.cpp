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
    ll NO_OP = 0;
    ll NEUTRAL = -1;
    vector<ll> operations;
    vector<ll> values;

    ll operation(ll a, ll b)
    {
        return a | b;
    }
    ll calc(ll a, ll b)
    {
        return a & b;
    }
    void opmod(ll &a, ll b)
    {
        a = operation(a, b);
    }

    //void build(int x, int lx, int rx)
    // {
    //     if (rx - lx == 1)
    //     {
    //         values[x] = 1;
    //         return;
    //     }
    //     int m = (lx + rx) / 2;
    //     build(2 * x + 1, lx, m);
    //     build(2 * x + 2, m, rx);
    //     values[x] = calc(values[2 * x + 1], values[2 * x + 2]);
    // }

    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        operations.assign(2 * size, 0LL);
        values.assign(2 * size, 0LL);
        // build(0, 0, size);
    }
    void lazy_propagate(int x, int lx, int rx)
    {
        if (rx - lx == 1)
            return;
        opmod(operations[2 * x + 1], operations[x]);
        opmod(values[2 * x + 1], operations[x]);
        opmod(operations[2 * x + 2], operations[x]);
        opmod(values[2 * x + 2], operations[x]);
        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx)
    {
        lazy_propagate(x, lx, rx);
        if (lx >= r || rx <= l)
            return;
        if (lx >= l && rx <= r)
        {
            opmod(operations[x], v);
            opmod(values[x], v);
            return;
        }
        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
        values[x] = calc(values[2 * x + 1], values[2 * x + 2]);
    }

    void modify(int l, int r, int v)
    {
        modify(l, r, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx)
    {
        lazy_propagate(x, lx, rx);
        if (lx >= r || rx <= l)
            return NEUTRAL;
        if (lx >= l && rx <= r)
        {
            return values[x];
        }
        int mid = (lx + rx) / 2;
        ll m1 = get(l, r, 2 * x + 1, lx, mid);
        ll m2 = get(l, r, 2 * x + 2, mid, rx);
        ll res = calc(m1, m2);
        opmod(res, operations[x]);
        return res;
    }

    ll get(int l, int r)
    {
        return get(l, r, 0, 0, size);
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
            int l, r;
            cin >> l >> r;
            cout << st.get(l, r) << "\n";
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