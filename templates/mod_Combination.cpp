const int N = 1e6+10;
ll fact[N], inv_fact[N], inv[N];

void precalc()
{
    for (ll i = 0; i < N; i++)
    {
        if (i == 0)
            fact[i] = 1LL;
        else
            fact[i] = (i * fact[i - 1]) % MOD;
    }
    inv[1] = 1;
    for (int i=2;i<N;++i){
    	inv[i] = MOD-(MOD/i)*inv[MOD%i]%MOD;
    }
    inv_fact[0] = inv_fact[1] = 1;
    for (ll i=2;i<N;++i){
    	inv_fact[i] = inv_fact[i-1] * inv[i];
    }
}

ll mod_pow(ll base, ll exp)
{
    if (exp == 0)
        return 1LL;
    if (exp == 1)
        return base;
    ll m = mod_pow(base, exp / 2);
    if (exp % 2 == 0)
        return (m * m) % MOD;
    return (((m * m) % MOD) * base) % MOD;
}

ll inv_mod(ll a)
{
    return mod_pow(a, MOD - 2);
}

ll nCk(ll n, ll k)
{
    if (n < k)
        return 0LL;
    return (((fact[n] * inv_fact[k])) % MOD) * inv_fact[n - k]) % MOD;
}