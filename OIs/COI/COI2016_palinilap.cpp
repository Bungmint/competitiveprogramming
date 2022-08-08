//Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#define int long long
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

constexpr int B = 9973;

int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}
int mul(int a, int b) {
	return 1LL * a * b % MOD;
}
int sub(int a, int b) {
	a -= b;
	if (a < 0) a += MOD;
	return a;
}
int binPow(int a, int b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = (res * a) % MOD;
		a = (1LL * a * a) % MOD;
		b >>= 1LL;
	}
	return res;
}


struct HashRange {
	vi t, power, inv;
	HashRange(string &s) {
		int n = sz(s);
		t.resize(n + 1);
		power.resize(n + 1);
		inv.resize(n + 1);
		power[0] = inv[0] = 1;
		inv[1] = binPow(B, MOD - 2);
		FOR(i, 1, n + 1) inv[i] = mul(inv[i - 1], inv[1]);
		FOR(i, 1, n + 1) power[i] = mul(power[i - 1], B);
		F0R(i, n) {
			t[i + 1] = add(t[i], mul(power[i], s[i]));
		}
	}
	int calcHash(int l, int r) { // 0 - indexed
		return mul(sub(t[r + 1], t[l]), inv[l]);
	}
};

void solve()
{
	string s, t;
	cin >> s;
	int n = sz(s);
	F0R(i, n) {
		t += '#';
		t += s[i];
	}
	t += '#';
	HashRange hshF(t);
	reverse(all(t));
	HashRange hshB(t);
	int nn = sz(t);
	vi rd(nn);
	vector<vi> a(nn, vi(26));
	ll tot{}, ans{0};
	reverse(all(t));
	F0R(i, nn) {
		int l = 0, r = min(i, nn - 1 - i), ret = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (hshF.calcHash(i, i + mid) == hshB.calcHash(nn - 1 - i, nn - 1 - i + mid)) {
				ret = mid; l = mid + 1;
			}else r = mid - 1;
		}
		rd[i] = ret;
		if (i & 1) {
			tot += (ret + 1) / 2;
		}else tot += ret / 2;
		
		if (i - ret > 0 && i + ret + 1 < nn) {
			char c = t[i + ret + 1];
			char d = t[i - ret - 1];
			dbg(i, c, d);
			l = 1, r = min(i - ret - 1, nn - 1 - i - ret - 1);
			int z = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (hshF.calcHash(i + ret + 2, i + ret + 1 + mid) == hshB.calcHash(nn - 1 - (i - ret - 2), nn - 1 - (i - ret - 1) + mid)) {
					z = mid, l = mid + 1;
				}else r = mid - 1;
			}
			a[i - ret - 1][c - 'a'] += z / 2 + 1;
			a[i + ret + 1][d - 'a'] += z / 2 + 1;
			dbg(z);
		}
	}
	int sum{}, cnt{};
	vpi fr(nn);
	vpi bk(nn);
	F0R(i, nn) {
		char c = t[i];
		if (c != '#') {
			int z = (sum - (i + 1) * cnt) / 2 + cnt;
			F0R(j, 26) {
				if (j == c - 'a') continue;
				a[i][j] -= z;
			}
		}
		sum += i + rd[i];
		cnt++;
		fr[i + rd[i]].fi += i + rd[i];
		fr[i + rd[i]].se++;
		sum -= fr[i].fi;
		cnt -= fr[i].se;
	}
	cnt = sum = 0;
	R0F(i, nn) {
		char c = t[i];
		if (c != '#') {
			int z = ((i - 1) * cnt - sum) / 2 + cnt;
			dbg(z);
			F0R(j, 26) {
				if (j == c - 'a') continue;
				a[i][j] -= z;
			}
		}
		sum += i - rd[i];
		cnt++;
		bk[i - rd[i]].fi += i - rd[i];
		bk[i - rd[i]].se++;
		sum -= bk[i].fi;
		cnt -= bk[i].se;
	}
	F0R(i, nn) {
		if (i & 1) {
			F0R(j, 26) {
				ckmax(ans, tot + a[i][j]);
			}
		}
	}
	cout << ans << '\n';
	
}

int32_t main()
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