#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxN = 1e3 + 10;
int n;
char s[maxN];

int calc(int i, int j) {
    int res = 0;
    while(i <= n && j <= n) {
        if(s[i] == s[j] && s[j] == s[j + 1]) {
            res++; i++, j += 2;
        } else {
            return res;
        }
    }
    return res;
}

int main() {
    cin >> (s + 1); n = strlen(s + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            ans += calc(i, j);
            if(ans >= 17171717) ans -= 17171717;
        }
    }
    cout << ans;
}