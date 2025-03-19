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
int meb[maxn];

void crivo(int lim) {
	for (int i = 2; i <= lim; i++) meb[i] = 2;
	meb[1] = 1;
	for (int i = 2; i <= lim; i++) if (meb[i] == 2)
		for (int j = i; j <= lim; j += i) if (meb[j]) {
			if (meb[j] == 2) meb[j] = 1;
			meb[j] *= j/i%i ? -1 : 0;
		}
}
void solve(){
    int n; cin >> n;
    vector<int> p(n+1), f(n+1);
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i) { 
        int cnt = 0;
        for (int j = i; j <= n; j += i) if (p[j] % i == 0) cnt++;
        f[i] = cnt * (cnt + 1) / 2;
    }
    crivo(200500);
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 2*i; j <= n; j += i) f[i] += f[j] * meb[j/i];
        ans += f[i];
        cout << f[i] << ' ';
    }
    cout << endl;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
