#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <chrono>
#include <random>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <utility>
#include <bitset>
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
mt19937 rng(15135);
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

#pragma endregion TEMPLATE


/**
 * Description: Fast input and output.
 * Time: input is $\sim$300ms faster for $10^6$ long longs on CF
 * Source: 
 	* https://codeforces.com/contest/1254/submission/65420506 (neal)
 * Verification: https://codeforces.com/gym/102394/problem/G 
 */

namespace FastIO {
    constexpr int BUFFER_SIZE = 1 << 15;

    char input_buffer[BUFFER_SIZE];
    int input_pos = 0, input_len = 0;

    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;

    char number_buffer[100];
    uint8_t lookup[100];
 
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) input_buffer[0] = EOF;
    }
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) _update_input_buffer();
        return input_buffer[advance ? input_pos++ : input_pos];
    }
    void read_string(string &s) {
        char ch; 
        while (isspace(ch = next_char()));
        do {
            s += ch;
        } while(!isspace(ch = next_char()) && ch != EOF);
    }
    template<typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
        while (!isdigit(next_char(false)))
            if (next_char() == '-') negative = true;
        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));
        if (negative) number = -number;
    }
    template<typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) _flush_output();
        output_buffer[output_pos++] = c;
    }
    void write_string(const string& s) {
        for (auto &ch : s) write_char(ch);
    }
    template<typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }
        int length = 0;
        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = (lookup_value & 15) + '0';
            number_buffer[length++] = (lookup_value >> 4) + '0';
        }
        if (number != 0 || length == 0) write_char(number + '0');
        for (int i = length - 1; i >= 0; i--) write_char(number_buffer[i]);
        if (after) write_char(after);
    }
    void init() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);
        for (int i = 0; i < 100; i++) lookup[i] = (i / 10 << 4) + i % 10;
    }
}
/**
 * Segment tree of sparse tables
 * This better work 
 */

const int MAXN = 260;
int N, LG, SZ;
int grid[MAXN][MAXN];
int r[MAXN*MAXN], c[MAXN*MAXN];
int r_min[18][MAXN*MAXN], r_max[18][MAXN*MAXN];
int c_min[18][MAXN*MAXN], c_max[18][MAXN*MAXN];
int clz[MAXN*MAXN];

struct Node {
	int sparse_min[9][260];
	int sparse_max[9][260];
	Node() {
		memset(sparse_min, 0x3f, sizeof(sparse_min));
		memset(sparse_max, 0, sizeof(sparse_max));
	}
	void init(int* b) {
		for (int j = 0; j < N; j++) sparse_min[0][j] = sparse_max[0][j] = b[j];
		for (int i = 1; i <= LG; i++) {
			for (int j = 0; j + (1 << i) <= N; j++) {
				sparse_min[i][j] = min(sparse_min[i-1][j], sparse_min[i-1][j+(1<<(i-1))]);
				sparse_max[i][j] = max(sparse_max[i-1][j], sparse_max[i-1][j+(1<<(i-1))]);
			}
		}
	}
	friend void merge(Node& a, const Node& lhs, const Node& rhs) {
		for (int i = 0; i <= LG; i++) {
			for (int j = 0; j < N; j++) {
				a.sparse_max[i][j] = max(lhs.sparse_max[i][j], rhs.sparse_max[i][j]);
				a.sparse_min[i][j] = min(lhs.sparse_min[i][j], rhs.sparse_min[i][j]);
			}
		}
	}
	inline pii query(int L, int R) {
		int t = 31 - __builtin_clz(R-L+1);
		return {
			min(sparse_min[t][L], sparse_min[t][R-(1<<t)+1]),
			max(sparse_max[t][L], sparse_max[t][R-(1<<t)+1])
		};
	}
}seg[520];


void build() {
	for (int i = 0; i < N; i++) seg[i + N].init(grid[i]);
	for (int i = N - 1; i; i--) {
		merge(seg[i], seg[2*i], seg[2*i + 1]);
	}
}
inline pii comb(const pii& a, const pii& b) {
	return {(a.fi > b.fi ? b.fi : a.fi), (a.se < b.se ? b.se : a.se)};
}
// Iterative seg, I first saw it from an old codeforces blog, I believe from Al.Cash
inline pii seg_query(int L, int R, int c1, int c2) {
	pii ra = {INF, -INF}, rb = {INF, -INF};
	for (L += N, R += N; L < R; L /= 2, R /= 2) {
		if (L % 2) ra = comb(ra, seg[L++].query(c1, c2));
		if (R % 2) rb = comb(seg[--R].query(c1, c2), rb);
	}
	return comb(ra, rb);
}
void init() {
	int lg = 31 - __builtin_clz(N*N);
	for (int i = 0; i < N*N; i++) {
		r_min[0][i] = r_max[0][i] = r[i];
		c_min[0][i] = c_max[0][i] = c[i];
	}
	for (int i = 1; i <= lg; i++) {
		for (int j = 0; j + (1 << i) <= N*N; j++) {
			r_min[i][j] = min(r_min[i-1][j], r_min[i-1][j+(1<<(i-1))]);
			c_min[i][j] = min(c_min[i-1][j], c_min[i-1][j+(1<<(i-1))]);
			r_max[i][j] = max(r_max[i-1][j], r_max[i-1][j+(1<<(i-1))]);
			c_max[i][j] = max(c_max[i-1][j], c_max[i-1][j+(1<<(i-1))]);
		}
	}
}
inline ar<int, 4> query(int L, int R) {
	int t = 31 - __builtin_clz(R-L+1);
	int rr = R-(1<<t)+1;
	return {
		min(r_min[t][L], r_min[t][rr]),
		min(c_min[t][L], c_min[t][rr]),
		max(r_max[t][L], r_max[t][rr]),
		max(c_max[t][L], c_max[t][rr])
	};
}
void solve() {
	FastIO::read_int(N);
	LG = 31 - __builtin_clz(N);
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
		FastIO::read_int(grid[i][j]);
		grid[i][j]--;
		r[grid[i][j]] = i;
		c[grid[i][j]] = j;
	}
	build();
	init();
	ll ans{};
	for (int i = 0; i < N*N; i++) {
		// count distinct O(N) rectangles
		int r1 = r[i], r2 = r[i], c1 = c[i], c2 = c[i];
		int R = i;
		while (1) {
			pii q = seg_query(r1, r2+1, c1, c2);
			if (q.fi < i) break;
			if ((q.se-q.fi+1) == (r2-r1+1)*(c2-c1+1)) ans++;
			if (R == N*N-1) break;
			if (q.se == N*N-1) {
				dbg(i);
				auto [rr1, cc1, rr2, cc2] = query(i, N*N-1);
				r1 = rr1, c1 = cc1, r2 = rr2, c2 = cc2;
				pii qq = seg_query(r1, r2+1, c1, c2);
				if ((qq.se-qq.fi+1) == (r2-r1+1)*(c2-c1+1)) ans++;
				break;
			}
			int lo = R + 1, hi = N*N - 1, ret = -1;
			while (lo <= hi) {
				int mid = (lo+hi)/2;
				auto [rr1, cc1, rr2, cc2] = query(R+1, mid);
				if (rr1 < r1 || rr2 > r2 || cc1 < c1 || cc2 > c2) {
					ret = mid;
					hi = mid-1;
				}else lo = mid+1;
			}
			if (ret == -1) break;
			if (r1 > r[ret]) r1 = r[ret];
			if (r2 < r[ret]) r2 = r[ret];
			if (c1 > c[ret]) c1 = c[ret];
			if (c2 < c[ret]) c2 = c[ret];
			R = ret;
		}
	}
	FastIO::write_int(ans-1);
	FastIO::write_char('\n');
}

int main() {
	FastIO::init();
	int testcase = 1;
	FastIO::read_int(testcase);
	for (int tc = 1; tc <= testcase; tc++) {
		FastIO::write_string("Case #");
		FastIO::write_int(tc);
		FastIO::write_char('\n');
		solve();
	}
}
