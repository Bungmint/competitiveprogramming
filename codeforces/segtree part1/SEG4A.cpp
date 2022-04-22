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
    vector<int> sums;
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
            {
                if (l % 2 == 0)
                    sums[x] = vec[l];
                else
                    sums[x] = -vec[l];
            }
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
            if (l % 2 == 0)
                sums[x] = v;
            else
                sums[x] = -v;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, l, mid);
        else
            set(i, v, 2 * x + 2, mid, r);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void set(int i, int v) { set(i, v, 0, 0, size); }
    int query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
            return sums[x];
        int mid = (lx + rx) / 2;
        int s1 = query(l, r, 2 * x + 1, lx, mid);
        int s2 = query(l, r, 2 * x + 2, mid, rx);
        return s1 + s2;
    }
    int query(int l, int r)
    {
        if (l % 2 == 1)
        {
            return -query(l, r, 0, 0, size);
        }
        return query(l, r, 0, 0, size);
    }
};

void solve()
{
    int n, m;
    cin >> n;
    segtree st;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    st.init(n);
    st.build(vec);
    cin >> m;
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 0)
        {
            int i, j;
            cin >> i >> j;
            st.set(i - 1, j);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.query(l - 1, r) << "\n";
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