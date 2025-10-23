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

void solve(int n) {
    // se n eh multiplo de 10
    if (n == 1) {
         cout << 1 << endl;
         return;
    }
    vector<int> dist(n, inf);
    vector<int> who(n);
    auto recover = [&] () {
        int cur = 0;
        string ans(dist[0], '0');
        while (true) {
            ans[dist[cur]-1] = '1';
            cur = who[cur];
            if (cur == 0) break;
        }
        reverse(all(ans));
        cout << ans << endl;
    };
    dist[1] = 1;
    int val = 1;
    for (int i = 1; i < n; ++i) {
        val = 10 * val % n;
        for (int j = 0; j < n; ++j) {
            if (dist[j] <= i) {
                int nv = (j + val) % n;
                if (dist[nv] == inf) {
                    dist[nv] = i + 1;
                    who[nv] = j;
                }
            }
        }
        if (dist[val] == inf) {
            dist[val] = i + 1;
        }
        if (dist[0] != inf) {
            recover();
            return;
        }
    }
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    solve(n);
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
