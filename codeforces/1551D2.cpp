// Problem: D2. Domino (hard version)
// Contest: Codeforces - Codeforces Round #734 (Div. 3)
// URL: https://codeforces.com/contest/1551/problem/D2
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

void solve()
{
	int n, m, k;
	cin >> n >> m>>k;
	int c = m/2;
	vector<vi> grid(n, vi(m));
	if (n&1){
		if (k<c||c%2!=k%2||n*c<k){
			cout << "NO\n";
			return;
		}
		cout << "YES\n";
		//Column by Column
		vi col(c, 1);
		k-=c;
		for (int i=0;i<c;++i){
			int x = min(n-1, k);
			k-=x;
			col[i] += x;
		}
		for (int i=0;i<c;++i){
			int x= n - col[i];
			x/=2;
			for (int j=0;j<col[i];++j){
				for (int color = 0;color<26;++color){
					if (i&&grid[j][i*2-1]==color) continue;
					if (j&&grid[j-1][i*2]==color) continue;
					grid[j][i*2] = grid[j][i*2+1] = color;
					break;
				}				
			}
			for (int j=0;j<x;++j){
				int top = col[i] + j*2;
				int bottom = col[i] + j*2+1;
				//left side
				for (int color = 0;color<26;++color){
					if (i&&grid[top][i*2-1]==color) continue;
					if(i&&grid[bottom][i*2-1]==color)continue;
					if (top&&grid[top-1][i*2]==color) continue;
					grid[top][i*2] = grid[bottom][i*2] = color;
					break;
				}				
				// right side
				for (int color = 0;color<26;++color){
					if (grid[top][i*2]==color) continue;
					if (top&&grid[top-1][i*2+1]==color) continue;
					grid[bottom][i*2+1] = grid[top][i*2+1] = color;
					break;
				}				
			}
		}
		
	}else{
		if (n*c<k||(k&1)){
			cout << "NO\n";
			return;
		}
		cout << "YES\n";
		vi col(c);
		for (int i=0;i<c;++i){
			int x = min(n, k);
			k-=x;
			col[i] += x;
		}
		for (int i=0;i<c;++i){
			int x= n - col[i];
			x/=2;
			for (int j=0;j<col[i];++j){
				for (int color = 0;color<26;++color){
					if (i&&grid[j][i*2-1]==color) continue;
					if (j&&grid[j-1][i*2]==color) continue;
					grid[j][i*2] = grid[j][i*2+1] = color;
					break;
				}				
			}
			for (int j=0;j<x;++j){
				int top = col[i] + j*2;
				int bottom = col[i] + j*2+1;
				//left side
				for (int color = 0;color<26;++color){
					if (i&&grid[top][i*2-1]==color) continue;
					if(i&&grid[bottom][i*2-1]==color)continue;
					if (top&&grid[top-1][i*2]==color) continue;
					grid[top][i*2] = grid[bottom][i*2] = color;
					break;
				}				
				// right side
				for (int color = 0;color<26;++color){
					if (grid[top][i*2]==color) continue;
					if (top&&grid[top-1][i*2+1]==color) continue;
					grid[bottom][i*2+1] = grid[top][i*2+1] = color;
					break;
				}				
			}
		}
		if (m&1){
			for (int j=0;j<n/2;++j){
				int top = j*2;
				int bottom = j*2+1;
				//left side
				for (int color = 0;color<26;++color){
					if (c&&grid[top][c*2-1]==color) continue;
					if(c&&grid[bottom][c*2-1]==color)continue;
					if (top&&grid[top-1][c*2]==color) continue;
					grid[top][c*2] = grid[bottom][c*2] = color;
					break;
				}		
			}
		}
		
	}
	for (int i=0;i<n;++i){
		for (int j=0;j<m;++j){
			cout << (char)(grid[i][j]+'a');
		}
		cout << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}