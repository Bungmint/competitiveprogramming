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
string ans, s;
vector<bool> chosen;
set<string> set1;
int N;

void perms()
{
    if (ans.length() == N)
    {
        if (set1.count(ans) == 0)
        {
            set1.insert(ans);
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            if (!chosen[i])
            {
                chosen[i] = true;
                ans.push_back(s[i]);
                perms();
                chosen[i] = false;
                ans.pop_back();
            }
        }
    }
}

void solve()
{
    cin >> s;
    N = s.length();
    chosen.resize(N, false);
    perms();
    cout << set1.size() << "\n";
    for (auto x : set1)
    {
        cout << x << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}