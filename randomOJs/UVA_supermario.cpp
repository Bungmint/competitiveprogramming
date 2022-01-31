
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i, s, n) for (int i = s; i < n; ++i)
#define CL(a, b) memset(a, b, sizeof(a))
#define CLL(a, b, n) fill(a, a + n, b)

const int INF = 1 << 30;
struct Node
{
    int u, k;
    Node(int _u, int _k) : u(_u), k(_k) {}
};
int n, m, A, B, L, K, d[105][12], vis[105][12], G[105][105];

int dijkstra()
{
    REP(i, 0, n)
    REP(j, 0, K + 1) d[i][j] = INF;
    CL(vis, 0);
    queue<Node> q;
    d[n - 1][K] = 0;
    vis[n - 1][K] = 1;
    q.push(Node(n - 1, K));
    while (!q.empty())
    {
        Node top = q.front();
        q.pop();
        int u = top.u, k = top.k;
        REP(v, 0, n)
        {
            if (G[u][v] == INF || v == u)
                continue;
            if (d[v][k] > d[u][k] + G[u][v])
            {
                d[v][k] = d[u][k] + G[u][v];
                if (!vis[v][k])
                {
                    vis[v][k] = 1;
                    q.push(Node(v, k));
                }
            }
            if (k > 0 && L >= G[u][v] && d[v][k - 1] > d[u][k])
            {
                d[v][k - 1] = d[u][k];
                if (!vis[v][k - 1])
                {
                    vis[v][k - 1] = 1;
                    q.push(Node(v, k - 1));
                }
            }
        }
        vis[u][k] = 0;
    }
    int ans = INF;
    REP(i, 0, K + 1)
    ans = min(ans, d[0][i]);
    return ans;
}

void floyd()
{
    REP(k, 0, A)
    REP(i, 0, n) REP(j, 0, n) if (G[i][k] != INF && G[k][j] != INF && G[i][j] > G[i][k] + G[k][j])
        G[i][j] = G[i][k] + G[k][j];
}

int main()
{
    int T, a, b, c;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d%d", &A, &B, &m, &L, &K);
        n = A + B;
        REP(i, 0, n)
        REP(j, 0, n) G[i][j] = INF;
        while (m--)
        {
            scanf("%d%d%d", &a, &b, &c);
            --a, --b;
            G[a][b] = G[b][a] = min(G[a][b], c);
        }
        floyd();
        printf("%d\n", dijkstra());
    }
    return 0;
}