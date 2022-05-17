#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long l, r;
    cin >> l >> r;
    while (__builtin_clzll(l) == __builtin_clzll(r) && r > 0)
    {
        r -= 1LL << (63 - __builtin_clzll(r));
        l -= 1LL << (63 - __builtin_clzll(l));
    }
    (r) ? cout << (1LL << (64 - __builtin_clzll(r))) - 1 << "\n" : cout << 0 << "\n";
    return 0;
}