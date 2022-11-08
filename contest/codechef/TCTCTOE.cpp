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
char tic[3][3];

void solve()
{
    memset(tic, '_', sizeof(tic));
    int o = 0, x = 0;
    for (int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < 3; j++)
        {
            tic[i][j] = s[j];
            if (tic[i][j] == 'O')
                o++;
            else if (tic[i][j] == 'X')
                x++;
        }
    }
    if (o > x || o + 1 < x)
    {
        cout << 3 << "\n";
        return;
    }
    int vert = 0LL, hor = 0, diag = 0;
    map<char, int> lines;
    for (int i = 0; i < 3; i++)
    {
        char cur = tic[i][0];
        if (cur == '_')
            continue;
        bool skip = false;
        for (int j = 0; j < 3; j++)
        {
            if (tic[i][j] != cur)
                skip = true;
        }
        if (skip)
            continue;
        lines[cur]++;
        hor++;
    }
    for (int i = 0; i < 3; i++)
    {
        char cur = tic[0][i];
        if (cur == '_')
            continue;
        bool skip = false;
        for (int j = 0; j < 3; j++)
        {
            if (tic[j][i] != cur)
                skip = true;
        }
        if (skip)
            continue;
        lines[cur]++;
        vert++;
    }
    char a = tic[1][1];
    if (a != '_')
    {
        if (tic[0][0] == a && tic[2][2] == a)
        {
            lines[a]++;
            diag++;
        }
        if (tic[0][2] == a && tic[2][0] == a)
        {
            lines[a]++;
            diag++;
        }
    }
    if (vert + hor + diag > 2 || lines.size() == 2 || vert == 2 || hor == 2)
    {
        cout << 3 << "\n";
        return;
    }
    char which = '_';
    for (auto p : lines)
    {
        which = p.first;
    }
    if (which == '_')
    {
        if (o + x == 9)
        {
            cout << 1 << "\n";
        }
        else
        {
            cout << 2 << "\n";
        }
        return;
    }
    if ((which == 'O' && o < x) || (which == 'X' && o == x))
    {
        cout << 3 << "\n";
        return;
    }
    cout << 1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}