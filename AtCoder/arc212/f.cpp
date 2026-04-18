#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
    int n, m, x; cin >> n >> m >> x;
    // so precisamos resolver o caso com gcd(a1, a2) = 1
    // a[3]-a[2] = value added to form a[3] = +- a[1]
    // a[4]-a[3] = value added to form a[4] = +- a[2]
    // a[5]-a[4] = value added to form a[5] = += a[3]
    // number of ways to get to coordinate (x, y) in N-2 steps
    int ans = 0;
    for (int y = 1; y <= m; ++y) { 
        int a = y, b = x, left = n-2, z;
        while (left) {
            if (left == 1) {
                z = abs(a-b);
                b = a;
                a = z;
                break;
            }
            if (left == 2) {
                z = abs(a-b);
                b = a;
                a = z;
                z = abs(a-b);
                b = a;
                a = z;
                break;
            }
            if (a == b) {
                if (left % 3) {
                    // one of them is going to be zero, ignore
                    a = b = 0; break;
                } else {
                    break;
                }
            }
            // this is safe
            if (b < a) {
                z = abs(a-b);
                b = a;
                a = z;
                z = abs(a-b);
                b = a;
                a = z;
                left -= 2;
                continue;
            }
            // a < b
            if (a == 0) {
                a = b;
                left -= 2;
                continue;
            }
            int rounds = b / a;
            if (rounds == 1) {
                z = abs(a-b);
                b = a;
                a = z;
                left--;
                continue;
            }
            int want = 3 * (rounds/2);
            if (want > left) { 
                int consigo = left / 3;
                b -= 2 * consigo * a;
                left %= 3;
                continue;
            }
            b -= a*(rounds/2)*2;
            left -= want;
        }
        ans = (ans + a*b) % mod;
    }
    if (n % 3 == 1) ans = (ans + x*x) % mod;
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
