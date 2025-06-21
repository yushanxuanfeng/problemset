#include <bits/stdc++.h>
#include "poly.h"
using namespace std;
using ll = long long;
const int maxN = 1e5 + 10;


inline int qpow(int a, int b) {
    assert(b >= 0);
    int ans = 1;
    while(b) {
        if(b & 1) ans = 1ll * ans * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return ans;
}



int fac[maxN], facinv[maxN];
inline void linear_inv(int* a, int* b, int n) {
    static int pre_mul[maxN]; memset(pre_mul, 0, sizeof pre_mul);
    pre_mul[0] = 1;
    for(int i = 1; i <= n; i++) pre_mul[i] = 1ll * pre_mul[i - 1] * a[i] % mod;
    b[n] = qpow(pre_mul[n], mod - 2);
    for(int i = n - 1; i >= 1; i--) b[i] = 1ll * b[i + 1] * a[i + 1] % mod;
    for(int i = 1; i <= n; i++) b[i] = 1ll * pre_mul[i - 1] * b[i] % mod;
}


int main() {
    int n, k;
    cin >> n >> k;
    
    fac[0] = fac[1] = facinv[1] = 1;
    for(int i = 2; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    linear_inv(fac, facinv, n);
    cout << "\n";
    Poly<mod> _sin(n + 1);
    for(int i = 1; i <= n; i++) {
        if(i & 1) {
            _sin[i] = (i & 2 ? -1 : 1);
            (_sin[i]) *= (facinv[i]);
        } else _sin[i] == 0;
    }

    Poly<mod> _cos(n + 1);
    for(int i = 1; i <= n; i++) {
        if(i & 1) {
            _cos[i] = 0;
        } else {
            _cos[i] = (i & 2 ? -1 : 1);
            _cos[i] *= facinv[i];
        }
    }
    _sin[0] = _cos[0] = 1;
    auto E = _sin * _cos.inv(n + 1);
    E = E.pow(k, E.size());
    cout << E[k] * fac[n];
}