#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
vector<int> arr[101];
bool check[101];

void dfs(int x, const vector<vector<int>> &lang)
{
    if (check[x])
        return;
    check[x] = true;
    for (auto lan : lang[x])
    {
        for (auto y : arr[lan])
        {
            dfs(y, lang);
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> lang(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int tmp;
            cin >> tmp;
            lang[i].push_back(tmp);
            arr[tmp].push_back(i);
        }
    }
    int counter = 0;
    bool nobody = true;
    for (int i = 0; i < n; i++)
    {
        if (check[i])
            continue;
        if (lang[i].size() != 0)
            nobody = false;
        dfs(i, lang);
        counter++;
    }
    if (!nobody)
        counter--;
    cout << counter << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}