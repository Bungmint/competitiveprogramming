#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, b) FOR(i, 0, b)
#define pb push_back
#define lb lower_bound

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

struct DSU{
	vi p, size;
	DSU(int n) {
		p.resize(n), iota(all(p), 0);
		size.assign(n, 1);
	}
	int get(int a) {return a == p[a] ? a : p[a] = get(p[a]);}
	bool unite(int a, int b) {
		a = get(a), b = get(b);
		if (a == b) return false;
		if (size[a] < size[b]) swap(a, b);
		size[a] += size[b];
		p[b] = a;
		return true;
	}
};

struct Edge{
	ll u, v, w;
	bool operator<(const Edge& other) const{
		return w < other.w;
	}
};

ll sq(ll x) {
	return 1LL * x * x;
}

void solve() {
	int n;
	cin >> n;
	vpl a(n);
	vector<vpl> yCoord(11);
	int iii = 0;
	for (auto &[x, y] : a) cin >> x >> y, yCoord[y].pb({x, iii++});
	ll ans = 0;
	F0R(i, 11) {
		sort(all(yCoord[i]));
	}
	DSU dsu(n);
	vector<Edge> edges;
	F0R(i, n) {
		auto [x, y] = a[i];
		F0R(j, 11) {
			if (yCoord[j].empty()) continue;
			auto id1 = lb(all(yCoord[j]), make_pair(x, LINF)) - yCoord[j].begin();
			if (id1 >= 0 && id1 < sz(yCoord[j])) {
				edges.pb({i, yCoord[j][id1].se, sq(yCoord[j][id1].fi - x) + sq(j - y)});
			}
			id1 = lb(all(yCoord[j]), make_pair(x - 1, LINF)) - yCoord[j].begin() - 1;
			if (id1 >= 0 && id1 < sz(yCoord[j])) {
				edges.pb({i, yCoord[j][id1].se, sq(yCoord[j][id1].fi - x) + sq(j - y)});
			}
			id1 = lb(all(yCoord[j]), make_pair(x - 1, LINF)) - yCoord[j].begin();
			if (id1 >= 0 && id1 < sz(yCoord[j])) {
				edges.pb({i, yCoord[j][id1].se, sq(yCoord[j][id1].fi - x) + sq(j - y)});
			}
		}
	}
	sort(all(edges));
	for (auto &[u, v, w] : edges) {
		if (dsu.unite(u, v)) ans += w;
	}
	cout << ans;
}


int main() {
	setIO();
	solve();
}