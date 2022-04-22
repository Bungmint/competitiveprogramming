#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
template <typename T>
bool ckmin(T& a, const T& b) {
	return a > b ? a = b, 1 : 0;
}

/**
 * Description: 1D point update, range query where \texttt{comb} is
 	* any associative operation. If $N=2^p$ then \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

template<class T> struct Seg { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return min(a,b); }
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		ckmin(seg[p += n],val); for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// sum on interval [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};

const int MX = 1e5 + 100;
Seg<int> S;
int N,P;
int ans[MX];
vi distinct_y;

#define f first
#define s second
#define lb lower_bound
#define pb push_back
#define all(x) (x).begin(), (x).end()

void setIO(string s) {
	cin.tie(0) -> sync_with_stdio(0);
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int query_min(int ind) { return S.query(0,ind); }
void ins(int ind, int val) { S.upd(ind,val); }
int y_index(int y) {return lb(all(distinct_y),y)-begin(distinct_y); }

int main() {
	setIO("boards");
	cin >> N >> P;
	vector<pair<pair<int,int>,pair<int,int>>> ev;
	for (int i = 0; i < P; ++i) {
		pair<int,int> a,b;
		cin >> a.f >> a.s >> b.f >> b.s;
		ev.push_back({a,{i,-1}}); // start point
		ev.push_back({b,{i,1}}); // end point
		distinct_y.pb(a.s);
		distinct_y.pb(b.s);
	}
	sort(all(distinct_y));
	sort(begin(ev),end(ev));
	S.init(2*P);
	ins(0,0);
	for (auto& t: ev) {
		if (t.s.s == -1) {
			ans[t.s.f] = t.f.f+t.f.s+query_min(y_index(t.f.s));
		} else {
			ins(y_index(t.f.s),ans[t.s.f]-t.f.f-t.f.s);
		}
	}
	cout << query_min(2*P-1)+2*N;
}