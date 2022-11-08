#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;

int n; LL m;
 
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod f(2);
 
LL mul(LL x, LL y) {
    return f.reduce(x * y);
}
 
LL add(LL x, LL y) {
    x += y;
    if (x >= m) x -= m;
    return x;
}
 
LL sub(LL x, LL y) {
    x -= y;
    if (x < 0) x += m;
    return x;
}
 
LL powmod(LL a, LL b) {LL res=1; a %= (m+1); for(;b;b>>=1) {if (b&1) res = res*a % (m+1); a = a*a % (m+1);} return res;}
 
const int MAXN = 7505;
LL factorial[MAXN], c[MAXN][MAXN];
 
int main() {
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    cin >> n >> m;
 
    m--;
    f = FastMod(m);
 
    factorial[0] = 1;
    for (int i = 1; i < MAXN; ++i) factorial[i] = mul(factorial[i-1], i);
 
    c[1][0] = c[1][1] = 1;
    for (int i = 2; i < MAXN; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) c[i][j] = add(c[i-1][j-1], c[i-1][j]);
    }
 
    vector<int> composite(MAXN);
 
    LL ans = 1;
 
    for (int i = 2; i <= n; i++) {
        if (!composite[i]) {
            for (int j = i; j <= n; j *= i) {
                // count permutations of length j*k where ALL cycles are divisible by j
                vector<LL> aj(n/j+1);
                aj[0] = 1;
 
                for (int k = 1; k < n/j+1; k++) {
                    for (int l = 1; l <= k; l++) {
                        aj[k] = add(aj[k], mul(mul(c[j*k-1][j*l-1], factorial[j*l-1]), aj[k-l]));
                    }
                }
 
                // count permutations of length n-j*k where NO cycle is divisible by j
                vector<LL> nj(n/j+1);
 
                for (int k = n/j; k >= 0; k--) {
                    nj[k] = factorial[n-j*k];
                    for (int l = k+1; l <= n/j; l++) {
                        nj[k] = sub(nj[k], mul(c[n-j*k][n-l*j], mul(aj[l-k], nj[l])));
                    }
                }
 
                ans = (ans * powmod(i, sub(factorial[n], nj[0]))) % (m+1);
            }
 
            for (int j = 2*i; j <= n; j += i) {
                composite[j] = 1;
            }
        }
    }
 
    printf("%lld\n", ans);
}
