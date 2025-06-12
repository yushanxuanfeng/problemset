#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    cout<< setiosflags(ios::fixed) << setprecision(3);
    if(n == 3) return cout << -1.0, 0;
    if(n == 4) return cout << 1, 0;
    if(n == 5) return cout << 3.5, 0;
    if(n == 6) return cout << 8.5, 0;
    return cout << 1ll * n * (n + 1) / 4.0, 0;
}