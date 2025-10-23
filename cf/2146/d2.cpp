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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int l, r; cin >> l >> r;
    int tot = 0, L = l;
    vector<int> ans(r-l+1, -1);
	int lx = l, rx = r;
    for (int i = 29; ~i; --i) {
        if (r >> i & 1) {
            int st = (1 << i);
            int menor = max(0LL, st-l), maior = r - st + 1;
            int x = (1 << (i+1)) - 1;
            if (menor == maior) {
                for (int j = lx; j <= rx; ++j) ans[j-L] = x ^ j;
                tot +=  (r-l+1) * x;
                break;
            }
            if (menor == 0) {
                tot += (r-l+1) * (1LL << i);
                r -= (1 << i);
                l -= (1 << i);
                continue;
            }
            tot += 2 * x * min(menor, maior);
            if (menor > maior) {
                // fold right
                for (int j = rx-maior+1; j <= rx; ++j) ans[j-L] = j ^ x, ans[(j ^ x) - L] = j;
                r -= 2 * maior;
				rx -= 2 * maior;
            }
            else {
                // fold left
                for (int j = lx; j < lx+menor; ++j) ans[j-L] = j ^ x, ans[(j ^ x) - L] = j;
                l += 2 * menor, i++;
				lx += 2 * menor;
            }
        }
    }
    cout << tot << endl;
    for (int i = 0; i < r-l+1; ++i) if (ans[i] == -1) ans[i] = L + i;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
