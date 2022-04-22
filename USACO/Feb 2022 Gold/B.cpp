#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;
using ld = long double;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, b) FOR(i, 0, b)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define pb push_back


const int INF = 1e9;
const ll LINF = 1e18;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
template<typename T>
bool ckmin(T& a, const T& b) {
	return (a > b ? a = b, 1 : 0);
}
template<typename T>
bool ckmax(T& a, const T& b) {
	return (a < b ? a = b, 1 : 0);
}


void dbg_out(){
	cerr << endl;
}
template<typename Head, typename...Tail>
void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H;
	dbg_out(T...);
}

#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif



void setIO() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}

const ld EPS = 1e-9;
const int N = 1e3 + 3;

ld binPow(ld a, int k) {
	ld res = 1;
	while (k) {
		if (k & 1) res *= a;
		a *= a;
		k >>= 1;
	}
	return res;
}

ld dp[N][N];
ld ex[N];
ld cumP[N];

void solve() {
	int t, k;
	cin >> t >> k;
	dp[1][1] = 1;
	FOR(tt, 2, t + 1) {
		FOR(i, 1, tt + 1) {
			dp[tt][i] += dp[tt - 1][i] / 2;
			dp[tt][i] += dp[tt - 1][i - 1] / (ld)2;
			// dbg(dp[tt][i], i, tt);
		}
	}
	ROF(i, 1, t + 1) {
		ex[i] = ex[i + 1] + dp[t][i] * i;
		cumP[i] = cumP[i + 1] + dp[t][i];
		dbg(i, ex[i], cumP[i]);
	}
	ld previous = 0, ans = 0;
	FOR(i, 1, k + 1) {
		if (i == 1) {
			ans = (ld) (t + 1) / 2;
			previous = ans;
			continue;
		}
		int x = ceil(previous);
		int l = i, r = k, nxt = i;
		while (l <= r) {
			int mid = (l + r) / 2;
			ld val = ex[x] * ((ld)1 - binPow((ld)1 - cumP[x], mid - i)) / cumP[x] + previous * binPow((ld)1 - cumP[x], mid - i);
			int y = ceil(val);
			if (x < y) r = mid - 1;
			else l = mid + 1, nxt = mid;
		}
		ans = ex[x] * ((ld)1 - binPow((ld)1 - cumP[x], nxt + 1 - i)) / cumP[x] + previous * binPow((ld)1 - cumP[x], nxt + 1 - i);
		previous = ans;
		i = nxt;
	}
	cout << ans;
}



int main() {
	setIO();
	cout << fixed << setprecision(20);
	solve();
}