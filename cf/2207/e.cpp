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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    if (*max_element(all(a)) > n) {
        cout << "NO" << endl;
        return;
    }
    for (int i = 0; i < n-1; ++i) {
        if (a[i] < a[i+1]) {
            cout << "NO" << endl;
            return;
        }
    }
    vector<int> occ(n+1);
    set<int> pode;
    for (int i = 0; i < n; ++i) occ[a[i]]++;
    vector<int> b(n), tem(n+1);
    for (int i = 0; i < n; ++i) {
        if (occ[i] == 0) pode.insert(i);
    }
    if (a[0] == n-1) {
        b[0] = n;
    } else {
        b[0] = (*begin(pode));
        pode.erase(begin(pode));
    }
    tem[b[0]] = 1;
    for (int i = 1; i < n; ++i) {
        occ[a[i-1]]--;
        if (occ[a[i-1]] == 0 and tem[a[i-1]] == 0) {
            pode.insert(a[i-1]);
        }
        if (a[i] == a[i-1]) {
            // quero por alguem que ainda nao ta presente ali pra tras, mas que nao ta presente ali pra frente!
            if (pode.empty()) {
                cout << "NO" << endl;
                return;
            }
            b[i] = *begin(pode);
            tem[b[i]] = 1;
            pode.erase(begin(pode));
        } else {
            b[i] = n+1;
        }
    }
    cout << "YES" << endl;
    for (auto x : b) cout << x << " ";
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
