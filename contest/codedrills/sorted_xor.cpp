#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int,int>;

#define sz(x) (int)(x).begin()
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define F0R(i,n) FOR(i,0,n)
#define ROF(i,a,b) for (int i=(b)-1;i>=(a);--i)
#define R0F(i,b) ROF(i,0,b)

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

const int root = 0;
int cur = 1, tree[6000000][2], cnt[6000000];

void add(int x){
	int now = root;
	R0F(i,31){
		int c = !!(x&(1<<i));
		if (!tree[now][c]) tree[now][c] = cur++;
		now = tree[now][c];
		cnt[now]++;
	}
}
void remove(int x){
	int now = root;
	R0F(i,31){
		int c = !!(x&(1<<i));
		if (!tree[now][c]) tree[now][c] = cur++;
		now = tree[now][c];
		cnt[now]--;
	}
}
int find(int x, int k){ // Finds the number of integers when xored, strictly less than k
	int now = root;
	int res = 0;
	R0F(i,31){
		int cx = !!(x&(1<<i)), ck = !!(k&(1<<i));
		int nxt = 0;
		if (cx==0){
			if (ck==0){
				nxt = tree[now][0];
			}else{
				nxt = tree[now][1];
				res += cnt[tree[now][0]];
			}
		}else{
			if (ck==0){
				nxt = tree[now][1];
			}else{
				nxt = tree[now][0];
				res += cnt[tree[now][1]];
			}
		}
		if (nxt==0) break;
		else now = nxt;
	}
	return res;
}

void reset(){
	F0R(i,cur) tree[i][0] = tree[i][1] = cnt[i] = 0;
	cur = 1;
}


void solve(){
	ll n, k;
	cin >> n>>k;
	reset();
	vi a(n);
	F0R(i,n) cin >> a[i], add(a[i]);
	ll l = 0, r = INT_MAX, ans = 0;
	while(l<=r){
		int m = l +(r-l)/2;
		ll sum = 0;
		F0R(i,n){
			remove(a[i]);
			sum += find(a[i], m);
			add(a[i]);
		}
		sum/=2;
		if (sum<k) ans = m, l = m+1;
		else r = m-1;
	}
	cout << ans << "\n";
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	int tc;
	cin >> tc;
	while(tc-->0){
		solve();
	}
}