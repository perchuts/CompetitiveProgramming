#include <bits/stdc++.h>
#define endl '\n'
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;

const int mod = 1e9+7;

int fat[5001], ifat[5001], score2[5001][5001];

int C(int a, int b) {
    return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
}

int fexp(int b, int e) {
    int ans = 1;
    while (e) {
        if (e&1) ans = ans * b % mod;
        e /= 2, b = b * b % mod;
    }
    return ans;
}
int N = 5000;
void solve(){
    int n, a, b; cin >> n >> a >> b;
    if (a == 0 and b == 0) {
        cout << fat[n] << endl;
        return;
    }
    if (a + b > n or min(a, b) == 0) {
        cout << 0 << endl;
        return;
    }
    int ans = C(n, a+b) * fat[n] % mod * score2[a+b][a] % mod;
    cout << ans << endl;
}
int32_t main(){_
    fat[0] = 1;
    for (int i = 1; i <= N; ++i) fat[i] = i * fat[i-1] % mod;
    ifat[N] = fexp(fat[N], mod-2);
    for (int i = N-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    score2[2][1] = 1;
    for (int i = 3; i <= N; ++i) {
        for (int j = 1; j < i; ++j) {
            score2[i][j] = score2[i-1][j] * j + score2[i-1][j-1] * (i-j);
            score2[i][j] %= mod;
            score2[i][j] = (score2[i][j] + score2[i-2][j-1] * (i-1)) % mod;
        }
    }
    int t = 1; cin >> t;
    while(t--) solve();
}
