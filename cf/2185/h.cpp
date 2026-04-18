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

vector<int> brute(int n, int k, vector<int> a) {
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        for (int pos = 0; pos < n; ++pos) {
            a.erase(begin(a)+i);
            a.insert(begin(a)+pos, val);
            int s = 0, used = 0;
            // minha nova posicao eh a posicao pos
            for (int j = 0; j < pos; ++j) s += a[j];
            if (s >= a[pos]) used++;
            s += a[pos];
            for (int j = pos+1; j < n; ++j) {
                if (s < a[j]) used++;
                s += a[j];
            }
            if (used <= k) {
                ans[i]++;
            }
            a.erase(begin(a)+pos);
            a.insert(begin(a)+i, val);
        }
    }
    return ans;
}

vector<int> solve(int n, int k, vector<int> a) {
    return vector<int>();
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        auto ans = brute(n, k, a);
        for (auto x : ans) cout << x << " ";
        cout << endl;
    }
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
