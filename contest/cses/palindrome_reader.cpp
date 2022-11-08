//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    string s;
    cin >> s;
    map<char, int> map1;
    for (int i = 0; i < s.length(); i++)
    {
        map1[s[i]]++;
    }
    string part1 = "";
    char special = '0';
    bool is_pos = true;
    if (s.length() % 2 == 0)
    {
        for (auto p : map1)
        {
            if (p.second % 2 == 1)
            {
                is_pos = false;
                break;
            }
            for (int i = 0; i < p.second / 2; i++)
            {
                part1 += p.first;
            }
        }
    }
    else
    {
        int odds = 0;
        for (auto p : map1)
        {
            if (p.second % 2 == 1)
            {
                odds++;
                special = p.first;
                if (odds > 1)
                {
                    is_pos = false;
                    break;
                }
            }
            for (int i = 0; i < p.second / 2; i++)
            {
                part1 += p.first;
            }
                }
    }
    if (is_pos)
    {
        string part2 = part1;
        if (special != '0')
            part1 += special;
        reverse(all(part2));
        part1 += part2;
        cout << part1 << "\n";
    }
    else
    {
        cout << "NO SOLUTION"
             << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}