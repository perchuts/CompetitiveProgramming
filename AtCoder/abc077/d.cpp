#include <bits/stdc++.h>
//#define gato
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

int solve(int k){
    int cur = k;
    while (cur % 2 == 0) cur /= 2;
    while (cur % 5 == 0) cur /= 5;
    if (cur == 1) {
        return 1;
    }
    vector<int> f(k, 0);
    cur = 1;
    while (!f[cur]) {
        int nxt = cur * 10 % k;
        f[cur] = 1, cur = nxt;
    }
    while (f[cur] == 1) f[cur] = 2, cur = cur * 10 % k;
    for (int i = 1; i < k; ++i) if (f[i] and f[k-i]) {
        return 2;
    }
    for (int i = 0; i < k; ++i) {
        if (f[i] == 0) continue;
        int falta = (k - 2*i) % k;
        falta = (falta + k) % k;
        if (f[falta]) {
            return 3;
        }
    }
    vector<int> pode;
    for (int i = 1; i < k; ++i) if (f[i]) pode.pb(i);
    vector<int> reach = {0}, foi(k, 0);
    for (int step = 1; ; ++step) {
        vector<int> nreach;
        bitset<200010> sexo, novo;
        for (auto x : reach) sexo[x] = 1;
        for (auto x : pode) novo |= (sexo << x);
        for (int i = 0; i < k; ++i) if (!foi[i] and (novo[i] or novo[k+i])) nreach.pb(i), foi[i] = 1;
        if (foi[0]) return step;
        swap(reach, nreach);
    }
}

int32_t main(){_
#ifndef gato
    int k; cin >> k;
    cout << solve(k) << endl;
#else
    for (int i = 1; i <= 100000; ++i) {
        cout << i << endl;
        solve(i);
    }
#endif
}

