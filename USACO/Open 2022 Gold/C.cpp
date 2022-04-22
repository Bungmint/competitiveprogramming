#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
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
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, b) FOR(i, 0, b)
#define REP(a) F0R(_, a)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define R0F(i, b) ROF(i, 0, b)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
template <typename T> 
bool ckmax(T& a, const T& b) {return b > a ? a = b, 1 : 0;}
template <typename T>
bool ckmin(T& a, const T& b) {return b < a ? a = b, 1 : 0;}


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
void dbg_out() {
	cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__);
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

void setIO() {
	cin.tie(0) -> sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}



inline namespace seg{
	const int MN = 1e5;
	pii t[MN * 4];
	int sz = 1;
	pii merge(const pii& a, const pii& b) {
		return {max(a.fi, b.fi), min(a.se, b.se)};
	}
	void init(int n) {
		sz = 1;
		while (sz < n) sz *= 2;
		fill(t, t + sz * 2, make_pair(0, 2 * INF));
	}
	void upd(int i, pii v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			t[x] = v;
			return;
		}
		int mid = (lx + rx) >> 1;
		if (i < mid) upd(i, v, 2 * x + 1, lx, mid);
		else upd(i, v, 2 * x + 2, mid, rx);
		t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, pii v) {
		upd(i, v, 0, 0, sz);
	}
	pii query(int l, int r, int x, int lx, int rx) {
		if (rx <= l || lx >= r) return make_pair(0, 2 * INF);
		if (l <= lx && rx <= r) return t[x];
		int m = (lx + rx) >> 1;
		pii a = query(l, r, 2 * x + 1, lx, m);
		pii b = query(l, r, 2 * x + 2, m, rx);
		return merge(a, b);
	}
	pii query(int l, int r) {
		return query(l, r, 0, 0, sz);
	}
};





void solve(bool B) {
	int N;
	cin >> N;
	vector<vi> g(N);
	vi tin(N), tout(N);
	vpi rang(N);
	int timer{};
	FOR(i, 1, N) {
		int p;
		cin >> p;
		p--;
		g[p].pb(i), g[i].pb(p);
	}
	for (auto &[l, r] : rang) cin >> l >> r;
	auto dfsInit = y_combinator([&](auto self, int u, int pu) -> void {
		tin[u] = timer++;
		for (auto &e : g[u]) {
			if (e != pu) self(e, u);
		}
		tout[u] = timer - 1;
	});
	dfsInit(0, -1);
	int L = 0, R = INF, ans = INF;
	while (L <= R) {
		int mid = (L + R) >> 1;
		init(N);
		auto dfs = y_combinator([&](auto self, int u, int pu) -> bool {
			pii cur = rang[u];
			bool ok = 1;
			for (auto &e : g[u]) {
				if (pu != e) {
					ok &= self(e, u);
					if (!ok) return ok;
				}
			}
			auto [l, r] = query(tin[u], tout[u] + 1);
			if (cur.fi < l) cur.fi = l;
			if (cur.se > r) cur.se = r;
			if (cur.fi > cur.se) ok = 0;
			upd(tin[u], {cur.fi - mid, cur.se + mid});
			return ok;
		});
		if (dfs(0, -1)) {
			ans = mid; R = mid - 1;
		}else L = mid + 1;
	}
	cout << ans << "\n";
	if (B) {
		vi res(N);
		init(N);
		vpi a(N);
		auto dfs = y_combinator([&](auto self, int u, int pu) -> void {
			pii cur = rang[u];
			for (auto &e : g[u]) {
				if (pu != e) {
					self(e, u);
				}
			}
			auto [l, r] = query(tin[u], tout[u] + 1);
			if (cur.fi < l) cur.fi = l;
			if (cur.se > r) cur.se = r;
			upd(tin[u], {cur.fi - ans, cur.se + ans});
			a[u] = cur;
		});
		dfs(0, -1);
		multiset<int> st;
		auto go = y_combinator([&](auto self, int u, int pu) -> void {
			if (!sz(st)) {
				res[u] = a[u].fi;
			}else{
				auto [l, r] = a[u];
				if (*st.begin() > r) {
					res[u] = r;
				}else if (*--st.end() < l) {
					res[u] = l;
				}else{
					auto it = st.lb(l);
					if (*it >= l && *it <= r) res[u] = *it;
					else {
						int k = *it;
						it--;
						int m = *it;
						if (k - r > l - m) res[u] = l;
						else res[u] = r;
					}
				}
			}
			st.insert(res[u]);
			for (auto &e : g[u]) {
				if (e != pu) self(e, u);
			}
			st.erase(st.find(res[u]));
		});
		go(0, -1);
		F0R(i, N) cout << res[i] << " \n"[i == N - 1];
	}
}
int main() {
	setIO();
	int tc;
	int b;
	cin >> tc >> b;
	while (tc--) {
		solve(b);
	}
}
