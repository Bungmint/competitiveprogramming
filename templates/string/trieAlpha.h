/**
 * Description: Trie supporting string insertion
 * Source: Folklore, Benq
 * Verification: https://oj.uz/problem/view/IOI08_printer
 * Time complexity: O(|S_i|) per insertion
 */

template <int SZ, int ALPHA>
struct TrieAlpha {
    int nxt[SZ][ALPHA], sz[SZ], num = 0;
    TrieAlpha() { memset(nxt, 0, sizeof(nxt)), memset(sz, 0, sizeof(sz)); }
    void insert(const string& s, int cnt = 1) {
        int now = 0; sz[now] += cnt;
        for (int i = 0; i < sz(s); i++) {
            int c = s[i] - 'a';
            if (!nxt[now][c]) nxt[now][c] = ++num;
            now = nxt[now][c];
            sz[now] += cnt;
        }
    }
};