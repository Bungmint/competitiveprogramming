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
    deque<int> soldier1, soldier2;
    int k1, k2;
    cin >> k1;
    for (int i = 0; i < k1; i++)
    {
        int tmp;
        cin >> tmp;
        soldier1.push_back(tmp);
    }
    cin >> k2;
    for (int i = 0; i < k2; i++)
    {
        int tmp;
        cin >> tmp;
        soldier2.push_back(tmp);
    }
    int counter = 0;
    while (soldier1.size() > 0 && soldier2.size() > 0 && counter < 1000)
    {
        int top1 = soldier1.front();
        int top2 = soldier2.front();
        soldier1.pop_front();
        soldier2.pop_front();
        if (top1 > top2)
        {
            soldier1.push_back(top2);
            soldier1.push_back(top1);
        }
        else
        {
            soldier2.push_back(top1);
            soldier2.push_back(top2);
        }
        counter++;
    }
    if (counter >= 1000)
        cout << -1 << "\n";
    else
    {
        if (soldier1.size() == 0)
        {
            cout << counter << " " << 2 << "\n";
        }
        else
        {
            cout << counter << " " << 1 << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}