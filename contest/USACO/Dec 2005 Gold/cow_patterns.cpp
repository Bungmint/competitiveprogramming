// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <iostream>
#include <cstring>
#include <vector>

const int NAX = 1e5 + 100;
int a[NAX], pi[NAX * 2], n, k, s;
int chk[25100], early[30], max_chk;
int b[NAX * 2];
std::vector<int> ans;

void solve() {
	std::cin >> n >> k >> s;
	for (int i = 0; i < n; i++) std::cin >> a[i];
	for (int i = 0; i < k; i++) std::cin >> chk[i], max_chk = std::max(chk[i], max_chk);
	memset(early, -1, sizeof(early));
	for (int i = k - 1; i >= 0; i--) early[chk[i]] = i;
	for (int i = 0; i < k; i++) b[i] = chk[i];
	b[k] = 100;
	for (int i = k + 1; i < k + n + 1; i++) b[i] = a[i - 1 - k];
	for (int i = 1, j = 0; i < k; i++) {
		while (j > 0) {
			int id = early[chk[j]];
			if (id == j) {
				bool bad = 0;
				for (int x = 1; x <= max_chk; x++) {
					if (early[x] < j && x != chk[j]) {
						if (x < chk[j]) {
							if (b[i - (j - early[x])] >= b[i]) {
								bad = 1;
								break;
							}
						}else{
							if (b[i - (j - early[x])] <= b[i]) {
								bad = 1;
								break;
							}
						}
					}
				}
				if (bad) j = pi[j - 1];
				else break;
			}else{
				if (b[i] != b[i - (j - id)]) {
					j = pi[j - 1];
				}else{
					break;
				}
			}
		}
		int id = early[chk[j]];
		if (id == j) {
			bool bad = 0;
			for (int x = 1; x <= max_chk; x++) {
				if (early[x] < j && x != chk[j]) {
					if (x < chk[j]) {
						if (b[i - (j - early[x])] >= b[i]) {
							bad = 1;
							break;
						}
					}else{
						if (b[i - (j - early[x])] <= b[i]) {
							bad = 1;
							break;
						}
					}
				}
			}
			if (!bad) j++;
		}else{
			if (b[i] == b[i - (j - id)]) j++;
		}
		pi[i] = j;
	}
	for (int i = k + 1, j = 0; i < k + n + 1; i++) {
		while (j > 0) {
			if (j == k) {
				j = pi[j - 1];
				continue;
			}
			int id = early[chk[j]];
			if (id == j) {
				bool bad = 0;
				for (int x = 1; x <= max_chk; x++) {
					if (early[x] < j && x != chk[j]) {
						if (x < chk[j]) {
							if (b[i - (j - early[x])] >= b[i]) {
								bad = 1;
								break;
							}
						}else{
							if (b[i - (j - early[x])] <= b[i]) {
								bad = 1;
								break;
							}
						}
					}
				}
				if (bad) j = pi[j - 1];
				else break;
			}else{
				if (b[i] != b[i - (j - id)]) {
					j = pi[j - 1];
				}else{
					break;
				}
			}
		}
		int id = early[chk[j]];
		if (id == j) {
			bool bad = 0;
			for (int x = 1; x <= max_chk; x++) {
				if (early[x] < j && x != chk[j]) {
					if (x < chk[j]) {
						if (b[i - (j - early[x])] >= b[i]) {
							bad = 1;
							break;
						}
					}else{
						if (b[i - (j - early[x])] <= b[i]) {
							bad = 1;
							break;
						}
					}
				}
			}
			if (!bad) j++;
		}else{
			if (b[i] == b[i - (j - id)]) j++;
		}
		pi[i] = j;
		// std::cerr << "\033[1;35m" << i << ' ' << b[i] << ' ' << pi[i] << "\033[0m" << std::endl;
		if (j == k) ans.push_back(i - 2*k + 1);
	}
	std::cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << '\n';
	}
	// std::cout << ans << '\n';
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin.exceptions(std::cin.failbit);
	int testcase = 1;
	while (testcase--) {
		solve();
	}
}
