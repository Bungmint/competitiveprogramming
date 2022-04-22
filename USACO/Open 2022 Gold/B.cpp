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

int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}
int sub(int a, int b) {
	a -= b;
	if (a < 0) a += MOD;
	return a;
}
int mul(int a, int b) {
	return 1LL * a * b % MOD;
}
int binPow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1LL * res * a % MOD;
		a = 1LL * a * a % MOD;
		b >>= 1;
	}
	return res;
}

const int MN = 2000;
int c[MN + 1][MN + 1];

void precalc() {
	F0R(i, MN + 1) {
		c[i][i] = c[i][0] = 1;
		FOR(j, 1, i) {
			c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
		}
	}
}

int process(string &s) {
	vi cnt(10);
	int var{};
	int n = sz(s);
	int dp[n + 1][2]{};
	for (auto &e : s) {
		if (e == '+') var++;
		else cnt[e - '0']++;
	}
	int current = 1, previous = 0;
	F0R(i, cnt[5] + 1) F0R(j, cnt[7] + 1) {
		dp[i + j + 1] = 
	}
	
	
	
	
	bool isZero = !!cnt[0];
	if (isZero) {
		
	}else{

	}
}



void solve() {
	int N;
	cin >> N;
	string bes, els;
	cin >> bes >> els;
	// Elsie 
	int x = process(els);
	int y = process(bes);
	for (auto &e : els) if (e == '0') y = 1;
	cout << mul(x, y) << "\n";
}
int main() {
	setIO();
	int tc;
	cin >> tc;
	precalc();
	while (tc--) {
		solve();
	}
}
