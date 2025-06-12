# 倍杀出题者 题解

## 思路
串串题。用 SA 大概也是能做的，但这里就说一下 SAM 怎么做就好。  

想到二倍串满足分配律（即 $2S+2T=2(S+T)$），我们有一个简单粗暴的做法：把二倍串做出来。  

做出来以后，我们建立 $s+2s$ 的 SAM，按照套路线段树合并。那么，对于每个节点，它产生的贡献是：对于他表示的每个偶数长度 $2i$ 的子串，$\rm{card}([1, n] \cap \rm{endpos})\times \rm{card}([n + 2i, 3n] \cap \rm{endpos})$，这里的 $\rm{endpos} \cap [n + 1, 3n]$ 只统计和 $n$ 同奇偶性的部分，以正确的统计答案。  

假设每个节点表示的子串的长度的区间是 $[2a, 2b]$，这样，每个 $[n, n + 2a)$ 都不产生贡献；每个 $[n + 2a, n + 2b]$ 产生 $\frac{i - (n + 2a)}{2} + 1$ 的贡献，每个 $(n + 2b, 3n]$ 产生 $b - a + 1$ 的贡献，当然每个节点还要乘上 $\rm{card}([1, n] \cap \rm{endpos})$。这样线段树节点维护俩信息即可。到此，已经容易统计出答案。

## std

```cpp
#include <bits/stdc++.h>

const int MAX = 1e6 + 5;
const int mod = 17171717;

int l, r, cnt, tot, lst = 1, tot1 = 1, tot2, n, q, m;

char S[MAX];

struct Node {
    int sum1, sum2;
    inline Node() {}
    inline Node(int a, int b) { sum1 = a % mod, sum2 = b % mod; }
    inline Node operator+(Node rhs) {
        return Node(sum1 + rhs.sum1, sum2 + rhs.sum2);
    }
    inline Node operator+=(Node rhs) { return *this = *this + rhs; }
} st[MAX << 4];
int ls[MAX << 4], rs[MAX << 4];
int h[MAX], rt[MAX], pos[MAX], ans[MAX];

inline void pu(int x) {
    st[x] = st[ls[x]] + st[rs[x]];
}

int merge(int l, int r) {
    if (!l or !r) {
        return l | r;
    }
    int x = ++tot;
    ls[x] = merge(ls[l], ls[r]);
    rs[x] = merge(rs[l], rs[r]);
    pu(x);
    return x;
}

Node qry(int l, int r, int s, int t, int x) {
    if (!x) {
        return {0, 0};
    }
    if (l >= s and r <= t) {
        return st[x];
    }
    int k = l + ((r - l) >> 1);
    Node res = {0, 0};
    if (k >= s) {
        res += qry(l, k, s, t, ls[x]);
    }
    if (k < t) {
        res += qry(k + 1, r, s, t, rs[x]);
    }
    return res;
}

int build(int l, int r, int s) {
    int x = ++tot;
    int k = l + ((r - l) >> 1);
    if (l == r) {
        st[x] = {(s - n) >> 1, 1};
        return x;
    }
    if (k >= s) {
        ls[x] = build(l, k, s);
    } else {
        rs[x] = build(k + 1, r, s);
    }
    pu(x);
    return x;
}

struct E {
    int v, x;
} e[MAX];
struct N {
    int l, f, p, c[26];
} t[MAX];

inline void add(int u, int v) {
    e[++tot2] = {v, h[u]};
    h[u] = tot2;
}

inline void ins(int c, int k) {
    int p = lst, np = lst = ++tot1;
    if (!(k > n && (k - n) & 1))
        rt[np] = build(1, 3 * n, k);
    for (; p and !t[p].c[c]; p = t[p].f) {
        t[p].c[c] = np;
    }
    if (!p) {
        t[np].f = 1;
        return;
    }
    int q = t[p].c[c];
    if (t[q].l == t[p].l + 1) {
        t[np].f = q;
        return;
    }
    int nq = ++tot1;
    t[nq] = t[q];
    t[nq].l = t[p].l + 1;
    t[np].f = t[q].f = nq;
    for (; p and t[p].c[c] == q; p = t[p].f) {
        t[p].c[c] = nq;
    }
}

inline void _build() {
    for (int i = 2; i <= tot1; ++i) {
        add(t[i].f, i);
    }
}
void dfs(int u) {
    for (int i = h[u]; i; i = e[i].x) {
        int v = e[i].v;
        dfs(v);
        rt[u] = merge(rt[u], rt[v]);
    }
}

int main() {
    scanf("%s", S + 1);
    n = strlen(S + 1);
    for (int i = 1; i <= n; ++i) {
        S[i * 2 - 1 + n] = S[i * 2 + n] = S[i];
    }
    for (int i = 1; i <= n * 3; i++)
        ins(S[i] - 'a', i);
    _build();
    dfs(1);
    int ans = 0;
    for (int i = 1; i <= tot1; i++) {
        int a = t[t[i].f].l + 1, b = t[i].l;
        if (a & 1)
            a++;
        if (b & 1)
            b--;
        a >>= 1, b >>= 1;
        int w = qry(1, 3 * n, 1, n, rt[i]).sum2;
        Node tmp = qry(1, 3 * n, n + 2 * a, n + 2 * b, rt[i]);
        ans += 1ll * w * (tmp.sum1 - (a - 1) * tmp.sum2) % mod;
        ans += 1ll * w * qry(1, 3 * n, n + 2 * b + 1, 3 * n, rt[i]).sum2 *
               (b - a + 1) % mod;
        ans %= mod;
    }
    printf("%d", ans);
    return 0;
}

```