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
    int brac, open, close;
};

struct segtree
{
    int size;
    item NEUTRAL = {0, 0, 0};
    vector<item> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    item single(char v)
    {
        if (v == '(')
        {
            return {0, 1, 0};
        }
        return {0, 0, 1};
    }
    item merge(item a, item b)
    {
        item res;
        res.brac = a.brac + b.brac + 2 * min(a.open, b.close);
        res.open = a.open + b.open - min(a.open, b.close);
        res.close = a.close + b.close - min(a.open, b.close);
        return res;
    }

    void build(string &s, int x, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < (int)s.length())
                vals[x] = single(s[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(s, 2 * x + 1, l, mid);
        build(s, 2 * x + 2, mid, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void build(string &s)
    {
        build(s, 0, 0, size);
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
};

void solve()
{
    string s;
    cin >> s;
    int m;
    cin >> m;
    segtree st;
    st.init((int)s.length());
    st.build(s);
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << st.query(l - 1, r).brac << "\n";
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