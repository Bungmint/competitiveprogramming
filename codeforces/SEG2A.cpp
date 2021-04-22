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
    ll seg, pref, suf, sum;
};

struct segtree
{
    int size;
    vector<item> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    item NEUTRAL = {0, 0, 0, 0};
    item merge(item A, item B)
    {
        return {
            max(A.seg, max(B.seg, A.suf + B.pref)),
            max(A.pref, A.sum + B.pref),
            max(B.suf, B.sum + A.suf),
            A.sum + B.sum};
    }
    item single(int v)
    {
        if (v > 0)
        {
            return {v, v, v, v};
        }
        else
            return {0, 0, 0, v};
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
    ll max_ans()
    {
        return vals[0].seg;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    segtree st;
    st.init(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    st.build(vec);
    cout << st.max_ans() << "\n";
    while (m--)
    {
        int i, v;
        cin >> i >> v;
        st.set(i, v);
        cout << st.max_ans() << "\n";
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