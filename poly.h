#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 998244353;
int n;

using i64 = long long;

template <class T> inline constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template <int mod> struct MInt {
    int x;
    inline constexpr MInt() : x{} {}
    inline constexpr MInt(i64 x) : x{norm(x % mod)} {}
    inline constexpr int norm(int x) const {
        if (x < 0)
            x += mod;
        if (x >= mod)
            x -= mod;
        return x;
    }
    inline constexpr int val() const { return x; }
    explicit inline constexpr operator int() const { return x; }
    inline constexpr MInt operator-() const {
        MInt res;
        res.x = norm(mod - x);
        return res;
    }
    inline constexpr MInt inv() const {
        // assert(x != 0);
        return power(*this, mod - 2);
    }
    inline constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % mod;
        return *this;
    }
    inline constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    inline constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    inline constexpr MInt &operator/=(MInt rhs) & { return *this *= rhs.inv(); }
    friend inline constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend inline constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend inline constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend inline constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend inline constexpr std::istream &operator>>(std::istream &is,
                                                     MInt &a) {
        i64 v = 0;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend inline constexpr std::ostream &operator<<(std::ostream &os,
                                                     const MInt &a) {
        return os << a.val();
    }
    friend inline constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend inline constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};


template <int V, int mod> inline constexpr MInt<mod> CInv = MInt<mod>(V).inv();

using Z = MInt<mod>;

std::vector<int> rev;
template <int mod> std::vector<MInt<mod>> roots{0, 1};

template <int mod> inline constexpr MInt<mod> findPrimitiveRoot() {
    MInt<mod> i = 2;
    int k = __builtin_ctz(mod - 1);
    while (true) {
        if (power(i, (mod - 1) / 2) != 1) {
            break;
        }
        i += 1;
    }
    return power(i, (mod - 1) >> k);
}

template <int mod>
inline constexpr MInt<mod> primitiveRoot = findPrimitiveRoot<mod>();

template <> inline constexpr MInt<998244353> primitiveRoot<998244353>{31};

template <int mod> inline constexpr void dft(std::vector<MInt<mod>> &a) {
    int n = a.size();

    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }

    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    if (roots<mod>.size() < n) {
        int k = __builtin_ctz(roots<mod>.size());
        roots<mod>.resize(n);
        while ((1 << k) < n) {
            auto e =
                power(primitiveRoot<mod>, 1 << (__builtin_ctz(mod - 1) - k - 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots<mod>[2 * i] = roots<mod>[i];
                roots<mod>[2 * i + 1] = roots<mod>[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                MInt<mod> u = a[i + j];
                MInt<mod> v = a[i + j + k] * roots<mod>[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}

template <int mod> inline constexpr void idft(std::vector<MInt<mod>> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    MInt<mod> inv = (1 - mod) / n;
    for (int i = 0; i < n; i++) {
        a[i] *= inv;
    }
}

template <int mod = 998244353> struct Poly : public std::vector<MInt<mod>> {
    using Value = MInt<mod>;

    Poly() : std::vector<Value>() {}
    explicit inline constexpr Poly(int n) : std::vector<Value>(n) {}

    explicit inline constexpr Poly(const std::vector<Value> &a)
        : std::vector<Value>(a) {}
    inline constexpr Poly(const std::initializer_list<Value> &a)
        : std::vector<Value>(a) {}

    template <class InputIt, class = std::_RequireInputIter<InputIt>>
    explicit inline constexpr Poly(InputIt first, InputIt last)
        : std::vector<Value>(first, last) {}

    template <class F>
    explicit inline constexpr Poly(int n, F f) : std::vector<Value>(n) {
        for (int i = 0; i < n; i++) {
            (*this)[i] = f(i);
        }
    }

    inline constexpr Poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return Poly();
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }
    inline constexpr Poly trunc(int k) const {
        Poly f = *this;
        f.resize(k);
        return f;
    }
    inline constexpr friend Poly operator+(const Poly &a, const Poly &b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
        return res;
    }
    inline constexpr friend Poly operator-(const Poly &a, const Poly &b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
        return res;
    }
    inline constexpr friend Poly operator-(const Poly &a) {
        std::vector<Value> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = -a[i];
        }
        return Poly(res);
    }
    inline constexpr friend Poly operator*(Poly a, Poly b) {
        if (!(a.size() && b.size())) {
            return Poly();
        }
        if (a.size() < b.size()) {
            std::swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((mod - 1) & (n - 1)) != 0 || b.size() < 128) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return c;
        }
        a.resize(n), b.resize(n);
        dft(a), dft(b);
        for (int i = 0; i < n; ++i)
            a[i] *= b[i];
        idft(a);
        a.resize(tot);
        return a;
    }
    inline constexpr friend Poly operator*(Value a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    inline constexpr friend Poly operator*(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    inline constexpr friend Poly operator/(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] /= b;
        }
        return a;
    }
    inline constexpr Poly &operator+=(Poly b) { return (*this) = (*this) + b; }
    inline constexpr Poly &operator-=(Poly b) { return (*this) = (*this) - b; }
    inline constexpr Poly &operator*=(Poly b) { return (*this) = (*this) * b; }
    inline constexpr Poly &operator*=(Value b) { return (*this) = (*this) * b; }
    inline constexpr Poly &operator/=(Value b) { return (*this) = (*this) / b; }
    inline constexpr Poly deriv() const {
        if (this->empty()) {
            return Poly();
        }
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = (i + 1) * (*this)[i + 1];
        }
        return res;
    }
    inline constexpr Poly integr() const {
        Poly res(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = (*this)[i] / (i + 1);
        }
        return res;
    }
    inline constexpr Poly inv(int m) const {
        Poly x{(*this)[0].inv()};
        int k = 1;
        while (k < m) {
            k <<= 1;
            x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }
    inline constexpr Poly log(int m) const {
        return (deriv() * inv(m)).integr().trunc(m);
    }
    inline constexpr Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k <<= 1;
            x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }
    inline constexpr Poly pow(int k, int m) const {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return Poly(m);
        }
        Value v = (*this)[i];
        auto f = shift(-i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    }
    inline constexpr Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, mod>;
        }
        return x.trunc(m);
    }
    inline constexpr Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }
    inline constexpr std::vector<Value> eval(std::vector<Value> x) const {
        if (this->size() == 0) {
            return std::vector<Value>(x.size(), 0);
        }
        const int n = std::max(x.size(), this->size());
        std::vector<Poly> q(4 * n);
        std::vector<Value> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly &)> work =
            [&](int p, int l, int r, const Poly &num) {
                if (r - l == 1) {
                    if (l < int(ans.size())) {
                        ans[l] = num[0];
                    }
                } else {
                    int m = (l + r) / 2;
                    work(2 * p, l, m, num.mulT(q[2 * p + 1]).trunc(m - l));
                    work(2 * p + 1, m, r, num.mulT(q[2 * p]).trunc(r - m));
                }
            };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
    inline constexpr Poly<mod> power(i64 b) {
        auto _ = log((*this).size()) * b;
        return _.exp((*this).size());
    }
    inline constexpr Poly<mod> sin() {
        int img = 86583718;
        auto _ = ((*this) * img).exp((*this).size());
        return (_ - _.inv(_.size())) / 2 / img;
    }
    inline constexpr Poly<mod> cos() {
        int img = 86583718;
        auto _ = ((*this) * img).exp((*this).size());
        return (_ + _.inv(_.size())) / 2;
    }
};

template <int mod = 998244353> Poly<mod> berlekampMassey(const Poly<mod> &s) {
    Poly<mod> c;
    Poly<mod> oldC;
    int f = -1;
    for (int i = 0; i < s.size(); i++) {
        auto delta = s[i];
        for (int j = 1; j <= c.size(); j++) {
            delta -= c[j - 1] * s[i - j];
        }
        if (delta == 0) {
            continue;
        }
        if (f == -1) {
            c.resize(i + 1);
            f = i;
        } else {
            auto d = oldC;
            d *= -1;
            d.insert(d.begin(), 1);
            MInt<mod> df1 = 0;
            for (int j = 1; j <= d.size(); j++) {
                df1 += d[j - 1] * s[f + 1 - j];
            }
            assert(df1 != 0);
            auto coef = delta / df1;
            d *= coef;
            Poly<mod> zeros(i - f - 1);
            zeros.insert(zeros.end(), d.begin(), d.end());
            d = zeros;
            auto temp = c;
            c += d;
            if (i - temp.size() > f - oldC.size()) {
                oldC = temp;
                f = i;
            }
        }
    }
    c *= -1;
    c.insert(c.begin(), 1);
    return c;
}

template <int mod = 998244353>
MInt<mod> linearRecurrence(Poly<mod> p, Poly<mod> q, i64 n) {
    int m = q.size() - 1;
    while (n > 0) {
        auto newq = q;
        for (int i = 1; i <= m; i += 2) {
            newq[i] *= -1;
        }
        auto newp = p * newq;
        newq = q * newq;
        for (int i = 0; i < m; i++) {
            p[i] = newp[i * 2 + n % 2];
        }
        for (int i = 0; i <= m; i++) {
            q[i] = newq[i * 2];
        }
        n /= 2;
    }
    return p[0] / q[0];
}

inline ll read() {
    register ll num = 0, neg = 1;
    register char ch = getchar();
    while (!isdigit(ch) && ch != '-') {
        ch = getchar();
    }
    if (ch == '-') {
        neg = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        num = (num << 3) + (num << 1) + (ch - '0');
        num %= mod;
        ch = getchar();
    }
    return num * neg;
}

signed _main() {
    int n, m;
    cin >> n >> m;
    vector<MInt<mod>> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    Poly<mod> f(a);
    auto ans = (m ? f.cos() : f.sin());
    for (auto i : ans) {
        cout << i << " ";
    }
}