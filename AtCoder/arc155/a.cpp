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
 	int n, k; cin >> n >> k;
	string s; cin >> s;
	if (k >= 2 * n) {
		int espaco = k % (2*n);
		int rodadas = k / (2*n);
		string la_dentro(espaco+2*n, '-');
		string sr = s; reverse(all(sr));
		if (rodadas % 2 == 0) swap(s, sr);
		for (int i = 0; i < n; ++i) la_dentro[i] = la_dentro[espaco+n+i] = sr[i];
		bool ok = 1;
		for (int i = 0; i < n; ++i) {
			if (la_dentro[n+i] == '-') la_dentro[n+i] = s[i];
			else ok &= (la_dentro[n+i] == s[i]); 
		}
		for (int i = 0; i < n; ++i) {
			if (la_dentro[espaco+i] == '-') la_dentro[espaco+i] = s[i];
			else ok &= (la_dentro[espaco+i] == s[i]);
		}	
		string s1, s2;
		for (int i = 0; i < espaco+n; ++i) s1 += la_dentro[i];
		for (int i = 0; i < espaco+n; ++i) s2 += la_dentro[n+i];
		string s3 = s1, s4 = s2;
		reverse(all(s3)), reverse(all(s4));
		ok = ((s1 == s3) && (s2 == s4));
		cout << (ok ? "Yes" : "No") << endl;
	}
	else {
		string ss(k, '-');
		for (int i = 0; i < min(n, k); ++i) ss[k-1-i] = s[i];
		bool ok = 1;
		for (int i = 0; i < min(n, k); ++i) {
			if (ss[i] == '-') ss[i] = s[n-1-i];
			else ok &= (ss[i] == s[n-1-i]);
		}
		string a = s + ss, b = ss + s, a2 = a, b2 = b;
		reverse(all(a2)), reverse(all(b2));
		ok &= (a == a2 && b == b2);
		cout << (ok ? "Yes" : "No") << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
