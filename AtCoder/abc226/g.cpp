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

bool solve(vector<int> a, vector<int> b){
    swap(a, b);
    bool L = 0;
    auto apply = [&] (auto&&self) {
        for (int i = 1; i <= 5; ++i) {
            int k = min(a[i], b[i]);
            a[i] -= k, b[i] -= k;
        }
        int x = -1;
        for (int i = 5; i >= 1; --i) {
            if (a[i]) {
                if (x != -1) break;
                x = i;
            }
            if (b[i]) {
                if (x == -1) {
                    L = 1;
                    return;
                }
                int k = min(b[i], a[x]);
                b[i] -= k;
                a[x] -= k;
                a[x-i] += k;
                return void(self(self));
            }
        }
        x = -1;
        for (int i = 1; i <= 5; ++i) {
            if (a[i]) {
                if (x == -1) a[i] = 0;
                else {
                    int k = min(a[i], b[x]);
                    a[i] -= k;
                    b[x] -= k;
                    a[i-x] += k;
                    return void(self(self));
                }
            }
            if (b[i]) {
                if (x != -1) break;
                x = i;
            }
        }
    };
    apply(apply);
    if (L) return false;
    int i = 5, j = 5;
    while (j) {
        if (i < j) return false;
        if (b[j] == 0) j--;
        else if (a[i] == 0) i--;
        else {
            int k = min(a[i], b[j]);
            a[i] -= k;
            a[i-j] += k;
            b[j] -= k;
        }
    }
    return true;
}

bool brute(vector<int> a, vector<int> b) {
    // backtrackzao
    swap(a, b);
    for (int i = 1; i <= 5; ++i) {
        int k = min(a[i], b[i]);
        a[i] -= k, b[i] -= k;
    }
    auto go = [&] (auto&& self, int i) -> bool {
        if (i == 6) return true;
        if (b[i] == 0) return self(self, i+1);
        b[i]--;
        for (int j = i; j <= 5; ++j) {
            if (a[j] == 0) continue;
            a[j]--, a[j-i]++;
            if (self(self, i)) return true;
            a[j]++, a[j-i]--;
        }
        b[i]++;
        return false;
    };
    return go(go, 1);
}

int32_t main(){_
#ifndef gato
    int t; cin >> t;
    while (t--) {
        vector<int> a(6), b(6);
        for (int i = 1; i <= 5; ++i) cin >> a[i];
        for (int i = 1; i <= 5; ++i) cin >> b[i];
        cout << (solve(a, b) ? "Yes" : "No") << endl;
    }
#else
    int t = 1;
    while (true) {
        vector<int> a(6), b(6);
        int s1 = 0, s2 = 0;
        int lima = 8, limb = 8;
        for (int i = 1; i <= 5; ++i) a[i] = rnd(0, lima), b[i] = rnd(0, limb), s1 += a[i], s2 += b[i];
        if (min(s1, s2) == 0) continue;
        int my = solve(a, b), ans = brute(a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            for (int i = 1; i <= 5; ++i) cout << a[i] << ' ';
            cout << endl;
            for (int i = 1; i <= 5; ++i) cout << b[i] << ' ';
            cout << endl;
            cout << "Your output: " << (my ? "Yes" : "No") << endl;
            cout << "Answer: " << (ans ? "Yes" : "No") << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
