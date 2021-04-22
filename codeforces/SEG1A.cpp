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
    vector<ll> sums;

    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        sums.assign(2 * size, 0LL);
    }
    void build(vector<int> &vec, int x, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < (int)vec.size())
                sums[x] = vec[l];
            return;
        }
        int mid = (l + r) / 2;
        build(vec, 2 * x + 1, l, mid);
        build(vec, 2 * x + 2, mid, r);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void build(vector<int> &vec)
    {
        build(vec, 0, 0, size);
    }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            sums[x] = v;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, l, mid);
        else
            set(i, v, 2 * x + 2, mid, r);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }
    ll sum(int x, int l, int r, int lx, int rx)
    {
        if (l >= rx || r <= lx)
            return 0;
        if (l >= lx && r <= rx)
            return sums[x];
        int mid = (l + r) / 2;
        ll s1 = sum(2 * x + 1, l, mid, lx, rx);
        ll s2 = sum(2 * x + 2, mid, r, lx, rx);
        return s1 + s2;
    }
    ll sum(int l, int r)
    {
        return sum(0, 0, size, l, r);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    st.build(arr);
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int j, v;
            cin >> j >> v;
            st.set(j, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.sum(l, r) << "\n";
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