#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

void solve()
{
	int n;
	cin >> n;
	vector<ll> r, g, b;
	ll t;
	char c;
	for (int i=0;i<2*n;i++){
		cin >> t >>c;
		if (c=='R') r.PB(t);
		else if ( c=='G') g.PB(t);
		else b.PB(t);
	}
	if ((int)r.size()%2==0&&(int)g.size()%2==0){
		cout << 0 << "\n";
		return;
	}
	sort(all(r));sort(all(g));sort(all(b));
	if (sz(g)==0) swap(r,g);
	if (sz(b)==0) swap(r,b);
	if (sz(r)==0){
		ll ans = LINF;
		int i = 0, j= 0;
		while(i<sz(g)||j<sz(b)){
			if (j == sz(b)||(i<sz(g)&&g[i]<b[j])){
				ans = (j!=sz(b) ? min(ans, b[j]-g[i]):min(ans, llabs(b[j-1]-g[i])));
				i++;
			}else if (i==sz(g)||(j<sz(b)&&g[i]>b[j])){
				ans = (i!=sz(g) ? min(ans, g[i]-b[j]):min(ans, llabs(g[i-1]-b[j])));
				j++;
			}else{
				cout << 0 << "\n";
				return;
			}
		}
		cout << ans << "\n";
		return;
	}
	if (sz(g)%2==0) swap(r,g);
	if (sz(b)%2==0) swap(r,b);
	ll ans = LINF;
	int i = 0, j= 0;
	while(i<sz(g)||j<sz(b)){
		if (j == sz(b)||(i<sz(g)&&g[i]<b[j])){
			ans = (j!=sz(b) ? min(ans, b[j]-g[i]):min(ans, llabs(b[j-1]-g[i])));
			i++;
		}else if (i==sz(g)||(j<sz(b)&&g[i]>b[j])){
			ans = (i!=sz(g) ? min(ans, g[i]-b[j]):min(ans, llabs(g[i-1]-b[j])));
			j++;
		}else{
			cout << 0 << "\n";
			return;
		}
	}
	vector<pair<ll,ll>> gp(sz(r)), bp(sz(r));
	for (int i=0;i<sz(r);i++){
		ll val1 = LINF, val2 = LINF;
		auto it = lower_bound(all(g), r[i]);
		if (it==g.end()){
			it--;
			val1 = llabs(*it-r[i]);
		}else{
			val1 = llabs(*it-r[i]);
			if (it!=g.begin()) it--, val1 = min(val1, llabs(*it-r[i]));
		}
		it = lower_bound(all(b), r[i]);
		if (it==b.end()){
			it--;
			val2 = llabs(*it-r[i]);
		}else{
			val2 = llabs(*it-r[i]);
			if (it!=b.begin()) it--, val2 = min(val2, llabs(*it-r[i]));
		}
		gp[i] = {val1, i}, bp[i] = {val2, i};
	}
	sort(all(gp)); sort(all(bp));
	if (gp[0].second != bp[0].second){
		ans = min(ans, gp[0].first+bp[0].first);
	}else{
		ans = min(ans, gp[0].first+bp[1].first);
		ans =min(ans, gp[1].first+bp[0].first);
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}