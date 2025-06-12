#include <bits/stdc++.h>
#define i128 __int128_t
using namespace std;
int n, p;
int c[3001][3001], d[3001], dd[3001];
bool vis[3001][3001];
int res[3001][3001];
inline int b(int m, int k) {
    if (!k)
        return 0;
    if (vis[m][k])
        return res[m][k];
    vis[m][k] = 1;
    int upper = min((n - m) / k, m), i;
    i128 ans = 0;
    for (i = 0; i <= upper; i++)
        ans += (i & 1 ? -1ll : 1ll) * c[n - i * k - 1][m - 1] * c[m][i];
    return res[m][k] = (ans % p + p) % p;
}
int main() {
    int i, j;
    scanf("%d%d", &n, &p);
    d[0] = 1;
    c[0][0] = 1;
    for (i = 2; i <= n; i++)
        d[i] = 1ll * (d[i - 1] + d[i - 2]) * (i - 1) % p,
        dd[i] = d[i] + d[i - 1];
    for (i = 1; i <= n; i++) {
        c[i][0] = 1;
        for (j = 1; j <= i; j++) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            if (c[i][j] >= p)
                c[i][j] -= p;
        }
    }
    i128 ans = 0;
    for (i = 1; i < n; i++)
        for (j = 1; j <= n; j++)
            ans += (i128)1 * (b(j, i) - b(j, i - 1)) * dd[j] * i;
    printf("%lld", ((ans + n) % p + p) % p);
}