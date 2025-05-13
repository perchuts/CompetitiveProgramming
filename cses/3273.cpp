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

int solve(int n, string s){
    vector<char> tipo(n, 'X');
#ifdef gato
    for (int i = 0; i < n; ++i) tipo[i] = s[i];
#endif
    auto ask = [&] (int k) {
        if (tipo[k%n] != 'X') return tipo[k%n];
        cout << "? " << (k%n)+1 << endl;
        cin >> tipo[k%n];
        return tipo[k%n];
    };
    if (ask(0) == ask(1)) return 1;
    ask(n/2);
    int want = (n/2) % 2, l, r;
    if ((tipo[1] == tipo[n/2]) != want) l = 1, r = n/2;
    else l = n/2, r = n;
    while (true) {
        if (r == l+1) {
            assert(ask(l) == ask(r));
            return l+1;
        }
        int md = (l+r)/2;
		int t_esq = md-l+1, cond = (ask(md) == ask(l));
		if (t_esq % 2 != cond) r = md;
		else l = md;
    }
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    string s;
	int ans = solve(n, s);
    cout << "! " << ans << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5) * 2 + 1;
        string s(n, 'R');
        for (auto& x : s) if (rnd(0, 1)) x = 'B';
		cout << n << ' ' << s << endl;
		cout.flush();
        solve(n, s);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
