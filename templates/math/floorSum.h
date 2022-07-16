// TODO : test imp
/**
 * Floor sum of the form $\frac{ax+b}{c}$ where a, b >= 0, c > 0
 * Source: OI Wiki (Chinese)
 * Verification: 
 * Time complexity : O(log(min(n, a))) (Euclidean-like)
 */
ll floor_sum(ll a, ll b, ll c, ll n) {
    if (!a) return (b / c) * (n + 1);
    if (a >= c || b >= c) {
        return ((a / c) * n + (b / c) * 2) * (n + 1) / 2 + floor_sum(a % c, b % c, c, n);
    }
    ll m = (a * n + b) / c;
    return m * n - floor_sum(c, c - b - 1, a, m - 1); 
}