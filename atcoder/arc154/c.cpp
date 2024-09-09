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

void solve(int t){
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(auto& x : a) cin >> x, --x;
    for(auto& x : b) cin >> x, --x;  
    if (a == b) {
        cout << "Yes" << endl;
        return;
    }
	int cc = 0;
	for (int i = 0; i < n; ++i) cc += (b[i] != b[(i+1)%n]);
	if (cc == n) {
		cout << "No" << endl;
		return;
	}
    vector<int> a2(n), b2(n);
    for (int st = 0; st < n; ++st) {
       for (int i = 0; i < n; ++i) b2[i] = b[(i+st)%n], a2[i] = a[i];
       vector<vector<int>> freqs(n);
       for (int i = n-1; i >= 0; --i) freqs[a2[i]].pb(i);
       int use = -1, ok = 1;
       for (int i = 0; i < n; ++i) {
           while (!freqs[b2[i]].empty() && freqs[b2[i]].back() < use) freqs[b2[i]].pop_back();
           if (freqs[b2[i]].empty()) {
               ok = 0;
               break;
           }
           use = freqs[b2[i]].back();
       }
       if (ok) {
           cout << "Yes" << endl;
           return;
       }

    }
    cout << "No" << endl;
}

int32_t main(){_
  int t; cin >> t;
  for (int i = 1; i <= t; ++i) solve(i);
}

