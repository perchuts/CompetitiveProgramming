#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int solve2(int n, vector<int> a) {
    int S = 0;
    for (auto x : a) S += x;
    if (S & 1) {
        cout << -1 << endl;
        return -1;
    }
    for (auto x : a) {
        if (2 * x > S) {
            cout << -1 << endl;
            return -1;
        }
    }
        int esq = 0, id = 0;
        for (int i = 0; i < n; ++i) {
            if (2 * (esq + a[i]) > S) break;
            esq += a[i], id = i;
        }
        vector<int> agr(n);
    if (2 * esq == S) {
        cout << 1 << endl;
        for (auto x : a) cout << x << ' ';
        cout << endl;
        return 1;
    }
    int dir = 0;
    for (int i = n-1; i > id+1; --i) dir += a[i];
    int A = (a[id+1] - dir + esq) / 2;
    for (int i = 0; i <= id; ++i) agr[i] = a[i];
    agr[id+1] = A;
    A = esq - A;
    for (int i = id+2; i < n; ++i) {
        agr[i] = min(A, a[i]);
        A -= agr[i];
    }
    for (int i = 0; i < n; ++i) {
        assert(agr[i] <= a[i]);
        a[i] -= agr[i];
    }
    cout << 2 << endl;
    for (auto x : agr) cout << x << ' ';
    cout << endl;
    for (auto x : a) cout << x << ' ';
    cout << endl;
    return 2;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        solve2(n, a);
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 6);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 10);
        cout << flush;
        int x1 = solve(n, a), x2 = solve2(n, a);
        if (x1 < x2) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << x2 << endl;
            cout << "Answer: " << x1 << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
