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
stack<int> st;
bool vis[5001], valid[5001];
vector<int> ans;
vector<vector<int>> adj, rev;
int v, cnt = 0;
set<int> comps[5001];
void dfs(int V)
{
    vis[V] = true;
    for (auto &e : adj[V])
    {
        if (!vis[e])
            dfs(e);
    }
    st.push(V);
}

void revdfs(int V)
{
    vis[V] = true;
    comps[cnt].insert(V);
    for (auto &e : rev[V])
    {
        if (!vis[e])
            revdfs(e);
    }
}
void checker(int V, int sc)
{
    if (vis[V])
        return;
    vis[V] = true;
    for (auto &e : adj[V])
    {
        if (!vis[e])
        {
            if (comps[sc].count(e) == 0)
            {
                valid[sc] = false;
                return;
            }
            checker(e, sc);
        }
    }
}

void scc()
{
    for (int i = 0; i <= 5000; i++)
        comps[i].clear();
    while (!st.empty())
    {
        int v1 = st.top();
        st.pop();
        if (vis[v1])
            continue;
        revdfs(v1);
        cnt++;
    }
    memset(vis, false, sizeof(vis));
    memset(valid, true, sizeof(valid));
    for (int i = 0; i < cnt; i++)
    {
        checker(*comps[i].begin(), i);
    }
    ans.clear();
    for (int i = 0; i < cnt; i++)
    {
        if (valid[i])
        {
            for (auto &e : comps[i])
                ans.PB(e);
        }
    }
    sort(all(ans));
    for (auto e : ans)
        cout << e << " ";
    cout << "\n";
}

void solve()
{
    while (true)
    {
        cin >> v;
        if (v == 0)
            break;
        int e;
        cin >> e;
        adj.clear();
        rev.clear();
        adj.resize(v + 1);
        rev.resize(v + 1);
        for (int i = 0; i < e; i++)
        {
            int u, w;
            cin >> u >> w;
            adj[u].PB(w);
            rev[w].PB(u);
        }
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= v; i++)
        {
            if (!vis[i])
                dfs(i);
        }
        memset(vis, false, sizeof(vis));
        cnt = 0;
        scc();
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