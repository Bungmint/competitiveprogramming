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
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 1e5 + 1, LOG = 20;
vector<int> adj[N];
int n, q, sz[N], dep[N], bigC[N], label[N], labeltime = 0, chain[N], up[N][LOG], arr[N];

struct item
{
    int v;
};

struct segtree
{
    int size;
    item NEUTRAL = {0};
    vector<item> vals;
    void init(int n1)
    {
        size = 1;
        while (size < n1)
            size *= 2;
        vals.resize(2 * size);
    }
    item single(int v)
    {
        return {v};
    }
    item merge(item a, item b)
    {
        return {a.v ^ b.v};
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
    int query(int l, int r)
    {
        return query(l, r, 0, 0, size).v;
    }
} st;

void dfs_sz(int V, int pV)
{
    int big = -1, bigsz = 0;
    sz[V] = 1;
    for (auto &e : adj[V])
    {
        if (e != pV)
        {
            dep[e] = dep[V] + 1;
            up[e][0] = V;
            for (int i = 1; i < LOG; i++)
                up[e][i] = up[up[e][i - 1]][i - 1];
            dfs_sz(e, V);
            sz[V] += sz[e];
            if (bigsz < sz[e])
            {
                big = e, bigsz = sz[e];
            }
        }
    }
    bigC[V] = big;
}

void label_dfs(int V, int pV)
{
    label[V] = labeltime++;
    st.set(label[V], arr[V]);
    if (bigC[V] != -1)
    {
        label_dfs(bigC[V], V);
    }
    for (auto e : adj[V])
    {
        if (e != bigC[V] && e != pV)
        {
            label_dfs(e, V);
        }
    }
}

//initialize as chain[i] = i first
void dfs_chains(int V, int pV)
{
    if (bigC[V] != -1)
        chain[bigC[V]] = chain[V];
    for (auto e : adj[V])
    {
        if (e != pV)
            dfs_chains(e, V);
    }
}

int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    int k = dep[a] - dep[b];
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (k & (1 << i))
            a = up[a][i];
    }
    if (a == b)
        return a;
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

int kth_anc(int V, int k)
{
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (k & (1 << i))
            V = up[V][i];
    }
    return V;
}

int chain_query(int v, int p)
{
    int val = 0;
    while (dep[p] < dep[v])
    {
        int top = chain[v];
        if (dep[top] <= dep[p])
        {
            int diff = dep[v] - dep[p];
            top = kth_anc(v, diff - 1);
        }
        val = st.query(label[top], label[v] + 1) ^ val;
        v = up[top][0];
    }
    return val;
}

int query(int u, int v)
{
    int lc = lca(u, v);
    int val = chain_query(u, lc) ^ chain_query(v, lc);
    return val ^ st.query(label[lc], label[lc] + 1);
}

void solve()
{
    cin >> n >> q;
    st.init(n + 1);
    iota(chain + 1, chain + n + 1, 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    dfs_sz(1, 0);
    label_dfs(1, 0);
    dfs_chains(1, 0);
    while (q--)
    {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 1)
            st.set(label[u], v);
        if (op == 2)
            cout << query(u, v) << "\n";
    }
}

int main()
{
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}