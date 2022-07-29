/**
 * Description: Trie-like structure storing distinct palindromes. Also called eertree
    * Edge from u to v with character c: S_v = "c" + S_u + "c"
    * Suffix links: Links to the longest nontrivial palindromic suffix
    * Root 1 = Length -1, Root 2 = Length 0
    * Unlike a trie, the number of nodes (distinct palindromes) is bounded to O(|S|)
 * Source: http://adilet.org/blog/palindromic-tree/ 
 * Verification:
 * Time complexity: O(|S|)
 * Memory complexity: O(\sigma |S|) but can be reduced by not storing all edges
    * Check adamant's comment - https://codeforces.com/blog/entry/13959?#comment-313090
 */

struct Node {
    int to[26];
    int len;
    int suf_link;
};

const int MAXN = 1e5;
Node tree[MAXN];
string s;
int ind, last_suf; 

bool add_char(int pos) {
    int c = s[pos] - 'a';
    int cur = last_suf, cur_len = 0;
    while (1) {
        cur_len = tree[cur].len;
        if (pos-1-cur_len >= 0 && s[pos-1-cur_len] == s[pos]) {
            break;
        }
        cur = tree[cur].suf_link;
    }
    if (tree[cur].to[c]) {
        last_suf = tree[cur].to[c];
        return false;
    }
    ind++;
    tree[cur].to[c] = ind;
    tree[ind].len = 2 + tree[cur].len;
    last_suf = ind;
    if (tree[ind].len == 1) {
        tree[ind].suf_link = 2;
        return true;
    }
    while (1) {
        cur = tree[cur].suf_link;
        cur_len = tree[cur].len;
        if (pos-1-cur_len >= 0 && s[pos-1-cur_len] == s[pos]) {
            tree[ind].suf_link = tree[cur].to[c];
            return true;
        }
    }
}

void init_tree() {
    tree[1].len = -1; tree[2].len = 0;
    tree[1].suf_link = tree[2].suf_link = 1;
    ind = last_suf = 2;
}