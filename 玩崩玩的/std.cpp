#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxN = 5e5 + 10;
const int mod = 17171717;

int n, m;
char s[maxN];

struct SA {
    int n, m = 127;
    char s[maxN];

    int height[maxN], key1[maxN], id[maxN], rk[maxN], oldrk[maxN], sa[maxN],
        cnt[maxN];

    inline bool cmp(int x, int y, int w) {
        return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }

    inline void radix_sort(int* A) {
        for (int i = 1; i <= m; i++)
            cnt[i] = 0;
        for (int i = 1; i <= n; i++)
            cnt[A[i]]++;
        for (int i = 1; i <= m; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--)
            sa[cnt[A[i]]--] = id[i];
    }

    inline void getsa() {
        n = strlen(s + 1);
        for (int i = 1; i <= n; i++)
            id[i] = i, rk[i] = s[i];
        radix_sort(rk);
        int p = 0;
        for (int j = 1; p != n; j <<= 1, m = p) {
            p = 0;
            for (int i = n; i > n - j; i--) id[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > j) id[++p] = sa[i] - j;
            for (int i = 1; i <= n; i++) key1[i] = rk[id[i]];
            radix_sort(key1);
            for (int i = 1; i <= n; i++) oldrk[i] = rk[i];
            p = 0;
            for (int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i], sa[i - 1], j) ? p : ++p;
        }
        for (int i = 1; i <= n; i++) sa[rk[i]] = i;
    }

    inline void get_height() {
        for (int i = 1, k = 0; i <= n; i++) {
            if (rk[i] == 1)
                continue;
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k])
                k++;
            height[rk[i]] = k;
        }
    }
} lcs, lcp;

struct sparse_table {
    int st[maxN][25];
    int query(int l, int r) {
        if(l >= r) swap(l, r); l++;
        int k = __lg(r - l + 1);
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
    void build() {
        for (int i = 1; i < 25; i++)
            for (int j = 1; j + (1 << i) <= n + 1; j++)
                st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    }

} _lcs, _lcp;

int main() {
    cin >> (s + 1) >> m;
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
        lcs.s[n - i + 1] = lcp.s[i] = s[i];
    lcs.getsa(), lcp.getsa();
    lcs.get_height(), lcp.get_height();
    for (int i = 1; i <= n; i++)
        _lcs.st[i][0] = lcs.height[i], _lcp.st[i][0] = lcp.height[i];
    _lcs.build(), _lcp.build();
    int ans = 0;
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n; i += len) {
            int l = i, r = i + len + m;
            if (r > n) break;
            int R = n - l + 1, L = n - r + 1;
            int _s = min(len, _lcs.query(lcs.rk[L], lcs.rk[R]));
            int _p = min(len, _lcp.query(lcp.rk[l], lcp.rk[r]));
            // printf("%d %d %d %d %d %d\n", L, R, l, r, _s, _p);
            int cnt = _s + _p - len - !!(_s | _p) + 1;
            if (cnt > 0) ans += cnt;
            if (ans >= mod) ans -= mod;
        }
    }
    cout << ans;
    return 0;
}