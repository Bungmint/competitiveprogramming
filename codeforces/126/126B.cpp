#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;
const long long MOD = 1e9 + 9;
long long p31[1000000 + 7];

void precalc()
{
    for (int i = 0; i < 1000005; i++)
    {
        if (i == 0)
            p31[i] = 1;
        else
            p31[i] = (31 * p31[i - 1]) % MOD;
    }
}

long long mod_pow(long long num, long long exp)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return num;
    long long mid = mod_pow(num, exp / 2);
    if (exp % 2 == 0)
        return (mid * mid) % MOD;
    else
        return (((mid * mid) % MOD) * mid) % MOD;
}

long long compute_hash(const string &str)
{
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_val = 0;
    char c;
    for (int i = 0; i < str.size(); i++)
    {
        c = str[i];
        hash_val = (hash_val + (c - 'a' + 1) * p31[i]) % m;
    }
    return hash_val;
}

vector<long long> gethash(string &s)
{
    long long n = s.length();
    vector<long long> hashs(n, 0);
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        hashs[i] = ((c - 'a' + 1) * p31[i]) % MOD;
        if (i)
            hashs[i] += hashs[i - 1];
        hashs[i] %= MOD;
    }
    return hashs;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    precalc();
    string s;
    cin >> s;
    vector<long long> possible_options;
    long long len = s.length();
    vector<long long> hashes = gethash(s);
    for (int i = 0; i < len; i++)
    {
        long long hash1 = (hashes[i] * p31[len - 1 - i]) % MOD;
        long long hash2 = (i < len - 1) ? (hashes[len - 1] - hashes[len - 2 - i] + MOD) % MOD : hashes[len - 1];
        if (hash1 == hash2)
        {
            possible_options.push_back(i + 1);
        }
    }
    sort(all(possible_options));
    int lo = 0, hi = possible_options.size() - 1;
    int ans = -1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        int length = possible_options[mid];
        bool is_ok = false;
        for (int i = 1; i < len - length; i++)
        {
            long long infix = ((hashes[i + length - 1] - hashes[i - 1] + MOD)) % MOD;
            long long suffix = (hashes[length - 1] * p31[i]) % MOD;
            if (infix == suffix)
                is_ok = true;
        }
        if (is_ok)
        {
            ans = length;
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }
    if (ans == -1)
        cout << "Just a legend"
             << "\n";
    else
        for (int i = 0; i < ans; i++)
        {
            cout << s[i];
        }
    cout << "\n";
    return 0;
}