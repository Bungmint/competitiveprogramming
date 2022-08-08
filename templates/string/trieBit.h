/**
 * Description: Bit Trie supporting xor min and xor max queries
 * Source: Folklore, Benq
 * Verification: https://judge.yosupo.jp/problem/set_xor_min
 * Time complexity: O(MAXBIT) per insertion
 */

template <int SZ, int MAXBIT>
struct TrieBit {
    int nxt[SZ][2], sz[SZ], num = 0;
    TrieBit() { memset(nxt, 0, sizeof(nxt)), memset(sz, 0, sizeof(sz)); }
    void insert(ll x, int cnt = 1) {
        int now = 0; sz[now] += cnt;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl]) nxt[now][fl] = ++num;
            now = nxt[now][fl];
            sz[now] += cnt;
        }
    }
    ll query_xor_min(ll x) {
        if (!sz[0]) return -1;
        int now = 0;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = x>>j & 1;
            if (!nxt[now][fl] || !sz[nxt[now][fl]]) {
                if (!fl) x ^= 1<<j;
                fl ^= 1;
            }else if (fl) x ^= 1<<j;
            now = nxt[now][fl];
        }
        return x;
    }
    ll query_xor_max(ll x) {
        if (!sz[0]) return -1;
        int now = 0;
        for (int j = MAXBIT-1; j >= 0; j--) {
            bool fl = (x>>j & 1) ^ 1;
            if (!nxt[now][fl] || !sz[nxt[now][fl]]) fl ^= 1;
            if (fl) x ^= 1<<j;
            now = nxt[now][fl];
        }
        return x;
    }
};