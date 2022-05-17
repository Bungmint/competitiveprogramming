const int MAXN = 1e6+1;

vector<int> prime;
bool is_composite[MAXN];

void sieve () {
	std::fill(is_composite, is_composite + MAXN, false);
	for (int i = 2; i < MAXN; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < MAXN; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}