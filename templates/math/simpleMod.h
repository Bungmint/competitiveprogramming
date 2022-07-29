/**
 * Description: Basic Modular Operations assuming 0 <= a, b < MOD
 * Source: Own
 * Verification:
 * Time complexity: O(log(min(a, b))) for modular inverse and mod_pow, other operations are O(1)
 */

namespace Util {
inline namespace ModUtil {

constexpr int MOD = 1e9 + 7; // 998244353
int add(int a, const int& b) { 
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int mul(const int& a, const int& b) { return 1LL * a * b % MOD; }
int sub(int a, const int& b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
int mod_pow(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}
template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1, b = m;
    while (a) {
        T q = b / a;
        u -= q * v, b -= q * a;
        swap(u, v), swap(a, b);
    }
    assert(b == 1);
    if (u < 0) u += m;
    return u;
}

} // namespace ModUtil
} // namespace Util
