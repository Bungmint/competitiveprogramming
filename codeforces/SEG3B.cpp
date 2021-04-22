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
int n;

struct segtree
{
    int size;
    vector<int> vals;
    void init(int num)
    {
        size = 1;
        while (size < num)
            size *= 2;
        vals.resize(size * 2);
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
        vals[x] = vals[2 * x + 1] + vals[2 * x + 2];
    }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x] = v;
            return;
        }
        int m = (l + r) / 2;
        if (i < m)
            set(i, v, 2 * x + 1, l, m);
        else
            set(i, v, 2 * x + 2, m, r);
        vals[x] = vals[2 * x + 1] + vals[2 * x + 2];
    }
    void build(vector<int> &vec) { build(vec, 0, 0, size); }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }
    int query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
            return vals[x];
        int m = (lx + rx) / 2;
        int s1 = query(l, r, 2 * x + 1, lx, m);
        int s2 = query(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }
    int query(int l, int r) { return query(l, r, 0, 0, size); }
    int find_empty(int k, int x, int l, int r)
    {
        if (r - l == 1)
            return l;
        int mid = (l + r) / 2;
        int right = vals[2 * x + 2];
        int s1;
        if (right <= k)
            s1 = find_empty(k - right, 2 * x + 1, l, mid);
        else
            s1 = find_empty(k, 2 * x + 2, mid, r);
        return s1;
    }
    int find_empty(int k)
    {
        return find_empty(k, 0, 0, size);
    }
};

void solve()
{
    cin >> n;
    vector<int> vec(n);
    fill(all(vec), 1);
    segtree st;
    st.init(n);
    st.build(vec);
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    for (int i = n - 1; i >= 0; i--)
    {
        vec[i] = st.find_empty(vec[i]);
        st.set(vec[i], 0);
    }
    for (auto x : vec)
        cout << x + 1 << " ";
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