#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxN = 1e5 + 10;
int n, mod = 998244353;

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


inline void linear_inv(int* a, int* b, int n) {
    static int pre_mul[maxN]; memset(pre_mul, 0, sizeof pre_mul);
    pre_mul[0] = 1;
    for(int i = 1; i <= n; i++) pre_mul[i] = 1ll * pre_mul[i - 1] * a[i] % mod;
    b[n] = qpow(pre_mul[n], mod - 2);
    for(int i = n - 1; i >= 1; i--) b[i] = 1ll * b[i + 1] * a[i + 1] % mod;
    for(int i = 1; i <= n; i++) b[i] = 1ll * pre_mul[i - 1] * b[i] % mod;
}

