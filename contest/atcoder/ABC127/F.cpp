// Problem: F - Absolute Minima
// Contest: AtCoder - AtCoder Beginner Contest 127
// URL: https://atcoder.jp/contests/abc127/tasks/abc127_f?lang=en
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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

#define all(v) (v).begin(), (v).end()
#define ar array
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

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}
//from maspy's blog and https://ei1333.github.io/library/structure/others/slope-trick.cpp
template< typename T >
struct SlopeTrick {
 
  const T INF = numeric_limits< T >::max() / 3;
 
  T min_f;
  priority_queue< T, vector< T >, less<> > L;
  priority_queue< T, vector< T >, greater<> > R;
  T add_l, add_r;
  
  void push_R(const T &a) {
    R.push(a - add_r);
  }
 
  T top_R() const {
    if(R.empty()) return INF;
    else return R.top() + add_r;
  }
 
  T pop_R() {
    T val = top_R();
    if(not R.empty()) R.pop();
    return val;
  }
 
  void push_L(const T &a) {
    L.push(a - add_l);
  }
 
  T top_L() const {
    if(L.empty()) return -INF;
    else return L.top() + add_l;
  }
 
  T pop_L() {
    T val = top_L();
    if(not L.empty()) L.pop();
    return val;
  }
 
  size_t size() {
    return L.size() + R.size();
  }
 

  SlopeTrick() : min_f(0), add_l(0), add_r(0) {
  	//When needed initialize the pqs with zeros
  	// for (int i=0;i<1000000;i++){
  		// L.push(0), R.push(0);
  	// }
  }
 
  struct Query {
    T lx, rx, min_f;
  };
 
  // return min f(x)
  Query query() const {
    return (Query) {top_L(), top_R(), min_f};
  }
 
  // f(x) += a
  void add_all(const T &a) {
    min_f += a;
  }
 
  // add \_
  // f(x) += max(a - x, 0)
  void add_a_minus_x(const T &a) {
    min_f += max(T(0), a - top_R());
    push_R(a);
    push_L(pop_R());
  }
 
  // add _/
  // f(x) += max(x - a, 0)
  void add_x_minus_a(const T &a) {
    min_f += max(T(0), top_L() - a);
    push_L(a);
    push_R(pop_L());
  }
 
  // add \/
  // f(x) += abs(x - a)
  void add_abs(const T &a) {
    add_a_minus_x(a);
    add_x_minus_a(a);
  }
 
  // \/ -> \_
  // f_{new} (x) = min f(y) (y <= x)
  void clear_right() {
    while(not R.empty()) R.pop();
  }
 
  // \/ -> _/
  // f_{new} (x) = min f(y) (y >= x)
  void clear_left() {
    while(not L.empty()) L.pop();
  }
 
  // \/ -> \_/
  // f_{new} (x) = min f(y) (x-b <= y <= x-a)
  void shift(const T &a, const T &b) {
    assert(a <= b);
    add_l += a;
    add_r += b;
  }
 
  // \/. -> .\/
  // f_{new} (x) = f(x - a)
  void shift(const T &a) {
    shift(a, a);
  }
 
  // L, R を破壊する
  T get(const T &x) {
    T ret = min_f;
    while(not L.empty()) {
      ret += max(T(0), pop_L() - x);
    }
    while(not R.empty()) {
      ret += max(T(0), x - pop_R());
    }
    return ret;
  }
 
  void merge(SlopeTrick &st) {
    if(st.size() > size()) {
      swap(st.L, L);
      swap(st.R, R);
      swap(st.add_l, add_l);
      swap(st.add_r, add_r);
      swap(st.min_f, min_f);
    }
    while(not st.R.empty()) {
      add_x_minus_a(st.pop_R());
    }
    while(not st.L.empty()) {
      add_a_minus_x(st.pop_L());
    }
    min_f += st.min_f;
  }
};

void solve()
{
	SlopeTrick<ll> st;
	int q;cin >> q;
	while(q--){
		int t;
		cin >> t;
		if(t==1){
			int a, b;
			cin>> a >> b;
			st.add_abs(a);
			st.add_all(b);
		}else{
			auto x = st.query();
			cout << x.lx << " "<<x.min_f <<"\n";
		}
	}
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