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
// Convex Hull Trick Estatico
//
// adds tem que serem feitos em ordem de slope
// queries tem que ser feitas em ordem de x
//
// add O(1) amortizado, get O(1) amortizado

struct CHT {
	int it;
	vector<ll> a, b;
	CHT():it(0){}
	ll eval(int i, ll x){
		return a[i]*x + b[i];
	}
	bool useless(){
		int sz = a.size();
		int r = sz-1, m = sz-2, l = sz-3;
		return (b[l] - b[r])*(a[m] - a[l]) <
			(b[l] - b[m])*(a[r] - a[l]);
	}
	void add(ll A, ll B){
		a.push_back(A); b.push_back(B);
		while (!a.empty()){
			if ((a.size() < 3) || !useless()) break;
			a.erase(a.end() - 2);
			b.erase(b.end() - 2);
		}
		it = min(it, int(a.size()) - 1);
	}
	ll get(ll x){
		while (it+1 < a.size()){
			if (eval(it+1, x) > eval(it, x)) it++;
			else break;
		}
		return eval(it, x);
	}
};
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n), ord(n); iota(all(ord), 0);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    sort(all(ord), [&] (int x, int y) {
        if (a[x] == a[y]) return b[x] > b[y];
        return a[x] > a[y];
    });
    vector<int> bichos = {ord[0]};
    for (auto i : ord) {
        if (b[i] > b[bichos.back()]) bichos.pb(i);
    }
    CHT sexo;
    vector<int> opt(sz(bichos));
    opt[0] = a[bichos[0]] * b[bichos[0]];
    sexo.add(-a[bichos[0]], 0);
    for (int i = 1; i < sz(bichos); ++i) {
        int k = bichos[i];
        opt[i] = -sexo.get(b[k]);
        ckmin(opt[i], opt[i-1] + a[k] * b[k]);
        sexo.add(-a[k], -opt[i-1]);
    }
    cout << opt[sz(bichos)-1] << endl; 
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
