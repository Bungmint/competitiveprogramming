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
    int n, tmp;
    cin >> n;
    unordered_map<int, int> map1;
    map1.reserve(1024);
    map1.max_load_factor(0.25);
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        map1[tmp] += 1;
    }
    cout << map1.size() << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}