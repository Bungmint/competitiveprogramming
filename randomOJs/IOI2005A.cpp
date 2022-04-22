// Problem: A. Garden 
// Contest: Yandex - IOI 2005
// URL: https://contest.yandex.com/ioi/contest/566/problems/A/
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

// inline namespace RecursiveLambda{
	// template <typename Fun>
	// struct y_combinator_result{
		// Fun fun_;
		// template <typename T> 
		// explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		// template <typename...Args>
		// decltype(auto) operator()(Args &&...args){
			// return fun_(ref(*this), forward<Args>(args)...);
		// }
	// };
	// template <typename Fun>
	// decltype(auto) y_combinator(Fun &&fun){
		// return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	// }
// };

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

int pref[251][251];
int dpL[256], dpR[256];
int l, w, n, K;
int ans = INF;

void solve()
{
	cin >> l >> w >> n >> K;
	FOR(i, 0, n) {
		int x, y;
		cin >> x >> y;
		pref[x][y]++;
	}
	FOR(i, 1, l + 1) FOR(j, 1, 1 + w) {
		pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
	}
	fill(dpL, dpL + 256, INF);
	fill(dpR, dpR + 256, INF);
	auto calc = [&](int a, int b, int c, int d) {
		return pref[b][d] - pref[a - 1][d] - pref[b][c - 1] + pref[a - 1][c - 1];
	};
	FOR(i, 1, l + 1) {
		dpL[i] = dpL[i - 1];
		FOR(j, 1, w + 1) {
			FOR(k, j, w + 1) {
				int L = 1, R = i, res = -1;
				while (L <= R) {
					int mid = (L + R) / 2;
					int z = calc(mid, i, j, k);
					if (z == K) {
						res = mid;
						L = mid + 1;
					}else if (z < K) {
						R = mid - 1;
					}else {
						L = mid + 1;
					}
				}
				if (res != -1) {
					ckmin(dpL[i], 2 * (i - res + 1 + k - j + 1));
				}
			}
		}
	}
	ROF(i, 1, l + 1) {
		dpR[i] = dpR[i + 1];
		FOR(j, 1, w + 1) {
			FOR(k, j, w + 1) {
				int L = i, R = l, res = -1;
				while (L <= R) {
					int mid = (L + R) / 2;
					int z = calc(i, mid, j, k);
					if (z == K) {
						res = mid;
						R = mid - 1;
					}else if (z < K) {
						L = mid + 1;
					}else {
						R = mid - 1;
					}
				}
				if (res != -1) {
					ckmin(dpR[i], 2 * (res - i + 1 + k - j + 1));
				}
			}
		}
	}
	FOR(i, 1, l + 1) {
		if (dpL[i] == INF || dpR[i + 1] == INF) continue;
		ckmin(ans, dpL[i] + dpR[i + 1]);
	}
	fill(dpL, dpL + 256, INF);
	fill(dpR, dpR + 256, INF);
	FOR(i, 1, w + 1) {
		dpL[i] = dpL[i - 1];
		FOR(j, 1, l + 1) {
			FOR(k, j, l + 1) {
				int L = 1, R = i, res = -1;
				while (L <= R) {
					int mid = (L + R) / 2;
					int z = calc(j, k, mid, i);
					if (z == K) {
						res = mid;
						L = mid + 1;
					}else if (z < K) {
						R = mid - 1;
					}else {
						L = mid + 1;
					}
				}
				if (res != -1) {
					ckmin(dpL[i], 2 * (i - res + 1 + k - j + 1));
				}
			}
		}
	}
	ROF(i, 1, w + 1) {
		dpR[i] = dpR[i + 1];
		FOR(j, 1, l + 1) {
			FOR(k, j, l + 1) {
				int L = i, R = w, res = -1;
				while (L <= R) {
					int mid = (L + R) / 2;
					int z = calc(j, k, i, mid);
					if (z == K) {
						res = mid;
						R = mid - 1;
					}else if (z < K) {
						L = mid + 1;
					}else {
						R = mid - 1;
					}
				}
				if (res != -1) {
					ckmin(dpR[i], 2 * (res - i + 1 + k - j + 1));
				}
			}
		}
	}
	FOR(i, 1, l + 1) {
		if (dpL[i] == INF || dpR[i + 1] == INF) continue;
		ckmin(ans, dpL[i] + dpR[i + 1]);
	}
	
	if (ans == INF) cout << "NO\n";
	else cout << ans << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}