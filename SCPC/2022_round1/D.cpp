#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <chrono>
#include <random>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <iomanip>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

/*
 * Solution: Z-algorithm/KMP to match patterns
 */

constexpr int M = 1e6 + 100;
int pref[M][2];
int z[M * 2];
char c[M * 2];

void calc_z(int tot) {
	for (int i = 0; i < tot; i++) z[i] = 0;
	for (int i = 1, l = 0, r = 0; i < tot; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < tot && c[z[i]] == c[i + z[i]]) {
			z[i]++;
		}
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

void solve(int tc) {
	int n, m;
	cin >> n >> m;
	string s, t;
	cin >> s >> t;
	cout << "Case #" << tc << '\n';
	int fr = t[0] - 'a', bk = t[m - 1] - 'a';
	int first = -1, last = -1;
	for (int i = 0; i < m; i++) {
		int cur = t[i] - 'a';
		if (first == -1 && fr != cur) {
			first = i;
		}
	}
	for (int i = m - 1; i >= 0; i--) {
		if (last == -1 && bk != t[i] - 'a') {
			last = i;
			break;
		}
	}
	if (first == -1) { // one component
		for (int i = 0; i < n; i++) {
			if (fr == s[i] - 'a') m--;
		}
		cout << (m <= 0 ? "YES" : "NO") << '\n';
		return;
	}else if (first > last) {
		int fcnt = first, lcnt = m - first;
		for (int i = 0; i < n; i++) {
			if (fr == s[i] - 'a') {
				fcnt--;
				if (fcnt == 0) {
					for (int j = i + 1; j < n; j++) {
						if (bk == s[j] - 'a') {
							lcnt--;
						}
					}
					cout << (lcnt <= 0 ? "YES" : "NO") << '\n';
					return;
				}
			}
		}
		cout << "NO\n";
	}else{
		int len = last - first + 1;
		const int fcnt = first, lcnt = m - 1 - last;
		for (int i = 0; i < len; i++) c[i] = t[i + first];
		c[len] = 'c';
		for (int i = 0; i < n; i++) c[i + len + 1] = s[i];
		calc_z(n + len + 1);
		for (int i = 0; i < n; i++) {
			if (i) {
				pref[i][0] = pref[i - 1][0];
				pref[i][1] = pref[i - 1][1];
			}
			pref[i][s[i] - 'a']++;
		}
		for (int i = 1; i < n + 1 - len; i++) {
			if (z[i + len + 1] == len) {
				if (pref[i - 1][fr] >= fcnt && pref[n - 1][bk] - pref[i + len - 1][bk] >= lcnt) {
					cout << "YES\n";
					return;
				}
			}
		}
		cout << "NO\n";
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	for (int i = 1; i <= testcase; i++) {
		solve(i);
	}
	return 0;
}
