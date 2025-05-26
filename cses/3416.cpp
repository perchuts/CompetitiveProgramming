#include <bits/stdc++.h>
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

template<class T> struct minstack {
	pair<T, T> s[500];
    int S = -1;
	void push(T x) {
		if (S == -1) s[++S] = {x, x};
		else S++, s[S] = {x, (s[S-1].second|x)};
	}
	T top() { return s[S].first; }
	T pop() {
		T ans = s[S--].first;
		return ans;
	}
	int size() { return S+1; }
	T min() { return s[S].second; }
};
 
template<class T> struct minqueue {
	minstack<T> s1, s2;
	void push(T x) { s1.push(x); }
	void move() {
		if (s2.size()) return;
		while (s1.size()) {
			T x = s1.pop();
			s2.push(x);
		}
	}
	T front() { return move(), s2.top(); }
	T pop() { return move(), s2.pop(); }
	inline int size() { return s1.size()+s2.size(); }
	T min() {
		if (!s1.size()) return s2.min();
		else if (!s2.size()) return s1.min();
		return (s1.min()|s2.min());
	}
};

int sp[500][500][9];
int temp[500][9];

void solve(){
    int n, X; cin >> n >> X;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    int want = (1 << X) - 1;
    ll ans = 0;
    vector<int> lg(501);
    for (int i = 2; i <= 500; ++i) lg[i] = lg[i/2]+1;
    for (int i = 0; i < n; ++i) {
        for (int j = n-1; ~j; --j) {
            int eu = grid[i][j] - 'A';
            sp[i][j][0] = (1 << eu);
            for (int k = 1, x = 1; j + 2 * x <= n; x += x, ++k) sp[i][j][k] = sp[i][j][k-1] | sp[i][j+x][k-1];
        }
    }
    int tam, k;
    auto query = [&] (int i, int l, int r) {
        return sp[i][l][k] | sp[i][r-(1<<k)+1][k];
    };
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            minqueue<int> mq;
            int s = 0;
            tam = r-l+1, k = lg[tam];
            for (int i = 0; i < n; ++i) {
                int eu = query(i, l, r);
                s++;
                mq.push(eu);
                while (s and mq.min() == want) mq.pop(), s--;
                ans += i+1-s;
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
