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
    vector<int> b(n), freq(n);
    for (auto& x : b) cin >> x, freq[x]++;
    int tot = freq[0];
    for (int i = 1; i < n; ++i) {
        if (freq[i] > 0 and i > tot) {
            cout << "No" << endl;
            return;
        }
        tot += freq[i];
    }
    vector<int> ans(n);
    vector<int> prox(n), ant(n);
    ant[0] = -1, prox[0] = 1;
    for (int i = 1; i < freq[0]; ++i) {
        ant[i] = i-1;
        if (i != freq[0]-1) prox[i] = i+1;
        else prox[i] = -1;
    }
    int ptr_ith = 0, pos = freq[0];
    vector<int> val(n);
    // add j after i
    auto add = [&] (int i, int j) {
        if (prox[i] == -1) {
            prox[i] = j;
            ant[j] = i;
            return;
        }
        int k = prox[i];
        ant[k] = prox[i] = j;
        ant[j] = i, prox[j] = k;
    };
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < freq[i]; ++j) {
            add(ptr_ith, pos);
            val[pos++] = i;
        }
        ptr_ith = prox[ptr_ith];
    }
    cout << "Yes" << endl;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        cout << val[cur] << " ";
        cur = prox[cur];
    }
    cout << endl;
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
