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

void solve(){

	int n, k; cin >> n >> k;
	vector<int> c(n);
	for(auto& x : c) cin >> x;
	if(k <= n-1){
		int mx = -inf, sm = 0;
		for(int i=0;i<k+1;i++) mx = max(mx, c[i]), sm += c[i];
		cout << sm - mx << endl;
		return;
	}
	int mx = -inf, mx2 = inf, sm = 0, im = 0, im2 = 0;
	for(int i=0;i<n;i++){
		if(c[i] >= mx){
			//im2 = im;
			im = i;
			//mx2 = mx;
			mx = c[i];
		}
		//else if(c[i] > mx2){
		//	im2 = i;
		//	mx2 = c[i];
		//}
		sm += c[i];
	}

	int tot = (sm - mx) * (k / (n-1));
	mx = -inf, sm = 0;
	for(int i=0;i<k%(n-1)+1;i++) mx = max(mx, c[i]), sm += c[i];

	//for(int i=0, j=0;i<k%(n-1);j++){
	//	if(j == im || j == im2){
	//		continue;
	//	}
	//	i++;
	//	tot += c[j];
	//}
	cout << tot+sm-mx << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
