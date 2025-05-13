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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(int n, vector<int> h){
    vector<int> p(n);
    p[0] = 1;
    int ops = 0;
    auto get_inv = [&] () {
        int tot = 0;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) tot += (h[i] > h[j]);
        return tot;
    };
    auto apply = [&] (int i, int j) {
        ops++;
        assert(ops <= 4*n);
        reverse(begin(p)+i, begin(p)+j+1);
#ifdef gato
        reverse(begin(h)+i, begin(h)+j+1);
        return get_inv();
#else
        cout << i + 1 << ' ' << j + 1 << endl;
        //reverse(begin(h)+i, begin(h)+j+1);
        int x; cin >> x;
        if (x == 0) exit(0);
        return x;
#endif
    };
    for (int i = 1; i < n; ++i) {
        int cur = apply(i, i);
        apply(0, i);
        int cur2 = apply(1, i);
        // antes eu tinha x inversoes, agora vou ter i-1-x
        // cur - cur2 = 2*x-i
        // (cur - cur2 + i) / 2 = x
        int inv = (cur - cur2 + i) / 2;
        // qtd de caras maiores que eu nesse intervalo
        p[0] = i+1-inv;
        for (int j = 1; j <= i; ++j) if (p[j] >= i+1-inv) p[j]++;
    }
    for (int i = 1; i <= n-1; ++i) {
        int pos = -1;
        for (int j = i-1; j < n; ++j) {
            if (p[j] == i) pos = j;
        }
        assert(pos != -1);
        apply(i-1, pos);
    }
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    if (n == 1) {
        cout << "1 1" << endl;
        int x; cin >> x;
        exit(0);
    }
    vector<int> h(n);
    solve(n, h);
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100);
        vector<int> p(n); iota(all(p), 1); shuffle(all(p), rng);
        cout << n << endl;
        for (auto x : p) cout << x << ' ';
        cout << endl;
        solve(n, p);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
