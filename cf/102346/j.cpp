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
	vector<vector<int>> cards;
	map<char, int> id;
	id['A'] = 0;
	id['2'] = 1;
	id['3'] = 2;
	id['4'] = 3;
	id['5'] = 4;
	id['6'] = 5;
	id['7'] = 6;
	id['8'] = 7;
	id['9'] = 8;
	id['D'] = 9;
	id['Q'] = 10;
	id['J'] = 11;
	id['K'] = 12;
	--k;
	for (int i = 0; i < n; ++i) {
		vector<int> v(14);
		string s; cin >> s;
		for (auto x : s) v[id[x]]++;
		if (i == k) v[13] = 1; 
		cards.push_back(v);
	}
	int act = k, passou = 1;	
	while (true) {
		for (int i = 0; i < n; ++i) {
			int tot = 0, ok = 0;
			for (auto x : cards[i]) {
				if (x == 4) ok = 1;
				tot += x;
			}
			if (ok && tot == 4) {
				cout << i + 1 << endl;
				exit(0);
			}
		}
		int prox = (act+1)%n;
		if (!passou && cards[act][13] == 1) {
			cards[act][13]--, cards[prox][13]++;
			passou = 1;
		} else {
			int mn = 1414;
			for (int i = 0; i < 13; ++i) {
				if (cards[act][i] != 0) ckmin(mn, cards[act][i]);
			}
			bool ok = 0;
			cout.flush();
			for (int i = 0; i < 13; ++i) {
				if (cards[act][i] == mn) {
					cards[act][i]--, cards[prox][i]++;
					passou = 0, ok = 1;
					break;
				}
			}
			assert(ok);
		}
		act = prox;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
