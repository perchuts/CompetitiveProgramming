#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
void solve(int n, vector<int> p) {
    vector<int> onde(n);
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    int qu = 0;
    auto ask = [&] (int x, int y) {
        qu++;
        assert(qu <= (5*n/2+800));
        int a, b;
#ifndef gato
        cout << "? " << x+1 << " " << y+1 << endl;
        cin >> a >> b;
        --a, --b;
#else
        cout << "asking to: " << x << " " << y << endl;
        a = x, b = y;
        if (rnd(0, 1)) a = n - 1 - a, b = n - 1 -b;
        cout << "given: " << a << " " << b << endl;
#endif
        swap(onde[p[a]], onde[p[b]]);
        swap(p[a], p[b]);
#ifdef gato
        for (auto x : p) cout << x << " ";
        cout << endl;
#endif
        return (a == x and b == y);
    };
    while (onde[n/2] != n/2 and n % 2 == 1) ask(onde[n/2], n/2); 
    vector<int> comp(n);
    for (int i = 0; i < n/2; ++i) comp[i] = comp[n-1-i] = i;
    set<int> s;
    for (int i = 0; i < n/2; ++i) s.insert(i);
    while (!s.empty()) {
        int i = *begin(s);
        if (comp[p[i]] != comp[p[n-1-i]]) {
            int j = comp[onde[n-1-p[i]]];
            if (ask(n-1-i, onde[n-1-p[i]])) s.erase(i);
            else s.erase(j);
        }
        else s.erase(i);
    }
    //for (int i = 0; i < n/2; ++i) {
    //    if (comp[p[i]] != comp[p[n-1-i]]) ask(n-1-i, onde[n-1-p[i]]);
    //}
    for (int i = 0; i < n/2; ++i) {
        int pos = onde[i];
        if (comp[pos] == i) {
            if (onde[i] != i) ask(i, n-1-i);
            continue;
        }
        while (true) {
            int z = ask(pos, i);
            if (z and ask(n-1-pos, n-1-i)) break;
            else if (!z and ask(pos, i)) break;
        }
    }
#ifndef gato
    cout << "!" << endl;
#else
    for (int i = 0; i < n; ++i) assert(p[i] == i);
#endif
    
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> p(n);
        for (auto& x : p) cin >> x, --x;
        solve(n, p);
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 69);
        vector<int> p(n); iota(all(p), 0);
        shuffle(all(p), rng);
        cout << n << endl;
        for (auto x : p) cout << x + 1 << " ";
        cout << endl;
        solve(n, p);
    }
#endif
}
