// TODO: Test imp
/**
 * Extended Euclidean Algorithm 
 * Returns {x, y}, such that ax + by = g 
 * Source: Folklore
 * Verification:
 * Time complexity: O(log(min(a, b)))
 */

template <typename T>
pair<T, T> extended_gcd(T a, T b) {
    if (b == 0) return {1, 0};
    auto [x, y] = extended_gcd(b, a % b);
    T z = x % b;
    if (z < 0) z += b;
    return {z, (1LL - z * a) / b};
}