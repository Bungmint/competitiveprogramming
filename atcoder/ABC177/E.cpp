#include <bits/stdc++.h>

using namespace std;

vector<int> sieve(int num)
{
    vector<bool> A(num + 1, true);
    vector<int> primes;
    A[0] = false, A[1] = false;
    for (int i = 2; i * i <= num; i++)
    {
        if (A[i])
        {
            for (int j = i * i; j <= num; j += i)
            {
                A[j] = false;
            }
        }
    }
    for (int i = 0; i <= num; i++)
    {
        if (A[i])
            primes.push_back(i);
    }
    return primes;
}
vector<int> primes = sieve(1e3);

int main()
{
    int n;
    cin >> n;
    int total_gcd;
    bool all_coprime = true;
    unordered_set<int> alr_found;
    int prev = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (prev == tmp)
            all_coprime = false;
        if (i == 0)
            total_gcd = tmp;
        total_gcd = gcd(total_gcd, tmp);
        if (all_coprime)
        {
            for (int j = 0; j < primes.size(); j++)
            {
                if (tmp < primes[j])
                    break;
                if (tmp % primes[j] == 0)
                {
                    if (alr_found.count(primes[j]) == 1)
                    {
                        all_coprime = false;
                        break;
                    }
                    while (tmp % primes[j] == 0)
                    {
                        tmp /= primes[j];
                    }
                    alr_found.insert(primes[j]);
                }
            }
            if (tmp > 1)
            {
                if (alr_found.count(tmp) == 1)
                {
                    all_coprime = false;
                    break;
                }
                else
                {
                    alr_found.insert(tmp);
                }
            }
        }
    }
    if (total_gcd != 1)
    {
        cout << "not coprime"
             << "\n";
    }
    else if (all_coprime)
    {
        cout << "pairwise coprime"
             << "\n";
    }
    else
    {
        cout << "setwise coprime"
             << "\n";
    }
}