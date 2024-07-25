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

int basis[30], tam = 0;

int add(int x) {
	for (int i = 0; i < 30; ++i) {
		if ((x >> i) & 1) x ^= basis[i];
		if (x == 0) return 0;
	}
	tam++;
	for (int i = 0; i < 30; ++i) {
		if ((x >> i) & 1) {
			basis[i] = x;
			return 1;
		}
	}
	assert(false);
}	

void solve(){
  	add('0'), add('1'), add(']'), add('['), add('='), add('*');
	add('1');
	for (int i = '1'; ; ++i) {
		add(i);
		if (tam == 7) {
			cout << char(i) << endl;
			break;
		}
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
