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
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 1e4 + 1, LOG = 15;

int n1, q, arr1[N], Edge[N], Vertex[N];
template <int size, int lg, typename seg_t = long long>
struct hld
{
    vector<ar<int, 2>> edges[size];
    int bigchild[size];
    int sz[size];
    int depth[size];
    int chain[size];
    int label[size], label_time;
    int par[size];

    int lca_lift[size][lg];

    seg_t seg_tree[4 * size];
    seg_t seg_lazy[4 * size];

    int N;

    /* ----------- segment tree ----------- */

    /* CHANGE THIS SECTION BY PROBLEM */
    inline seg_t seg_combine(seg_t a, seg_t b)
    {
        return (a > b) ? a : b;
    }

    inline seg_t seg_lazy_apply(seg_t lazy_val, seg_t new_val)
    {
        return new_val;
    }

    inline seg_t seg_lazy_func(seg_t cur_val, seg_t lazy_val, int l, int r)
    {
        return lazy_val;
    }

    const seg_t seg_sentinel = 0;
    const seg_t seg_lazy_sentinel = -1;
    const seg_t seg_init_val = 0;
    /* END SECTION */

    seg_t seg_query_header(int l, int r)
    {
        return seg_query_rec(0, 0, N - 1, l, r);
    }

    seg_t seg_query_rec(int i, int tl, int tr, int ql, int qr)
    {
        seg_eval_lazy(i, tl, tr);

        if (ql <= tl && tr <= qr)
            return seg_tree[i];
        if (tl > tr || tr < ql || qr < tl)
            return seg_sentinel;

        int mid = (tl + tr) / 2;
        seg_t a = seg_query_rec(2 * i + 1, tl, mid, ql, qr);
        seg_t b = seg_query_rec(2 * i + 2, mid + 1, tr, ql, qr);
        return seg_combine(a, b);
    }

    void seg_update_header(int l, int r, seg_t v)
    {
        seg_update_rec(0, 0, N - 1, l, r, v);
    }

    seg_t seg_update_rec(int i, int tl, int tr, int ql, int qr, seg_t v)
    {
        seg_eval_lazy(i, tl, tr);

        if (tl > tr || tr < ql || qr < tl)
            return seg_tree[i];
        if (ql <= tl && tr <= qr)
        {
            seg_lazy[i] = seg_lazy_apply(seg_lazy[i], v);
            seg_eval_lazy(i, tl, tr);
            return seg_tree[i];
        }
        if (tl == tr)
            return seg_tree[i];

        int mid = (tl + tr) / 2;
        seg_t a = seg_update_rec(2 * i + 1, tl, mid, ql, qr, v);
        seg_t b = seg_update_rec(2 * i + 2, mid + 1, tr, ql, qr, v);
        return seg_tree[i] = seg_combine(a, b);
    }

    void seg_eval_lazy(int i, int l, int r)
    {
        if (seg_lazy[i] == seg_lazy_sentinel)
            return;

        seg_tree[i] = seg_lazy_func(seg_tree[i], seg_lazy[i], l, r);

        if (l != r)
        {
            seg_lazy[i * 2 + 1] = seg_lazy_apply(seg_lazy[i * 2 + 1], seg_lazy[i]);
            seg_lazy[i * 2 + 2] = seg_lazy_apply(seg_lazy[i * 2 + 2], seg_lazy[i]);
        }

        seg_lazy[i] = seg_lazy_sentinel;
    }

    /* ----------- init phase 1 ----------- */
    /* initialize segtree, clear edges, etc. */

    void init_arrays(int n)
    {
        // everything not initialized doesn't need to be
        N = n;
        for (int i = 0; i < N; i++)
        {
            edges[i].clear();
            chain[i] = i;
        }

        for (int i = 0; i < 4 * N; i++)
        {
            seg_tree[i] = seg_init_val;
            seg_lazy[i] = seg_lazy_sentinel;
        }
    }

    /* ----------- init phase 2 ----------- */
    /* put edges in */

    void add_edge(int u, int v, int i)
    {
        edges[u].push_back({v, i});
        edges[v].push_back({u, i});
    }

    /* ----------- init phase 3 ----------- */
    /* build the lca and hld stuff */

    void init_tree(seg_t *arr, int root = 0)
    {
        // lca
        lca_dfs(root, -1);

        // size, compute biggest children
        dfs_size(root, -1, 0);

        // compute chains
        dfs_chains(root, -1);

        // label nodes
        label_time = 0;
        dfs_labels(arr, root, -1);
    }

    void lca_dfs(int v, int par1)
    {
        lca_lift[v][0] = par1;

        for (int i = 1; i < lg; i++)
        {
            if (lca_lift[v][i - 1] == -1)
                lca_lift[v][i] = -1;
            else
                lca_lift[v][i] = lca_lift[lca_lift[v][i - 1]][i - 1];
        }

        for (ar<int, 2> x : edges[v])
        {
            if (x[0] != par1)
            {
                lca_dfs(x[0], v);
            }
        }
    }

    void dfs_size(int v, int p, int d)
    {
        sz[v] = 1;
        depth[v] = d;
        par[v] = p;
        int bigc = -1, bigv = -1;

        for (ar<int, 2> x : edges[v])
        {
            if (x[0] != p)
            {
                dfs_size(x[0], v, d + 1);
                sz[v] += sz[x[0]];
                Edge[x[0]] = x[1];
                Vertex[x[1]] = x[0];
                if (sz[x[0]] > bigv)
                {
                    bigc = x[0];
                    bigv = sz[x[0]];
                }
            }
        }
        bigchild[v] = bigc;
    }

    void dfs_chains(int v, int p)
    {
        if (bigchild[v] != -1)
        {
            chain[bigchild[v]] = chain[v];
        }

        for (ar<int, 2> x : edges[v])
        {
            if (x[0] != p)
            {
                dfs_chains(x[0], v);
            }
        }
    }

    void dfs_labels(seg_t *arr, int v, int p)
    {
        label[v] = label_time++;
        if (v != 0)
            seg_update_header(label[v], label[v], arr[Edge[v]]);

        if (bigchild[v] != -1)
        {
            dfs_labels(arr, bigchild[v], v);
        }

        for (ar<int, 2> x : edges[v])
        {
            if (x[0] != p && x[0] != bigchild[v])
            {
                dfs_labels(arr, x[0], v);
            }
        }
    }

    /* ----------- init phase 4 ----------- */
    /* usage */

    int lca(int a, int b)
    {
        if (depth[a] < depth[b])
            swap(a, b);
        int d = depth[a] - depth[b];
        int v = get_kth_ancestor(a, d);
        if (v == b)
        {
            return v;
        }
        else
        {
            for (int i = lg - 1; i >= 0; i--)
            {
                if (lca_lift[v][i] != lca_lift[b][i])
                {
                    v = lca_lift[v][i];
                    b = lca_lift[b][i];
                }
            }
            return lca_lift[b][0];
        }
    }

    int get_kth_ancestor(int v, int k)
    {
        for (int i = lg - 1; i >= 0; i--)
        {
            if (v == -1)
                return v;
            if ((1 << i) <= k)
            {
                v = lca_lift[v][i];
                k -= (1 << i);
            }
        }
        return v;
    }

    /* excludes p */
    seg_t query_chain(int v, int p)
    {
        seg_t val = seg_sentinel;
        while (depth[p] < depth[v])
        {
            int top = chain[v];
            if (depth[top] <= depth[p])
            {
                int diff = depth[v] - depth[p];
                top = get_kth_ancestor(v, diff - 1);
            }
            val = seg_combine(val, seg_query_header(label[top], label[v]));
            v = par[top];
        }
        return val;
    }

    seg_t query(int u, int v)
    {
        int lc = lca(u, v);
        seg_t val = seg_combine(query_chain(u, lc), query_chain(v, lc));
        return val;
    }

    /* excludes p */
    void update_chain(int v, int p, seg_t val)
    {
        while (depth[p] < depth[v])
        {
            int top = chain[v];
            if (depth[top] <= depth[p])
            {
                int diff = depth[v] - depth[p];
                top = get_kth_ancestor(v, diff - 1);
            }
            seg_update_header(label[top], label[v], val);
            v = par[top];
        }
    }

    void update(int u, int v, seg_t val)
    {
        int lc = lca(u, v);
        update_chain(u, lc, val);
        update_chain(v, lc, val);
        seg_update_header(label[lc], label[lc], val);
    }
};
hld<N, LOG, int> h;
void solve()
{
    cin >> n1;
    h.init_arrays(n1);
    memset(arr1, 0, sizeof(arr1));

    for (int i = 0; i < n1 - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        h.add_edge(u, v, i);
        arr1[i] = w;
    }
    h.init_tree(arr1);
    string op;
    while (true)
    {
        cin >> op;
        if (op == "DONE")
            return;
        if (op == "CHANGE")
        {
            int u, v;
            cin >> u >> v;
            u--;
            h.update(Vertex[u], Vertex[u], v);
        }
        else
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            cout << h.query(u, v) << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}