#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
vector<int> mis_idx;
string ans = "", missing;
int counter = 0;
int maze[7][7];

bool valid(int x, int y)
{
    return (x >= 0 && x <= 6) && (y <= 6 && y >= 0) && (maze[x][y] == 0);
}

void path(int k, int x, int y)
{
    if (x == 6 && y == 0 && k != 48)
        return;
    if (k == 48 && x == 6 && y == 0)
    {
        bool is_val = true;
        for (auto x : mis_idx)
        {
            if (missing[x] != ans[x])
            {
                is_val = false;
            }
        }
        if (is_val)
            counter++;
        return;
    }
    if (!(!valid(x - 2, y) && valid(x - 1, y - 1) && valid(x - 1, y + 1)) && valid(x - 1, y))
    {
        ans.PB('U');
        maze[x - 1][y] = 1;
        path(k + 1, x - 1, y);
        ans.pop_back();
        maze[x - 1][y] = 0;
    }
    if (!(valid(x + 1, y) && !valid(x + 2, y) && valid(x + 1, y - 1) && valid(x + 1, y + 1)) && valid(x + 1, y))
    {
        ans.PB('D');
        maze[x + 1][y] = 1;
        path(k + 1, x + 1, y);
        ans.pop_back();
        maze[x + 1][y] = 0;
    }
    if (!(valid(x, y - 1) && !valid(x, y - 2) && valid(x - 1, y - 1) && valid(x + 1, y - 1)) && valid(x, y - 1))
    {
        ans.PB('L');
        maze[x][y - 1] = 1;
        path(k + 1, x, y - 1);
        ans.pop_back();
        maze[x][y - 1] = 0;
    }
    if (!(valid(x, y + 1) && !valid(x, y + 2) && valid(x - 1, y + 1) && valid(x + 1, y + 1)) && valid(x, y + 1))
    {
        ans.PB('R');
        maze[x][y + 1] = 1;
        path(k + 1, x, y + 1);
        ans.pop_back();
        maze[x][y + 1] = 0;
    }
}

void solve()
{
    cin >> missing;
    for (int i = 0; i < 48; i++)
    {
        if (missing[i] != '?')
            mis_idx.PB(i);
    }
    maze[0][0] = 1;
    path(0, 0, 0);
    cout << counter << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}