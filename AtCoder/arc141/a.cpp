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
vector<int> manos;
void solve(){
	int n; cin >> n;
	int digits = 0, cur = n;
	vector<int> num;
	while (cur) digits++, num.pb(cur%10), cur /= 10;
	int best = 0;
	if (digits % 2 == 0) {
		reverse(all(num));
		int eu = 0, pot = 1;
		for (int i = 0; i < digits/2; ++i) {
			eu = 10*eu + num[i];
			pot *= 10;
		}
		if ((pot+1) * eu > n) eu--;
		best = (pot+1)*eu;
	} else {
		best = 1;
		for (int i = 0; i < digits-1; ++i) best *= 10;
		best--;
	}
	int id = upper_bound(all(manos), n) - begin(manos) - 1;
	if (id != -1) ckmax(best, manos[id]);
	cout << best << endl;
}

int32_t main(){_
  int t; cin >> t;
  for (int i = 1; i <= 1e6; ++i) {
	  	int cur = i, digits = 0, pot = 1;
		while (cur) digits++, cur /= 10, pot *= 10;
		cur = i;
		int j = 1;
		while (cur < 8e18/pot) {
			cur *= pot, cur += i;
			j++;
			manos.pb(cur);
		}
  }
  sort(all(manos));
  while(t--) solve();
}
