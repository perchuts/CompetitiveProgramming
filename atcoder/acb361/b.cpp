#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

void solve(){
	vector<int> cubo(6), cubo2(6);
	for (auto& x : cubo) cin >> x;
	for (auto& x : cubo2) cin >> x;
	for (int i = cubo[0]; i < cubo[3]; ++i) {
		for (int j = cubo[1]; j < cubo[4]; ++j) {
			for (int k = cubo[2]; k < cubo[5]; ++k) {
				if (cubo2[0] <= i && i < cubo2[3] && cubo2[1] <= j && j < cubo2[4] && cubo2[2] <= k && k < cubo2[5]) {
					cout << "Yes" << endl;
					exit(0);
				}
			}
		}
	}	
	cout << "No" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
