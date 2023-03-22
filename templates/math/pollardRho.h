/*
 * Description: Miller-Rabin Primality Test And Pollard-Rho
 * Source: rkm0959
 * Verification: https://www.acmicpc.net/problem/5615
 * Time complexity: O(logN) for Miller-Rabin, O(n^{1/4}log^2n) for Pollard-Rho
**/
#include "miscellaneous/template.h"

ll mul(ll a, ll b, ll m) {
    return __int128_t(a) * b % m;
}
ll bin_pow(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, m);
        a = mul(a, a, m);
        b >>= 1LL;
    }
    return res;
}
bool trial(ll n, ll a) {
    if (n % a == 0) return false;
    ll cnt = -1, d = n - 1;
    while (d % 2 == 0) cnt++, d /= 2;
    ll prod = bin_pow(a, d, n);
    if (prod == 1 || prod == n - 1) return true;
    while (cnt--) {
        prod = mul(prod, prod, n);
        if (prod == n - 1) return true;
    }
    return false;
}
bool is_prime(ll n) {
    if (n == 1) return false;
    ll testcase[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (auto &a : testcase) {
        if (n == a) return true;
        if (n > 40 && !trial(n, a)) return false;
    }
    if (n <= 40) return false;
    return true;
}
ll pollardRho(ll N) {
    ll x = rng() % (N - 2) + 2, y = x;
    ll c = rng() % (N - 1) + 1;
    while (true) {
        x = mul(x, x, N) + c; if (x >= N) x -= N;
        y = mul(y, y, N) + c; if (y >= N) y -= N;
        y = mul(y, y, N) + c; if (y >= N) y -= N;
        ll d = gcd(abs(x - y), N);
        if (d == 1) continue;
        if (!is_prime(d)) return pollardRho(d);
        else return d;
    }
}
vl get_factor(ll N) {
    vl res;
    while (N % 2 == 0) res.pb(2), N /= 2;
    while (N != 1 && !is_prime(N)) {
        ll d = pollardRho(N);
        while (N % d == 0) res.pb(d), N /= d;
    }
    if (N != 1) res.pb(N);
    return res;
}