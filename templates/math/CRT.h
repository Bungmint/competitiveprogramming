/**
 * Chinese Remainder Theorem Solver
 * Source: rkm0959's github
 * Verification: BOJ rkm0959's third problemset
 * Time complexity: O(log(A.se, B.se))
 */

#include "simpleMod.h" 

pll crt(pll A, pll B) {
	if (A.se == -1 || B.se == -1) return {-1, -1};
	if (A.se == 1 || B.se == 1) return A.se == 1 ? B : A;
	ll g = gcd(A.se, B.se), l = (A.se / g) * B.se;
	if ((B.fi - A.fi) % g) return {-1, -1};
	ll a = A.se / g, b = B.se / g;
	ll mul = (B.fi - A.fi) / g;
	mul = (mul * inverse(a, b)) % b;
	ll ret = mul * A.se + A.fi;
	ret %= l, ret = (ret + l) % l;
	return {ret, l};
}