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

struct segtree
{
    int size;
    vector<ll> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x] += v;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, l, mid);
        else
            set(i, v, 2 * x + 2, mid, r);
        vals[x] = vals[2 * x + 1] + vals[2 * x + 2];
    }
    void set(int i, int v) { set(i, v, 0, 0, size); }

    ll query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
            return vals[x];
        int mid = (lx + rx) / 2;
        ll s1 = query(l, r, 2 * x + 1, lx, mid), s2 = query(l, r, 2 * x + 2, mid, rx);
        return s1 + s2;
    }
    ll query(int l, int r)
    {
        return query(l, r, 0, 0, size);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    segtree st;
    st.init(n + 1);
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            ll l, r, v;
            cin >> l >> r >> v;
            st.set(l, v);
            st.set(r, -v);
        }
        else
        {
            ll i;
            cin >> i;
            cout << st.query(0, i + 1) << "\n";
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