/**
 * Description: Fast flow. 
 * Source:
    * ksun: https://codeforces.com/contest/1416/submission/94013395
    * Benq: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/Dinic.h
 * Verification:
 * Time complexity: O(mn^2) for general graphs, O(m\sqrt{n}) for simple unit capacity networks
 */

template <typename F>
struct Dinic {
    struct Edge {
        int to, rev;
        F cap;
    };
    int N;
    vector<vector<Edge>> adj;
    vi ptr, lvl;
    Dinic(int _N) { N = _N; adj.resize(N); }
    pii add_edge(int a, int b, F cap, F rcap = 0) {
        assert(min(cap, rcap) >= 0);
        adj[a].pb({b, sz(adj[b]), cap});
        adj[b].pb({a, sz(adj[a]) - 1, rcap});
        return {a, sz(adj[a]) - 1};
    }
    F get_edge_flow(pii loc) {
        const Edge& e = adj.at(loc.fi).at(loc.se);
        return adj.at(e.to).at(e.rev).cap;
    }
    // Generate the level graph
    bool bfs(int s, int t) {
        lvl = ptr = vi(N);
        lvl[s] = 1; queue<int> q({s});
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap && !lvl[e.to]) {
                    q.push(e.to);
                    lvl[e.to] = lvl[u] + 1;
                    if (e.to == t) return 1;
                }
            }
        }
        return 0;
    }
    F dfs(int v, int t, F flow) {
        if (v == t) return flow;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge &e = adj[v][i];
            if (lvl[e.to] != lvl[v] + 1 || !e.cap) continue;
            if (F df = dfs(e.to, t, min(flow, e.cap))) {
                e.cap -= df; adj[e.to][e.rev].cap += df;
                return df;
            }
        }
        return 0;
    }
    F get_max_flow(int s, int t) {
        F res{};
        while (bfs(s, t)) {
            while (F df = dfs(s, t, numeric_limits<F>::max())) {
                res += df;
            }
        }
        return res;
    }
};