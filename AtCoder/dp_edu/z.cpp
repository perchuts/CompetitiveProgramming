#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int __int128

using namespace std;

using ll = long long;
using ull = unsigned long long;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
#warning cuidado com overflow!
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

void solve(){
    int64_t n, c; cin >> n >> c;
    vector<int64_t> h(n-1);
    CHT cht;
    #warning trocar o sinal
    int64_t y; cin >> y;
    cht.add(y, -y*y);
    int lst = 0;
    for (auto& x : h) {
        cin >> x;
        lst = -x*x - c + cht.get(2*x);
        cht.add(x, lst - x*x);
    }
    int64_t sexo = lst;
    cout << -sexo << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
