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

constexpr int M = 2011;
char grid[M][M];
int dp[M][M];
pii chain_end[M][M];

void solve(int tc) {
	int n;
	cin >> n;
	memset(dp, 0, sizeof(dp));
	int tot{}; 
	ll ans{};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == '.') tot++;
		}
	}
	ans = 1LL * tot * (tot - 1) / 2LL;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (grid[i][j] == '#') {
				if (j + 1 < n && grid[i][j + 1] == '#') {
					chain_end[i][j] = chain_end[i][j + 1];
				}else if (i + 1 == n) {
					chain_end[i][j] = {i, j};
				}else{
					if (grid[i + 1][j] == '#') {
						chain_end[i][j] = chain_end[i + 1][j];
					}else if (j + 1 < n && grid[i + 1][j + 1] == '#') {
						chain_end[i][j] = chain_end[i + 1][j + 1];
					}else{
						chain_end[i][j] = {i, j};
					}
				}
			}
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (grid[i][j] == '#') continue;
			if (i == n - 1 && j == n - 1) {
				dp[i][j] = 1;
			}else if (i == n - 1) {
				dp[i][j] = dp[i][j + 1] + 1;
			}else if (j == n - 1) {
				dp[i][j] = dp[i + 1][j] + 1;
			}else{
				if (grid[i][j + 1] == '#') {
					dp[i][j] = 1 + dp[i + 1][j];
				}else if (grid[i + 1][j] == '#') {
					dp[i][j] = 1 + dp[i][j + 1];
				}else{
					dp[i][j] = 1 + dp[i + 1][j] + dp[i][j + 1];
					if (grid[i + 1][j + 1] == '#') {
						auto [r, c] = chain_end[i + 1][j + 1];
						dp[i][j] -= dp[r + 1][c + 1];
					}else{
						dp[i][j] -= dp[i + 1][j + 1];
					}
				}
			}
			ans -= dp[i][j] - 1;
		}
	}
	cout << "Case #" << tc << endl;
	cout << ans << endl;
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