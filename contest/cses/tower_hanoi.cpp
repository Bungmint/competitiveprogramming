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

ll pow(ll base, ll exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    ll mid = pow(base, exp / 2);
    if (exp % 2 == 0)
        return mid * mid;
    else
        return mid * mid * base;
}

void hanoi(int x, int start, int end)
{
    if (x == 1)
    {
        cout << start << " " << end << "\n";
        return;
    }
    if (end == 1)
    {
        if (start == 2)
        {
            hanoi(x - 1, 2, 3);
            hanoi(1, 2, 1);
            hanoi(x - 1, 3, 1);
        }
        else if (start == 3)
        {
            hanoi(x - 1, 3, 2);
            hanoi(1, 3, 1);
            hanoi(x - 1, 2, 1);
        }
    }
    else if (end == 2)
    {
        if (start == 1)
        {
            hanoi(x - 1, 1, 3);
            hanoi(1, 1, 2);
            hanoi(x - 1, 3, 2);
        }
        else if (start == 3)
        {
            hanoi(x - 1, 3, 1);
            hanoi(1, 3, 2);
            hanoi(x - 1, 1, 2);
        }
    }
    else
    {
        if (start == 1)
        {
            hanoi(x - 1, 1, 2);
            hanoi(1, 1, 3);
            hanoi(x - 1, 2, 3);
        }
        else if (start == 2)
        {
            hanoi(x - 1, 2, 1);
            hanoi(1, 2, 3);
            hanoi(x - 1, 1, 3);
        }
    }
}

void solve()
{
    ll n;
    cin >> n;
    cout << pow(2LL, n) - 1 << "\n";
    hanoi(n, 1, 3);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}