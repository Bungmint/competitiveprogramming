#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
    vector<int> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    void build(vector<int> &vec, int x, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < (int)vec.size())
                vals[x] = vec[l];
            return;
        }
        int mid = (l + r) / 2;
        build(vec, 2 * x + 1, l, mid);
        build(vec, 2 * x + 2, mid, r);
        vals[x] = max(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void build(vector<int> &vec) { build(vec, 0, 0, size); }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x] = v;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, l, mid);
        else
            set(i, v, 2 * x + 2, mid, r);
        vals[x] = max(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void set(int i, int v) { set(i, v, 0, 0, size); }
    int first(int v, int x, int l, int r)
    {
        if (vals[x] < v)
            return -1;
        if (r - l == 1)
            return l;
        int mid = (l + r) / 2;
        int s1 = first(v, 2 * x + 1, l, mid);
        if (s1 == -1)
        {
            s1 = first(v, 2 * x + 2, mid, r);
        }
        return s1;
    }
    int first(int v)
    {
        return first(v, 0, 0, size);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    st.build(vec);
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }
        else
        {
            int x;
            cin >> x;
            cout << st.first(x) << "\n";
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