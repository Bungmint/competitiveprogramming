// Problem: The last digit
// Contest: SPOJ - Classical
// URL: https://www.spoj.com/problems/LASTDIG/
// Memory Limit: 1536 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll binPow(ll a, ll b){
	ll res = 1;
	while (b){
		if (b & 1) (res *= a) %= 10;
		(a *= a) %= 10;
		b >>= 1;
	}
	return res;
}

void solve()
{
	ll a, b;
	cin >> a >> b;
	cout << binPow(a, b) << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}