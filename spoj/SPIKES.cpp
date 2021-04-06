#include <bits/stdc++.h>

using namespace std;
bool vis[40][40];
int n, m, j;

bool is_valid(int x, int y)
{
    return (x >= 0 && x <= n - 1) && (y >= 0 && y <= m - 1);
}

void dfs(int x, int y, const vector<vector<char>> &labyrinth, int counter, bool &is_pos)
{
    if (vis[x][y])
        return;
    if (counter > j / 2)
    {
        return;
    }
    vis[x][y] = true;
    if (labyrinth[x][y] == 'x')
    {
        is_pos = true;
        return;
    }
    vector<pair<int, int>> options = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
    for (auto coords : options)
    {
        if (is_valid(coords.first, coords.second))
        {
            if (labyrinth[coords.first][coords.second] == '.' || labyrinth[coords.first][coords.second] == 'x')
            {
                dfs(coords.first, coords.second, labyrinth, counter, is_pos);
            }
            else if (labyrinth[coords.first][coords.second] == 's')
            {
                dfs(coords.first, coords.second, labyrinth, counter + 1, is_pos);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> j;
    pair<int, int> start_coords;
    vector<vector<char>> maze(n);
    for (int i = 0; i <= n - 1; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j <= m - 1; j++)
        {
            maze[i].push_back(s[j]);
            if (s[j] == '@')
            {
                start_coords.first = i;
                start_coords.second = j;
            }
        }
    }
    bool reachable = false;
    dfs(start_coords.first, start_coords.second, maze, 0, reachable);
    if (reachable)
    {
        cout << "SUCCESS"
             << "\n";
    }
    else
    {
        cout << "IMPOSSIBLE"
             << "\n";
    }

    return 0;
}