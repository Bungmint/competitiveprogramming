/**
 * Description: Tests primality up to SZ [1, SZ)
 * Source: Benq
 * Time complexity: O(SZ log log SZ) or O(SZ)
 */

template <int SZ>
struct Sieve {
    bitset<SZ> is_prime;
    vi primes;
    Sieve() {
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
        for (int i = 3; i * i < SZ; i += 2) {
            if (is_prime[i]) {
                for (int j = i * i; j < SZ; j += 2 * i) {
                    is_prime[j] = 0;
                }
            }
        }
        for (int i = 0; i < SZ; i++) if (is_prime[i]) primes.pb(i);
    }
    // int lp[SZ];
    // Sieve() {
    //     for (int i = 2; i < SZ; i++) {
    //         if (lp[i] == 0) lp[i] = i, primes.pb(i);
    //         for (int p : primes) {
    //             if (p > lp[i] || i * p >= SZ) break;
    //             lp[i * p] = p;
    //         }
    //     }
    // }
};