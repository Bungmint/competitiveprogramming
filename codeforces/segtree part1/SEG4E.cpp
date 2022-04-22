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

struct item
{
    int max, min;
};

struct segtree
{
    int size;
    item NEUTRAL = {INT_MAX, INT_MAX};
    vector<item> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.assign(2 * size, NEUTRAL);
    }
    item single(int v)
    {
        if (v == 0)
            return NEUTRAL;
        return {v, v};
    }
    item merge(item a, item b)
    {
        return {
            max(a.max, b.max),
            min(a.min, b.min)};
    }

    void build(vector<int> &vec, int x, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < (int)vec.size())
                vals[x] = single(vec[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(vec, 2 * x + 1, l, mid);
        build(vec, 2 * x + 2, mid, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void build(vector<int> &vec)
    {
        build(vec, 0, 0, size);
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
    void range_set(int l, int r)
    {
        for (int i = l; i < r; i++)
            set(i, 0, 0, 0, size);
    }
    int query(int l, int r, int x, int lx, int rx, int p)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
        {
            if (vals[x].min > p)
                return 0;
            if (vals[x].max <= p)
            {
                range_set(lx, rx);
                return rx - lx;
            }
        }
        int mid = (lx + rx) / 2;
        int a = query(l, r, 2 * x + 1, lx, mid, p);
        int b = query(l, r, 2 * x + 2, mid, rx, p);
        return a + b;
    }
    int query(int l, int r, int p)
    {
        return query(l, r, 0, 0, size, p);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i, h;
            cin >> i >> h;
            st.set(i, h);
        }
        else
        {
            int l, r, p;
            cin >> l >> r >> p;
            cout << st.query(l, r, p) << "\n";
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