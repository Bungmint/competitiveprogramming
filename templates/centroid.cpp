//WeakestTopology ORZ (From his solution to 342E) https://codeforces.com/contest/342/submission/90467624
//1-indexing
struct CentroidDecomposition
{
    const vector<vi>& E;
    vi par, subsz, level;
    vector<bool> vis;
    vector<vi> dist;
    int dfs(int u, int p, int h)
    {
        if (h != -1) dist[u][h] = dist[p][h] + 1;
        subsz[u] = 1;
        for (auto v : E[u])
            if (!vis[v] && v != p) subsz[u] += dfs(v, u, h);
        return subsz[u];
    }
    int find_centroid(int u, int p, int sz)
    {
        for (auto v : E[u])
            if (!vis[v] && v != p && subsz[v]*2 > sz)
                return find_centroid(v, u, sz);
        return u;
    }
    void build(int u, int p)
    {
        int sz = dfs(u, p, p == -1 ? -1 : level[p]);
        int centroid = find_centroid(u, p, sz);
        par[centroid] = p, vis[centroid] = 1;
        if (p != -1) level[centroid] = level[p] + 1;
        for (auto v : E[centroid])
            if (!vis[v]) build(v, centroid);
    }
    CentroidDecomposition(const vector<vector<int>>& E) : E(E)
    {
        int n = sz(E);
        par.assign(n, -1), subsz.assign(n, 0), vis.assign(n, 0);
        level.assign(n, 0), dist.assign(n, vector(31 - __builtin_clz(n), 0));
        build(1, -1);
    }
    int operator[](int u) const { return par[u]; }
    int lca(int u, int v) // centroid lca, not tree lca
    {
        if (level[u] < level[v]) swap(u, v);
        while (level[u] > level[v]) u = par[u];
        while (u != v) u = par[u], v = par[v];
        return u;
    }
    int distance(int u, int v)
    {
        int w = lca(u, v);
        return dist[u][level[w]] + dist[v][level[w]];
    }
};