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
	vector<int> freq(26);
	for (auto x : s) freq[x-'a']++;
	vector<int> id(26);
	iota(all(id), 0);
	sort(all(id), [&] (int a, int b) { return freq[a] > freq[b]; });
	string ans(n, 'a');
	int ptr = 0;
	for (auto x : id) {
		for (int j = 0; j < freq[x]; ++j) {
			if (ptr < (n+1)/2) ans[2 * ptr] = char(x + 'a');
			else ans[1 + 2*(ptr-(n+1)/2)] = char(x+'a');
			ptr++;
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
