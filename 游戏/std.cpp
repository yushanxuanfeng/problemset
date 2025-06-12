#include<bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
vector<int> edges[maxN];
int p[maxN]; bool root[maxN];
int ans, sumxor[maxN];
long long sum[maxN];

void dfs(int u) {
    sum[u] = sumxor[u] = p[u];
    for(int i: edges[u]) {
        dfs(i);
        sum[u] += sum[i], sumxor[u] ^= sumxor[i];
    }
    if(sumxor[u] ^ sum[u]) ans++;
}

signed main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m; long long res = 0; cin >> n >> m;
    memset(root, 1, sizeof root);
    for(int i = 1, u, v; i <= m; i++) {
        cin >> u >> v; edges[u].push_back(v); root[v] = false;
    }
    for(int i = 1; i <= n; i++) cin >> p[i], res += p[i];
    for(int i = 1; i <= n; i++) { if(root[i]) dfs(i); }
    cout << res << "\n" << ans;
}