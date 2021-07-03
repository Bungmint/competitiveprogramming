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
const int MOD = 1e9 + 7; //998244353

inline bool dif(pi p, pi q){
	return (p.fi!=q.fi&&p.fi!=q.se&&p.se!=q.fi&&p.se!=q.se);
}

void solve()
{
	int n;
	cin >> n;
	vi a(n+1);
	map<int,vpi> m1;
	for (int i=1;i<=n;++i) cin >> a[i];
	for (int i=1;i<=n;++i){
		for (int j=i+1;j<=n;++j){
			pi k = {i,j};
			for (auto x:m1[a[i]+a[j]]){
				if (dif(x, k)){
					cout << "YES\n";
					cout << x.fi << " "<< x.se << " "<< k.fi << " "<<k.se<<"\n";
					return;
				}
			}
			
			
			m1[a[i]+a[j]].pb({i,j});
			dbg(m1[a[i]+a[j]]);
			
			
			if (m1[a[i]+a[j]].size()==4){
				map<int,int> cnt;
				for (auto x:m1[a[i]+a[j]]){
					cnt[x.fi]++;
					cnt[x.se]++;
				}
				int mx = 0, id = 0;
				for (auto x:cnt){
					if (mx<x.se){
						mx = x.se, id = x.fi;
					}
				}
				vi ans;
				cout << "YES\n";
				if (mx==4){
					for (auto x:m1[a[i]+a[j]]){
						if (x.fi!=id) ans.pb(x.fi);
						if (x.se!=id) ans.pb(x.se);
					}
					for (int x:ans)cout << x << " ";
					cout << "\n";
				}else if (mx==3){
					pi p, q;
					for (auto x:m1[a[i]+a[j]]){
						if (x.fi!=id&&x.se!=id) p = x;
					}
					for (auto x:m1[a[i]+a[j]]){
						if (x!=p&&x.fi!=p.se&&x.se!=p.fi){
							q = x;
						}
					}
					cout << p.fi << " "<< p.se << " "<< q.fi << " "<<q.se << "\n";
				}else if (mx==2){
					pi p = m1[a[i]+a[j]][0];
					pi q = m1[a[i]+a[j]][1];
					pi r = m1[a[i]+a[j]][2];
					pi s = m1[a[i]+a[j]][3];
					pi x, y;
					if (dif(p, q)){
						x = p, y = q;
					}else if (dif(p,r)){
						x = p, y = r;
					}else if (dif(p,s)){
						x = p, y = s;
					}else if (dif(q,r)){
						x = q, y = r;
					}else if (dif(q,s)){
						x = q, y = s;
					}else {
						x = r, y = s;
					}
					cout << x.fi << " "<< x.se << " "<< y.fi << " "<<y.se << "\n";
				}else{
					pi p1 = m1[a[i]+a[j]][0], p2 = m1[a[i]+a[j]][1];
					cout << p1.fi << " "<< p1.se << " "<< p2.fi << " "<< p2.se<<"\n";
				}
				return;
			}
		}
	}
	cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}