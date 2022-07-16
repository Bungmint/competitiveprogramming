// TODO: Test implementation
/**
 * Heavy-Light Decomposition to accompany subtree queries/updates
 * Source: Benq ORZORZ How so ORZ
 * Verification:
 * Time complexity: O(log^2(n)) per query, O(logn) per update
 */

#include "segTreeLazy.h"

template <typename T, typename L, int SZ, bool VAL_IN_EDGES>
struct HLD {
    int N; vi adj[SZ];
    int par[SZ], head[SZ], depth[SZ], subt[SZ], ti;
    int pos[SZ]; vi revpos;
	LazySegTree<T, L> seg{LazySegTree<T, L>(SZ)};
    void add_edge(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
    void dfs_sz(int u) {
        subt[u]++;
        for (auto &v : adj[u]) {
            par[v] = u, depth[v] = depth[u] + 1;
            adj[v].erase(find(all(adj[v]), u));
            dfs_sz(v);
            subt[u] += subt[v];
            if (subt[v] > subt[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void dfs_label(int u) {
        pos[u] = ti++; revpos.pb(u);
        for (auto &v : adj[u]) {
            head[v] = (v == adj[u][0] ? head[u] : v);
            dfs_label(v); 
        }
    }
    void init(int _N, int root = 0) {
        N = _N;
        par[root] = depth[root] = ti = 0; dfs_sz(root); 
        head[root] = root; dfs_label(root);
    }
    int lca(int x, int y) {
        for (; head[x] != head[y]; y = par[head[y]]) {
            if (depth[head[x]] > depth[head[y]]) swap(x, y);
        }
        return depth[x] < depth[y] ? x : y;
    }
    int dist(int x, int y) {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }
    template <typename BinaryOp> 
    void process_path(int x, int y, BinaryOp op) { // [L, R) Half Open
        for (; head[x] != head[y]; y = par[head[y]]) {
            if (depth[head[x]] > depth[head[y]]) swap(x, y);
            op(pos[head[y]], pos[y] + 1);
        }
        if (depth[x] > depth[y]) swap(x, y);
        op(pos[x] + VAL_IN_EDGES, pos[y] + 1);
    }
    void modify_path(int x, int y, L v) {
        process_path(x, y, [this, &v](int l, int r) {
            seg.range_upd(l, r, v);
        });
    }
    T query_path(int x, int y) {
        T res{};
        process_path(x, y, [this, &res](int l, int r) {
            res = res + seg.query(l, r);
        });
        return res;
    }
    void modify_subtree(int x, L v) {
        seg.range_upd(pos[x] + VAL_IN_EDGES, pos[x] + subt[x], v);
    }
};