#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
vector<int> adj[210];

int dfs(int V, int pV)
{
    if (adj[V].size() == 0 && V != 1)
        return 1;
    int ans = 0;
    for (auto x : adj[V])
    {
        if (x != pV)
        {
            ans = max(ans, 1 + dfs(x, V));
        }
    }
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    unordered_map<string, int> handles;

    handles.reserve(1024);
    handles.max_load_factor(0.25);
    for (int i = 0; i < n; i++)
    {
        string s1, _, s2;
        cin >> s1 >> _ >> s2;
        for (int j = 0; j < s1.length(); j++)
        {
            s1[j] = tolower(s1[j]);
        }
        for (int j = 0; j < s2.length(); j++)
        {
            s2[j] = tolower(s2[j]);
        }
        if (i == 0)
        {
            handles.insert({s2, 1});
            handles.insert({s1, 2});
            adj[1].push_back(2);
        }
        else
        {
            assert(handles.count(s2) != 0);
            int former = handles[s2];
            handles.insert({s1, handles.size() + 1});
            adj[former].push_back(handles[s1]);
        }
    }
    int depth = dfs(1, 0);
    cout << depth << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}