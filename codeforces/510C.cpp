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
vector<int> adj[26], ans;
bool vis[26];
bool cycle = false;
int color[26];

void cycling(int v, int p)
{
    color[v] = 1; // GREY
    for (int w : adj[v])
    {
        if (color[w] == 1)
        {
            cycle = true;
        }
        if (color[w] == 0)
            cycling(w, v);
    }
    color[v] = 2; // BLACK
}

void dfs(int v)
{
    vis[v] = true;
    for (auto x : adj[v])
    {
        if (!vis[x])
            dfs(x);
    }
    ans.PB(v);
}
void topo()
{
    memset(vis, false, sizeof(vis));
    ans.clear();
    for (int i = 0; i < 26; ++i)
    {
        if (!vis[i])
            dfs(i);
    }
    reverse(ans.begin(), ans.end());
}

void solve()
{
    int n;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; i++)
        cin >> names[i];
    for (int i = 1; i < n; i++)
    {
        string prev = names[i - 1], nxt = names[i];
        int j = 0;
        bool not_same = false;
        while (j < min((int)prev.length(), (int)nxt.length()))
        {
            if (prev[j] != nxt[j])
            {
                not_same = true;
                adj[prev[j] - 'a'].PB(nxt[j] - 'a');
                break;
            }
            j++;
        }
        if (!not_same)
        {
            if (prev.length() > nxt.length())
            {
                cout << "Impossible"
                     << "\n";
                return;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (color[i] == 0)
            cycling(i, -1);
    }
    if (cycle)
    {
        cout << "Impossible"
             << "\n";
        return;
    }
    topo();
    for (auto x : ans)
    {
        char c = 'a' + x;
        cout << c;
    }
    cout << "\n";
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