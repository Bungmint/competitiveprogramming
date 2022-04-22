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

struct Cowple{
	int ty, t, x, n;
	bool operator<(const Cowple& other) const {
		return t - x < other.t - other.x;
	}
};



void solve() {
	int N;
	cin >> N;
	vector<Cowple> a(N);
	for (auto &[ty, t, x, n] : a) cin >> ty >> t >> x >> n;
	sort(all(a));
	multiset<pii> st;
	int ans{};
	F0R(i, N) {
		vector<Cowple> cows, apples;
		if (a[i].ty == 1) {
			cows.pb(a[i]);
		}else apples.pb(a[i]);
		while (i + 1 < N && a[i + 1].t - a[i + 1].x == a[i].t - a[i].x) {
			if (a[i + 1].ty == 1) {
				cows.pb(a[i + 1]);
			}else apples.pb(a[i + 1]);
			i++;
		}
		for (auto &[ty, t, x, n] : cows) {
			st.insert({t + x, n});
		}
		for (auto &[ty, t, x, n] : apples) {
			int T = t + x;
			while (sz(st) && st.begin()->fi <= T && n) {
				auto it = st.lb({T + 1, -INF});
				it--;
				auto [tt, nn] = *it;
				st.erase(it);
				int mi = min(nn, n);
				n -= mi, nn -= mi;
				ans += mi;
				if (nn) st.insert({tt, nn});
			}
		}
	}
	cout << ans;
}
int main() {
	setIO();
	solve();
}
