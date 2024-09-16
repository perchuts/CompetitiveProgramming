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

void solve(){
	int n; cin >> n;
	string s; cin >> s;
	// posso cortar nos R`s
	multiset<int> ss;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'R') {
			int cntA = 0, cntC = 0;
			while (cntA < i && s[i-cntA-1] == 'A') cntA++;
			while (i+cntC+1<n && s[i+cntC+1] == 'C') cntC++;
			if (min(cntA, cntC) != 0) ss.insert(min(cntA, cntC));
		}
	}
	int ans = 0;
	for (; !ss.empty(); ++ans) {
		if (ans%2==0) {
			auto x = *prev(end(ss));
			ss.erase(ss.find(x));
			if (x!=1) ss.insert(x-1);
		} else {
			auto x = begin(ss);
			ss.erase(ss.find((*x)));
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
