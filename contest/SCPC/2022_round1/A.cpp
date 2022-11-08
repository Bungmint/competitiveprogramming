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

constexpr int MX = 3e5 + 100;
int a[MX], v[MX], id[MX];
long long ans{};


void solve(int tc) {
	int n;
	cin >> n;
	ans = 0;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> v[i];
	iota(id, id + n, 0);
	sort(id, id + n, [&](int i, int j){
		return v[i] != v[j] ? v[i] < v[j] : a[i] < a[j];
	});
	for (int i = 0; i < n; i++) {
		ans += abs(a[id[i]] - a[i]);
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