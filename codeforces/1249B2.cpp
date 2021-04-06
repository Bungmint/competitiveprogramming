#include <bits/stdc++.h>

using namespace std;
const int MAX = 2e5 + 7;
int adj[MAX];
bool vis[MAX];
int starting_point[MAX];
vector<int> counting_vec(MAX);

void dfs_count(int x, int start, int &counter)
{
    if (x == start && vis[x])
        return;
    vis[x] = true;
    starting_point[x] = start;
    counter++;
    dfs_count(adj[x], start, counter);
}

int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        memset(vis, false, sizeof(vis));
        int n;
        cin >> n;
        vector<int> ans;
        for (int i = 1; i <= n; i++)
        {
            cin >> adj[i];
        }
        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
            {
                ans.push_back(counting_vec[starting_point[i]]);
                continue;
            }
            int counter = 0;
            dfs_count(i, i, counter);
            counting_vec[i] = counter;
            ans.push_back(counter);
        }
        for (auto x : ans)
        {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}