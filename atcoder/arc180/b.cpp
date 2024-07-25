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
int foi[505][505], cnt[505];
void solve(){
	int n, k; cin >> n >> k;
	vector<int> p(n);
	for (auto& x : p) cin >> x, --x;
	vector<ii> ans;
	vector<int> pos(n);
	for (int i = 0; i < n; ++i) pos[p[i]] = i;
	for (int i = 0; i < n; ++i) {
		for (int j = i + k; j < n; ++j) {
			if (p[i] > p[j]) cnt[p[i]-p[j]]++;
		}
	}
	while (true) {
		cout.flush();
		ii good = {-1, -1};
		int tam = 0;
		for (; tam < n; ++tam) if (cnt[tam]) break;
		if (tam == n) break;
		for (int i = 0; i + tam < n; ++i) {
			int pi = pos[i+tam], pj = pos[i];
			if (pi+k <= pj && !foi[pi][pj]) {
				good = {pi, pj}; break;
			}
		}
		auto [pi, pj] = good;
		assert(pi != -1);
		foi[pi][pj] = 1;
		for (int j = 0; j < 2; ++j) {
			for (int i = 0; i < n; ++i) {
				if (abs(pi-i) >= k && !foi[min(pi, i)][max(pi, i)]) {
					if ((i<pi&&p[i]>p[pi])||(i>pi&&p[pi]>p[i])) cnt[max(p[pi],p[i])-min(p[i],p[pi])]--;
				}
			}
			swap(pi, pj);
		}
		cnt[tam]--, swap(p[pi], p[pj]), swap(pos[p[pi]], pos[p[pj]]), ans.pb({pi, pj});
		for (int j = 0; j < 2; ++j) {
			for (int i = 0; i < n; ++i) {
				if (abs(pi-i) >= k && !foi[min(pi, i)][max(pi, i)]) {
					if ((i<pi&&p[i]>p[pi])||(i>pi&&p[pi]>p[i])) cnt[max(p[pi],p[i])-min(p[i],p[pi])]++;
				}
			}
			swap(pi, pj);
		}
	}
	cout << sz(ans) << endl;
	for (auto [x, y] : ans) cout << x + 1 << " " << y + 1 << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
