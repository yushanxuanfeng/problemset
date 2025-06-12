#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxN = 1e7 + 10;
int n, q;

int a[maxN];

struct Node
{
    int m, cnt;
    Node operator+(const Node &o) const
    {
        if (m == o.m)
            return {m, cnt + o.cnt};
        else if (cnt > o.cnt)
            return {m, cnt - o.cnt};
        else if (cnt == o.cnt)
            return {min(o.m, m), 0};
        else 
            return {o.m, o.cnt - cnt};
    }
    Node operator += (const Node &rhs) {
        return *this = *this + rhs;
    }
} ;

struct SegTree {
    Node ans[maxN << 2], tag[maxN << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid ((l + r) >> 1)
    void pushup(int p) { ans[p] = ans[ls] + ans[rs]; }
    void build(int p, int l, int r) {
        if(l == r)
            return void(ans[p] = {a[l], 1});
        build(ls, l, mid), build(rs, mid + 1, r);
        pushup(p);
    }
    Node query(int p, int l, int r, int nl, int nr) {
        if(nl <= l && r <= nr) return ans[p];
        Node res = {0, 0};
        if(nl <= mid) res += query(ls, l, mid, nl, nr);
        if(nr > mid) res += query(rs, mid + 1, r, nl, nr);
        return res;
    }

} tree;

using ull = unsigned long long;
ull seed;

ull shift(ull x) {
    x ^= seed;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= seed;
    return x;
}

ull _rand() {
    seed = shift(seed);
    return shift(seed) ^ shift(seed ^ (seed << 17));
}

pair<int, int> get_query() {
    int a = _rand() % n, b = _rand() % n;
    a++, b++;
    if (a > b)
        swap(a, b);
    return make_pair(a, b);
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> q >> seed;
    for(int i = 1; i <= n; i++) cin >> a[i];
    tree.build(1, 1, n);
    int ans = 0;
    for(int i = 1; i <= q; i++) {
        int l, r; tie(l, r) = get_query();
        ans ^= (tree.query(1, 1, n, l, r).m * i);
    }
    cout << ans;
}
