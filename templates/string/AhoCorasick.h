/**
 * Description: Deterministic Finite Automaton of a dictionary of strings
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/ACfixed.h
 * Verification: 
 * Time Complexity: O(\sigma |S|)
 */

struct AhoCorasick {
    static const int ALPHA = 26;
    struct Node {
        ar<int, 26> to;
        int link;
    };
    vector<Node> d{{}};
    int insert(const string& s) {
        int now = 0;
        for (auto &ch : s) {
            int c = ch - 'a';
            if (!d[now].to[c]) d[now].to[c] = sz(d), d.pb({});
            now = d[now].to[c];
        }
        return now;
    }
    void init() {
        d[0].link = -1;
        queue<int> q;
        q.push(0);
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (int c = 0; c < ALPHA; c++) {
                int v = d[u].to[c]; 
                if (!v) continue;
                d[v].link = d[u].link == -1 ? 0 : d[d[u].link].to[c];
                q.push(v);
            }
            if (u) {
                for (int c = 0; c < ALPHA; c++) {
                    if (!d[u].to[c]) d[u].to[c] = d[d[u].link].to[c];
                }
            }
        }
    }
};