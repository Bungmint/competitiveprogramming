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
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

struct item
{
    int zr;
};

struct segtree
{
    int size;
    item NEUTRAL = {0};
    vector<item> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    item single(int v)
    {
        return {v};
    }
    item merge(item a, item b)
    {
        return {a.zr + b.zr};
    }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x] = single(v);
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, l, mid);
        else
            set(i, v, 2 * x + 2, mid, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }
    void upd(int i, int x, int l, int r)
    {
        if (r - l == 1)
        {
            assert(vals[x].zr != 0);
            vals[x].zr--;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            upd(i, 2 * x + 1, l, mid);
        else
            upd(i, 2 * x + 2, mid, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void upd(int i)
    {
        upd(i, 0, 0, size);
    }
    item query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return NEUTRAL;
        if (lx >= l && rx <= r)
            return vals[x];
        int mid = (lx + rx) / 2;
        item a = query(l, r, 2 * x + 1, lx, mid);
        item b = query(l, r, 2 * x + 2, mid, rx);
        return merge(a, b);
    }
    item query(int l, int r)
    {
        return query(l, r, 0, 0, size);
    }
    pair<int, int> zrloc(int val, int l, int r)
    {
        if (r - l == 1)
        {
            return {l, val};
        }
        int mid = (l + r) / 2;
        int quer1 = query(l, mid).zr;
        if (val <= quer1)
            return zrloc(val, l, mid);
        else
            return zrloc(val - quer1, mid, r);
    }
    pair<int, int> zrloc(int val)
    {
        return zrloc(val, 0, size);
    }
};

void solve()
{
    int n, t, k;
    cin >> n >> t >> k;
    int num_sg = (n + 31) / 32;
    segtree st;
    st.init(num_sg);
    for (int i = 0; i < num_sg; i++)
    {
        int ql = 32 * i + 1, qr = min(32 * i + 32, n), ans = -1;
        cout << "? " << ql << " " << qr << "\n";
        cout.flush();
        cin >> ans;
        st.set(i, qr - ql + 1 - ans);
    }
    for (int i = 0; i < t; i++)
    {
        if (i != 0)
            cin >> k;
        auto [loc, val] = st.zrloc(k);
        int ql = loc * 32 + 1, qr = min(32 * loc + 32, n), ans = -1;
        while (ql <= qr)
        {
            if (ql == qr)
            {
                ans = ql;
                break;
            }
            int m = ql + (qr - ql) / 2, quer, numz;
            cout << "? " << ql << " " << m << "\n";
            cout.flush();
            cin >> quer;
            numz = m - ql + 1 - quer;
            if (numz >= val)
            {
                qr = m;
            }
            else
            {
                ql = m + 1;
                val -= numz;
            }
        }
        st.upd(loc);
        cout << "! " << ans << "\n";
        cout.flush();
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