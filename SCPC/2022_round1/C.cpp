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
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define sz(x) (int)(x).size()

/*
 * Solution: Sweepline + Observation
 * Observation: If there is odd number of nodes with the same x-values,
 * one of them is fake
 */

constexpr int MX = 1e5 + 100;
int x[MX], y[MX], on_l[MX], on_r[MX];
vector<int> x_index[MX];
vector<int> xs, ys;

int get_x(int xx) {
	return lower_bound(all(xs), xx) - xs.begin();
}
int get_y(int yy) {
	return lower_bound(all(ys), yy) - ys.begin();
}

void solve(int tc) {
	int n;
	cin >> n;
	ll ans{};
	xs.clear(), ys.clear();
	memset(on_l, -1, sizeof(on_l));
	memset(on_r, -1, sizeof(on_r));
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		xs.pb(x[i]), ys.pb(y[i]);
	}
	sort(all(xs)), sort(all(ys));
	xs.erase(unique(all(xs)), end(xs));
	ys.erase(unique(all(ys)), end(ys));
	for (int i = 0; i < sz(xs); i++) {
		x_index[i].clear();
	}
	for (int i = 0; i < n; i++) {
		x[i] = get_x(x[i]);
		y[i] = get_y(y[i]);
		x_index[x[i]].pb(i);
	}
	int issue = -1;
	for (int i = 0; i < sz(xs); i++) {
		sort(all(x_index[i]), [&](int lhs, int rhs) {
			return y[lhs] < y[rhs];
		});
		if (sz(x_index[i]) & 1) {
			issue = i;
		}else{
			for (int j = 0; j < sz(x_index[i]); j += 2) {
				int cur = x_index[i][j], nxt = x_index[i][j + 1];
				ans += ys[y[nxt]] - ys[y[cur]];
			}
		}
	}
	if (issue == -1) {
		for (int i = 0; i < sz(xs); i++) {
			for (auto &id : x_index[i]) {
				if (on_l[y[id]] >= 0) {
					ans += xs[i] - xs[on_l[y[id]]];
					on_l[y[id]] = -1;
				}else{
					on_l[y[id]] = i;
				}
			}
		}
	}else{
		for (int i = 0; i < issue; i++) {
			for (auto &id : x_index[i]) {
				if (on_l[y[id]] >= 0) {
					ans += xs[i] - xs[on_l[y[id]]];
					on_l[y[id]] = -1;
				}else{
					on_l[y[id]] = i;
				}
			}
		}
		for (int i = sz(xs) - 1; i > issue; i--) {
			for (auto &id : x_index[i]) {
				if (on_r[y[id]] >= 0) {
					ans += -xs[i] + xs[on_r[y[id]]];
					on_r[y[id]] = -1;
				}else{
					on_r[y[id]] = i;
				}
			}
		}
		int y_prev = -1;
		for (auto &id : x_index[issue]) {
			if (on_l[y[id]] == on_r[y[id]] && on_l[y[id]] == -1) {
				continue;
			}
			if (on_l[y[id]] >= 0 && on_r[y[id]] >= 0) {
				ans += xs[on_r[y[id]]] - xs[on_l[y[id]]];
				on_l[y[id]] = on_r[y[id]] = -1;
				continue;
			}
			if (on_l[y[id]] >= 0) {
				ans += xs[issue] - xs[on_l[y[id]]];
				on_l[y[id]] = -1;
			}else{
				ans += -xs[issue] + xs[on_r[y[id]]];
				on_r[y[id]] = -1;
			}
			if (y_prev >= 0) {
				ans += ys[y[id]] - ys[y_prev];
				y_prev = -1;
			}else{
				y_prev = y[id];
			}
		}
		for (int i = 0; i < sz(ys); i++) {
			if (on_l[i] >= 0 && on_r[i] >= 0) {
				ans += xs[on_r[i]] - xs[on_l[i]];
			}
		}
	}
	cout << "Case #" << tc << '\n';
	cout << ans << '\n';
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
