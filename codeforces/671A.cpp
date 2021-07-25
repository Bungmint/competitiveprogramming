#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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
#define dbg(...)
#endif

struct custom_hash
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
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

inline ld dist(pi point, int x, int y){
	return sqrtl((ll)(point.fi-x)*(point.fi-x) + (ll)(point.se-y)*(point.se-y));
}

void solve()
{
	cout << setprecision(20);
	int ax, ay, bx, by, tx, ty;
	cin>> ax >> ay >> bx >> by >> tx >> ty;
	int n;
	cin >> n;
	vpl trash(n), a(n), b(n);
	ld total = 0;
	for(int i=0;i<n;++i){
		cin >> trash[i].fi >> trash[i].se;
		total += dist(trash[i], tx,ty);
	}
	if (n==1){
		cout << min(dist(trash[0], ax, ay), dist(trash[0], bx, by)) + total<<"\n";
		return;
	}
	total *=2;
	a = trash, b= trash;
	sort(all(a), [&](pl p, pl q){
		ld v1 = -sqrtl(((p.fi-tx)*(p.fi-tx) + (p.se-ty)*(p.se-ty))) + sqrtl(((p.fi-ax)*(p.fi-ax) + (p.se-ay)*(p.se-ay)));
		ld v2 = -sqrtl(((q.fi-tx)*(q.fi-tx) + (q.se-ty)*(q.se-ty))) + sqrtl(((q.fi-ax)*(q.fi-ax) + (q.se-ay)*(q.se-ay)));
		
		return v1<v2;
	});
	sort(all(b), [&](pl p, pl q){
		ld v1 = -sqrtl(((p.fi-tx)*(p.fi-tx) + (p.se-ty)*(p.se-ty))) + sqrtl(((p.fi-bx)*(p.fi-bx) + (p.se-by)*(p.se-by)));
		ld v2 = -sqrtl(((q.fi-tx)*(q.fi-tx) + (q.se-ty)*(q.se-ty))) + sqrtl(((q.fi-bx)*(q.fi-bx) + (q.se-by)*(q.se-by)));
		
		return v1<v2;
	});
	ld ans = LINF;
	if (a[0]==b[0]){
		
		ld val1 = total, val2 = total;
		pl p = a[0], q = b[1];
		
		ld v1 = -sqrtl(((p.fi-tx)*(p.fi-tx) + (p.se-ty)*(p.se-ty))) + sqrtl(((p.fi-ax)*(p.fi-ax) + (p.se-ay)*(p.se-ay)));
		ld v2 = -sqrtl(((q.fi-tx)*(q.fi-tx) + (q.se-ty)*(q.se-ty))) + sqrtl(((q.fi-bx)*(q.fi-bx) + (q.se-by)*(q.se-by)));
		val1 += v1 + v2;
		ans = min(ans, total+v1);
		p = a[1], q = b[0];
		dbg(p,q);
		dbg(val2);
		v1 = -sqrtl(((p.fi-tx)*(p.fi-tx) + (p.se-ty)*(p.se-ty))) + sqrtl(((p.fi-ax)*(p.fi-ax) + (p.se-ay)*(p.se-ay)));
		v2 = -sqrtl(((q.fi-tx)*(q.fi-tx) + (q.se-ty)*(q.se-ty))) + sqrtl(((q.fi-bx)*(q.fi-bx) + (q.se-by)*(q.se-by)));
		dbg(v1, v2);
		val2 += v1 +v2;
		dbg(val1, val2);
		ans = min(ans, min(val1, val2));
		ans = min(ans, total+v2);
	}else{
		pl p = a[0], q = b[0];
		ld v1 = -sqrtl(((p.fi-tx)*(p.fi-tx) + (p.se-ty)*(p.se-ty))) + sqrtl(((p.fi-ax)*(p.fi-ax) + (p.se-ay)*(p.se-ay)));
		ld v2 = -sqrtl(((q.fi-tx)*(q.fi-tx) + (q.se-ty)*(q.se-ty))) + sqrtl(((q.fi-bx)*(q.fi-bx) + (q.se-by)*(q.se-by)));
		dbg(v1, v2);
		ans = v1 + v2 + total;
		ans =min(ans, total+v1);
		ans = min(ans, total+v2);
	}
	cout << ans << "\n";
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}