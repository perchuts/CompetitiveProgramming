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
    vector<array<int, 6>> a(n);
    for (auto& x : a) for (int i = 0; i < 6; ++i) cin >> x[i];
    vector<int> ans(n);
    for (int __ = 0; __ < 3; ++__) {
        vector sexo(101, vector(101, vector(101, -1)));
        vector<int> foi(n, -1);
        for (int i = 0; i < n; ++i) {
            for (int w = 0; w < 2; ++w) {
                for (int x = a[i][0]; x < a[i][3]; ++x) {
                   for (int y = a[i][1]; y < a[i][4]; ++y) {
                        if (sexo[x][y][a[i][2]] != -1) {
                            if (foi[sexo[x][y][a[i][2]]] != i) {
                                foi[sexo[x][y][a[i][2]]] = i;
                                ans[sexo[x][y][a[i][2]]]++;
                                ans[i]++;
                            }
                        } else sexo[x][y][a[i][2]] = i;
                    }
                }
                swap(a[i][2], a[i][5]);
            }
        }
        for (auto& x : a) {
            swap(x[0], x[1]);
            swap(x[0], x[2]);
            swap(x[3], x[4]);
            swap(x[3], x[5]);
        }
    }
    for (auto x : ans) cout << x << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
