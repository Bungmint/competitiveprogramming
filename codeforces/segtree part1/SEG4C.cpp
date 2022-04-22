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
const int MAX = 131072;
int cnt[40];
struct item
{
    ll arr[40], rev;
    item()
    {
        memset(arr, 0LL, sizeof(arr));
        rev = 0;
    }
};
struct segtree
{
    int sz;
    vector<item> vals;
    item NEUTRAL;
    item merge(item a, item b)
    {
        item ans;
        ans.rev = a.rev + b.rev;
        for (int i = 0; i < 40; i++)
        {
            ans.arr[i] = a.arr[i] + b.arr[i];
            cnt[i] = a.arr[i];
            if (i > 0)
                cnt[i] += cnt[i - 1];
        }
        for (int i = 0; i < 40; i++)
        {
            ans.rev += (cnt[39] - cnt[i]) * b.arr[i];
        }
        return ans;
    }
    item single(int v)
    {
        item res;
        res.arr[v - 1]++;
        return res;
    }
    void init(int n)
    {
        sz = 1;
        while (sz < n)
            sz *= 2;
        vals.resize(2 * sz);
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
        build(vec, 0, 0, sz);
    }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x] = single(v);
            return;
        }
        int m = (l + r) / 2;
        if (i < m)
            set(i, v, 2 * x + 1, l, m);
        else
            set(i, v, 2 * x + 2, m, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, sz);
    }
    item query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return NEUTRAL;
        if (lx >= l && rx <= r)
            return vals[x];
        int m = (lx + rx) / 2;
        item s1 = query(l, r, 2 * x + 1, lx, m), s2 = query(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }
    ll query(int l, int r)
    {
        return query(l, r, 0, 0, sz).rev;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    segtree st;
    st.init(n);
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    st.build(vec);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << st.query(l - 1, r) << "\n";
        }
        else
        {
            int i, v;
            cin >> i >> v;
            st.set(i - 1, v);
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