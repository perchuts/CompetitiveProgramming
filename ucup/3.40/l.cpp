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

void solve(vector<int> c, vector<int> d, int v) {

		if(c.size() == 0) return;
		int w = c[0];
		vector<int> d2(d.size());
		for(int u=1;u<c.size();u++){
			int wt = perg(w, c[u]);
			d2[u] = wt;
		}

		int dvw = perg(v, w);
		vector<int> path;
		for(int u=1;u<c.size();u++){
			if(d2[u] + d[u] = dvw) path.push_back(u);
		}
		sort(path.begin(), path.end(), [&](int k, int l) { return d[k] < d[l]; }
		if(path.size() == 0){
			cospe(v, w, dvw);
		}
		else{
			cospe(v, c[path[0]], d[path[0]]);
			for(int i=1;i<path.size();i++){
				cospe(c[path[i]], c[path[i-1]], d[path[i]] - d[path[i-1]]);
			}
			cospe(w, c[path.back()], d2[path.back()]);
		}

	
		solve(c, d, v);
}

int32_t main() {_
	int t; cin >> t;
	while(t--){

		int n; cin >> n;
		int v = 1;
		vector<int> c, d;
		for(int u=2;u<=n;u++){
			int w = perg(u, v);
			c.push_back(u);
			d.push_back(v);
		}
		cout << "! ";
		solve(c, d, v);
		cout << endl;
	}
}
