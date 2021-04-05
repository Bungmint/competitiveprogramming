#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 10;
bool visited[MAX];
int dist[MAX];

int main()
{
    int n, m;

    cin >> n >> m;
    if (n >= m)
    {
        cout << n - m << "\n";
    }
    else
    {
        queue<int> q1;
        q1.push(n);
        visited[n] = true;
        while (!q1.empty() && !visited[m])
        {
            int v = q1.front();
            q1.pop();
            int nxt1 = v * 2, nxt2 = v - 1;
            if (nxt1 < MAX)
            {
                if (!visited[nxt1])
                {
                    visited[nxt1] = true;
                    dist[nxt1] = 1 + dist[v];
                    q1.push(nxt1);
                }
            }
            if (nxt2 < 0)
                continue;
            if (!visited[nxt2])
            {
                visited[nxt2] = true;
                dist[nxt2] = 1 + dist[v];
                q1.push(nxt2);
            }
        }
        cout << dist[m] << "\n";
    }
    return 0;
}