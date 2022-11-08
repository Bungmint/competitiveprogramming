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
int column[8] = {0};
int diag1[17] = {0};
int diag2[17] = {0};
int counter;
char chessboard[8][8];

void backtrack(int y)
{
    if (y == 8)
    {
        counter++;
        return;
    }
    for (int x = 0; x < 8; x++)
    {
        if (column[x] || diag1[x + y] || diag2[x - y + 7] || chessboard[y][x] == '*')
            continue;
        column[x] = diag1[x + y] = diag2[x - y + 7] = 1;
        backtrack(y + 1);
        column[x] = diag1[x + y] = diag2[x - y + 7] = 0;
    }
}

void solve()
{
    for (int i = 0; i < 8; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < 8; j++)
        {
            chessboard[i][j] = s[j];
        }
    }
    counter = 0;
    backtrack(0);
    cout << counter << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}