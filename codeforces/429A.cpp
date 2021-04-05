#include <bits/stdc++.h>
const int MAX = 1e5 + 5;

using namespace std;

vector<int> adj[MAX];
int init[MAX];
int goal[MAX];
vector<int> result;

void dfs(int num, int prev, int odd_times, int even_times, int level)
{
    int cur;
    if (level % 2)
    {
        cur = (init[num] + odd_times) % 2;
    }
    else
    {
        cur = (init[num] + even_times) % 2;
    }
    if (cur != goal[num])
    {
        if (level % 2)
        {
            odd_times += 1;
        }
        else
        {
            even_times += 1;
        }
        result.push_back(num);
    }
    for (auto x : adj[num])
    {
        if (x == prev)
            continue;
        dfs(x, num, odd_times, even_times, level + 1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        init[i] = a;
    }
    for (int j = 1; j <= n; j++)
    {
        int d;
        cin >> d;
        goal[j] = d;
    }
    dfs(1, -1, 0, 0, 0);
    cout << result.size() << "\n";
    for (auto x : result)
    {
        cout << x << "\n";
    }

    return 0;
}