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
	string s; cin >> s;
	int n = sz(s);
	vector<int> p(n), freq(26), foi(26);
	for (int i = 1; i < n; ++i) freq[p[i]-'a']++;
	for (int i = 1; i < 26; ++i) freq[i] += freq[i-1];
	string s2 = s.substr(1, n-1);
	sort(all(s2));
	int x;
	for (int i = 0; i < n; ++i) {
		// quero ver quem vai chegar nessa aresta!
		char c = s[i];
		if (c == '#') {
			p[0] = i;
			x = i;
			continue;
		}
		int st = 1 + (c == 'a' ? 0 : freq[c-'a'-1]);
		p[st + foi[c-'a']] = i;
		foi[c-'a']++;
	}
	for (int i = 0; i < n; ++i, x = p[x]) cout << s2[x-1];
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
