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

void gray_code(ll x, vector<ll> &vec)
{
    if (x == 1)
    {
        vec.push_back(0);
        vec.push_back(1);
        return;
    }
    gray_code(x - 1, vec);
    for (ll i = (1 << (x - 1)) - 1; i >= 0; i--)
    {
        vec.push_back(vec[i] + (1 << (x - 1)));
    }
}

void solve()
{
    ll n;
    cin >> n;
    vector<ll> vec;
    gray_code(n, vec);
    for (auto x : vec)
    {
        bitset<16> bits(x);
        cout << bits.to_string().substr(16 - n) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}