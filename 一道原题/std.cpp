#include <bits/stdc++.h>
using namespace std;
typedef unordered_map<int, int> umap;
constexpr int maxN = 1e6 + 9, _lg = 20, _llg = 6, _lllg = 3;
constexpr int S = (maxN >> _llg) + 1, Z = 1 << (_llg * _lllg);
int n, m, c[maxN];
struct node {
    int val, c;
    node() : val(0), c(0) {}
    node(int x, int c) : val(x), c(c) {}
    node(int x) : val(x), c(1) {}
    friend node operator+(const node& a, const node& b) {
        if (a.val == b.val)
            return {a.val, a.c + b.c};
        if (a.c > b.c)
            return {a.val, a.c - b.c};
        return {b.val, b.c - a.c};
    }
};
template <int L, int maxN>
struct ct_tree {
    node val[maxN], ct[L][maxN];
    void build(node* a, int n) {
        copy_n(a, n, val);
        for (int h = 0, s = 1; s < n; ++h, s <<= 1)
            for (int i = s; i <= n; i += s << 1) {
                ct[h][i - 1] = val[i - 1];
                for (int j = i - 1; j > i - s; --j)
                    ct[h][j - 1] = val[j - 1] + ct[h][j];
                if (i == n)
                    break;
                ct[h][i] = val[i];
                for (int j = i + 1; j < i + s && j < n; ++j)
                    ct[h][j] = ct[h][j - 1] + val[j];
            }
    }
    node query(int l, int r) const {
        if (l == r)
            return val[l];
        int h = __lg(l ^ r);
        return ct[h][l] + ct[h][r];
    }
};
vector<int> dsct(int* a, int n) {
    umap tmp;
    vector<int> ret;
    for (int i = 0, t = 0; i < n; ++i) {
        int& x = tmp[a[i]];
        if (!x)
            ret.push_back(a[i]), x = ++t;
        a[i] = x - 1;
    }
    return ret;
}
umap s[maxN];
vector<int> idv;
node qans[Z][_llg][_llg];
struct iiblk {
    vector<int> idv;
    int st;
    void build(int* c, int n) {
        idv = dsct(c, n), st = 0;
        for (int i = 0; i < n; ++i)
            st |= c[i] << (i * _lllg);
    }
    node query(int l, int r) const {
        node ans = qans[st][l][r];
        ans.val = idv[ans.val];
        return ans;
    }
};
struct iblk {
    ct_tree<W, B> bs;
    iiblk ib[_lg];
    void build(int* c, int n) {
        int z = ((n - 1) >> _lllg) + 1;
        vector<node> val(z);
        for (int i = 0; i < n; ++i)
            val[i >> _lllg] = val[i >> _lllg] + c[i];
        bs.build(val.data(), z);
        for (int i = 0; i < z; ++i)
            ib[i].build(c + (i << _lllg), min(n - (i << _lllg), _llg));
    }
    node query(int l, int r) const {
        int lb = l >> _lllg, rb = r >> _lllg;
        if (lb == rb)
            return ib[lb].query(l & (_llg - 1), r & (_llg - 1));
        node ret =
            ib[lb].query(l & (_llg - 1), _llg - 1) + ib[rb].query(0, r & (_llg - 1));
        if (lb + 1 < rb)
            ret = ret + bs.query(lb + 1, rb - 1);
        return ret;
    }
} ib[S];
ct_tree<B, S> ct;
inline void init() {
    for (int s = 0; s < Z; ++s)
        for (int l = 0; l < _llg; ++l) {
            node tmp;
            for (int r = l; r < _llg; ++r)
                qans[s][l][r] = tmp = tmp + ((s >> (r * _lllg)) & (_llg - 1));
        }
    idv = dsct(c, n);
    vector<vector<int>> pos(n);
    for (int i = 0; i < n; ++i)
        pos[c[i]].push_back(i);
    for (int t = 0; t < n; ++t) {
        vector<int>& occ = pos[t];
        int k = occ.size();
        if (!k)
            continue;
        vector<int> val(k);
        for (int i = 0; i < k; ++i)
            val[i] = 2 * i - occ[i];
        basic_string<bool> pmn(k, false), smx(k, false);
        vector<int> sufmx(k);
        vector<pair<int, int>> itv, tmp;
        for (int i = 0, p = INT_MAX; i < k; ++i)
            if ((pmn[i] = val[i] < p))
                p = val[i];
        for (int i = k - 1, p = INT_MIN; ~i; --i)
            if ((smx[i] = val[i] > (sufmx[i] = p)))
                p = val[i];
        for (int i = 0, j = 0, w = 0; i < k; ++i) {
            if (!pmn[i])
                continue;
            while (j < k && (sufmx[j] >= val[i]))
                ++j;
            while (w < k && (w < i || !smx[w]))
                ++w;
            if (j < i)
                break;
            int l = max(i ? occ[i - 1] + 1 : 0, occ[i] - (val[w] - val[i]));
            int r = min(j < k - 1 ? occ[j + 1] - 1 : n - 1,
                        occ[j] + (val[j] - val[i]));
            itv.emplace_back(l, r);
        }
        int l = -1e9, r = l - 1;
        for (auto [pl, pr] : itv)
            if (pl > r + 1) {
                if (l <= r)
                    tmp.emplace_back(l - 1, r);
                l = pl, r = pr;
            } else
                r = max(r, pr);
        if (l <= r)
            tmp.emplace_back(l - 1, r);
        for (int i = 0; auto [l, r] : tmp)
            for (int j = l; j <= r; ++j) {
                while (i < k && occ[i] <= j)
                    ++i;
                s[t].emplace(j, i);
            }
    }
    int z = ((n - 1) >> _llg) + 1;
    vector<node> val(z);
    for (int i = 0; i < n; ++i)
        val[i >> _llg] = val[i >> _llg] + c[i];
    ct.build(val.data(), z);
    for (int i = 0; i < z; ++i)
        ib[i].build(c + (i << _llg), min(n - (i << _llg), _lg));
}
inline int gsum(int p, int x) {
    auto it = s[x].find(p);
    if (it == s[x].end())
        return -1;
    return it->second;
}
inline bool chk(int l, int r, int x) {
    int sl = gsum(l - 1, x), sr = gsum(r, x);
    if (!~sl || !~sr)
        return false;
    return ((sr - sl) << 1) > r - l + 1;
}
inline int qbase(int l, int r) {
    int lb = l >> _llg, rb = r >> _llg;
    if (lb == rb)
        return ib[lb].query(l & (_lg - 1), r & (_lg - 1)).val;
    node ret = ib[lb].query(l & (_lg - 1), _lg - 1) + ib[rb].query(0, r & (_lg - 1));
    if (lb + 1 < rb)
        ret = ret + ct.query(lb + 1, rb - 1);
    return ret.val;
}
inline int query(int l, int r) {
    int x = qbase(l, r);
    return chk(l, r, x) ? idv[x] : 0;
}
using ull = unsigned long long;
ull seed;

inline ull shift(ull x) {
    x ^= seed;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= seed;
    return x;
}

inline ull _rand() {
    seed = shift(seed);
    return shift(seed) ^ shift(seed ^ (seed << 17));
}

inline pair<int, int> get_query() {
    int a = _rand() % n, b = _rand() % n;
    a++, b++;
    if (a > b)
        swap(a, b);
    return make_pair(a, b);
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> seed;
    for (int i = 0; i < n; ++i)
        cin >> c[i];
    init();
    int ans = 0;
    for (int l, r, i = 1; i <= m; i++) {
        tie(l, r) = get_query();
        ans ^= (query(--l, --r) * i);
    }
    cout << ans;
    return 0;
}
