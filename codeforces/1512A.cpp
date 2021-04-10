#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    unordered_map<int, int> map1;
    map1.reserve(1024);
    map1.max_load_factor(0.25);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        vec[i] = tmp;
        map1[tmp] += 1;
    }
    int spy = -1;
    for (auto v : map1)
    {
        if (v.second == 1)
            spy = v.first;
    }
    for (int i = 0; i < n; i++)
    {
        if (vec[i] == spy)
        {
            cout << i + 1 << "\n";
        }
    }
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
}
