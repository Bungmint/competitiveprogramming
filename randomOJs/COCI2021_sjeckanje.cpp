#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ar array
#define for2(i) for (int i=0; i<2; ++i)
 
const int mxN=2e5;
int n, q, a[mxN];
 
void smax(ll& i, ll j) {
	if (j>i)
		i=j;
}
 
struct Node {
	ll la, ra, lz=0, dp[2][2];
	Node() {
		dp[0][0]=dp[0][1]=dp[1][0]=dp[1][1]=-1e18;
	}
} st[1<<19];
 
Node cmb(Node u, Node v) {
	Node r;
	r.la=u.la;
	r.ra=v.ra;
	for2(i1) for2(j2) {
		for2(j1) for2(i2)
			smax(r.dp[i1][j2], u.dp[i1][j1]+v.dp[i2][j2]);
		if (u.ra<=v.la)
			smax(r.dp[i1][j2], u.dp[i1][0]+v.dp[0][j2]+abs(v.la-u.ra));
      else 
        smax(r.dp[i1][j2], u.dp[i1][1]+v.dp[1][j2]+abs(v.la-u.ra));
		//cout << i1 << " " << j2 << " " << r.dp[i1][j2] << endl;
	}
	return r;
}
 
void bld(int u=1, int l=0, int r=n-1) {
	if (l==r) {
		st[u].la=st[u].ra=a[l];
		st[u].dp[0][0]=st[u].dp[1][1]=0;
		return;
	}
	int mid=(l+r)/2;
	bld(2*u, l, mid);
	bld(2*u+1, mid+1, r);
	st[u]=cmb(st[2*u], st[2*u+1]);
}
 
void psh(int u, int l, int r) {
	if (st[u].lz) {
		st[u].la+=st[u].lz;
		st[u].ra+=st[u].lz;
		if (l^r)
			st[2*u].lz+=st[u].lz, st[2*u+1].lz+=st[u].lz;
		st[u].lz=0;
	}
}
 
int ql, qr, x;
void upd(int u=1, int l=0, int r=n-1) {
	psh(u, l, r);
	if (l>qr||r<ql)
		return;
	if (ql<=l&&r<=qr) {
		st[u].lz+=x;
		psh(u, l, r);
		return;
	}
	int mid=(l+r)/2;
	upd(2*u, l, mid);
	upd(2*u+1, mid+1, r);
	st[u]=cmb(st[2*u], st[2*u+1]);
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (int i=0; i<n; ++i)
		cin >> a[i];
	bld();
	while(q--) {
		cin >> ql >> qr >> x, --ql, --qr;
		upd();
		cout << max({st[1].dp[0][0], st[1].dp[0][1], st[1].dp[1][0], st[1].dp[1][1]}) << "\n";
	}
	return 0;
}