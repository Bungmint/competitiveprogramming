const int N = 1e5 + 1, LOG = 20;

vector<int> adj[N];
int n, q, sz[N], dep[N], bigC[N], label[N], labeltime = 0, chain[N], up[N][LOG], arr[N];

struct item
{
    ll v;
};

ll combine(int a, int v)
{
}

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
    ll query(int l, int r)
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

ll chain_query(int v, int p)
{
    ll val = 0;
    while (dep[p] < dep[v])
    {
        int top = chain[v];
        if (dep[top] <= dep[p])
        {
            int diff = dep[v] - dep[p];
            top = kth_anc(v, diff - 1);
        }
        val = combine(st.query(label[top], label[v] + 1), val);
        v = up[top][0];
    }
    return val;
}

ll query(int u, int v)
{
    int lc = lca(u, v);
    ll val = combine(chain_query(u, lc), chain_query(v, lc));
    return combine(val, st.query(label[lc], label[lc] + 1));
}
