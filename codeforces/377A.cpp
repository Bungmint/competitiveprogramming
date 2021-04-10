#include <bits/stdc++.h>

using namespace std;
bool vis[501][501];
int N;
int total = 0;
int n, m, k;

void dfs(vector<vector<char>> &vec, int x, int y)
{
    if (vis[x][y])
        return;
    if (vec[x][y] == '#')
        return;
    if (N == total - k)
        return;
    vis[x][y] = true;
    N++;

    if (x < n - 1)
        dfs(vec, x + 1, y);
    if (x > 0)
        dfs(vec, x - 1, y);
    if (y < m - 1)
        dfs(vec, x, y + 1);
    if (y > 0)
        dfs(vec, x, y - 1);
}

int main()
{
    cin >> n >> m >> k;
    N = 0;
    vector<vector<char>> maze(n, vector<char>(m));
    int x_pos, y_pos;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            maze[i][j] = s[j];
            if (maze[i][j] == '.')
            {
                total++;
                x_pos = i;
                y_pos = j;
            }
        }
    }
    dfs(maze, x_pos, y_pos);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vis[i][j] && maze[i][j] == '.')
            {
                maze[i][j] = 'X';
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << maze[i][j];
        }
        cout << "\n";
    }
}