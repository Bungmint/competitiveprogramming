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
#define PB push_back
#define sz(x) (int)(x).size()

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

void count_sort(vi &p, vi &c){
	int n= sz(p);
	vi p_new(n), cnt(n),pos(n);
	for (int x:c){
		cnt[x]++;
	}
	pos[0] = 0;
	for (int i=1;i<n;++i) pos[i] = pos[i-1]+cnt[i-1];
	for (auto x:p){
		int i = c[x];
		p_new[pos[i]] = x;
		pos[i]++; 
	}
	p = p_new;
}

void solve()
{
	string s;
	cin >> s;
	s+='$';
	int n = sz(s);
	vi p(n), c(n), c_new(n);
	vector<pair<char,int>> a(n);
	for (int i=0;i<n;++i){
		a[i] = {s[i], i};
	}
	sort(all(a));
	for (int i=0;i<n;++i) p[i] = a[i].second;
	c[p[0]] = 0;
	for (int i=1;i<n;++i){
		if (a[i].first==a[i-1].first){
			c[p[i]] = c[p[i-1]];
		}else{
			c[p[i]] = c[p[i-1]]+1;
		}
	}
	
	int k=0;
	while((1<<k)<n){
		for (int i=0;i<n;++i){
			p[i] = (p[i]-(1<<k)+n)%n;
		}
		count_sort(p, c);
		c_new[p[0]] = 0;
		for (int i=1;i<n;++i){
			pi prev = {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
			pi cur = {c[p[i]], c[(p[i]+(1<<k))%n]};
			if (prev==cur){
				c_new[p[i]] = c_new[p[i-1]];
			}else{
				c_new[p[i]] = c_new[p[i-1]]+1;
			}
		}
		
		c = c_new;
		k++;
	}
	for (int i=0;i<n;++i) cout << p[i]<< " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}