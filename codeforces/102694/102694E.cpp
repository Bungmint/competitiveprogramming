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
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353
const int N = 3e5 + 10;
vector<int> adj[N];
int start[N], ending[N], timer = 0;

void dfs(int v, int pv)
{
    start[v] = timer;
    for (auto e : adj[v])
    {
        if (e != pv)
        {
            timer++;
            dfs(e, v);
        }
    }
    ending[v] = timer;
}

struct item
{
    long double val = 0LL;
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
        return {log10((long double)v)};
    }
    item merge(item a, item b)
    {
        return {a.val + b.val};
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

bool close(long double x, long double y)
{
    if (x - y > 0 && x - y < 1e-9)
        return true;
    if (y - x > 0 && y - x < 1e-9)
        return true;
    return false;
}

void solve()
{
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs(1, 0);
    cin >> q;
    segtree st;
    st.init(n);
    cout << setprecision(20);
    while (q--)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
        {
            int node = start[x];
            st.set(node, y);
        }
        else
        {
            int sbstart1 = start[x], sbend1 = ending[x];
            int sbstart2 = start[y], sbend2 = ending[y];
            long double logx = st.query(sbstart1, sbend1 + 1).val;
            long double logy = st.query(sbstart2, sbend2 + 1).val;
            if (close(logx, 9 + logy) || logx > 9 + logy)
            {
                cout << 1000000000 << "\n";
            }
            else
            {
                cout << pow(10, logx - logy) << "\n";
            }
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