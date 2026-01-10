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

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(all(b));
    int ans = 0, j = n-1;
    priority_queue<int> pq;
    for (int i = 1; i < n; ++i) b[i] += b[i-1];
    if (a.back() != m) a.pb(m), n++;
    while (b[j] > m) j--;
    for (int i = n-1; ~i; --i) {
        int k = j;
        while (~k and (i == 0 or a[i-1] <= b[k])) k--;
        k++;
        int pode = j-k;
        while (pode > 0 and !pq.empty()) {
			//cout << "add1 " << pq.top() << endl;
			ans += pq.top(), pq.pop(), pode--;
		}
        if (k <= j) {
            if (pq.empty() or pq.top() <= a[i] - b[k]) {
				//cout << "add2 " << a[i] - b[k] << endl;
                ans += a[i] - b[k];
                if (i and !pq.empty()) {
                    int x = pq.top(); pq.pop();
					//cout << "buff " << x << " -> " << x + b[k]-a[i-1] << endl;
                    pq.push(x + b[k] - a[i-1]);
                }
				if (i and pq.empty()) {
					pq.push(b[k] - a[i-1]);
				}
            } else {
                int x = pq.top(); pq.pop();
				//cout << "add3 " << x << endl;
                ans += x;
                if (i) {
					//cout << "push " << a[i] - a[i-1] << endl;
					pq.push(a[i] - a[i-1]);
				}
            }
        } else if (i) {
			//cout << "push " << a[i] - a[i-1] << endl;
			pq.push(a[i] - a[i-1]);
		}
		//cout << "j = " << j << " => " << " j = " << k-1 << endl;
        j = k-1;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
