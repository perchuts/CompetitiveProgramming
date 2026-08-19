#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n; cin >> n;
    vector<int> a(n-1);
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto ncr = [&] (int a, int b) {
        if (a < b or b < 0) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat[n] = fexp(fat[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    for (auto& x : a) cin >> x;
    // consider that N is on position i
    int p1 = -1, p2 = -1;
    for (int i = 0; i < n-1; ++i) {
        if (a[i] == n-1) p2 = i;
        if (p1 == -1 and a[i] == n-1) p1 = i;
    }
    if (p1 == -1) {
        cout << 0 << endl;
        return;
    }
    for (int i = p1; i <= p2; ++i) {
        if (a[i] != n-1) {
            cout << 0 << endl;
            return;
        }
    }
    vector<int> tipo(n+1);
    for (int i = 1; i <= p1; ++i) {
        tipo[a[i-1]] = 1;
        if (a[i-1] > a[i]) {
            cout << 0 << endl;
            return;
        }
    }
    for (int i = p2; i < n-2; ++i) {
        if (a[i] < a[i+1] or tipo[a[i+1]] == 1) {
            cout << 0 << endl;
            return;
        }
        tipo[a[i+1]] = 2;
    }
    int i = 0, j = n-2, ans = 2, livre = 0, cur = 1;
    while (i != p1 or j != p2) {
        int spaces = 0;
        if (a[i] > a[j]) {
            while (a[j-1] == a[j]) j--, spaces++;
            while (cur < a[j]) livre += (tipo[cur++] == 0);
            j--;
        } else {
            while (a[i+1] == a[i]) i++, spaces++;
            while (cur < a[i]) livre += (tipo[cur++] == 0);
            i++;
        }
        int ways = ncr(livre, spaces) * fat[spaces] % mod;
        ans = ans * ways % mod;
        livre -= spaces;
        if (livre < 0) break;
    }
    while (cur < n-1) livre += (tipo[cur++] == 0);
    ans = ans * fat[livre] % mod;
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
