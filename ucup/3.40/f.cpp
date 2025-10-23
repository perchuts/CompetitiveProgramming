#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()             
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll                                
//#define gato
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

vector<string> solve(vector<int> p) {
    const int n = 10;
    int N = sz(p);
    vector<string> ans;
    int pos_1;
    for (int i = 0; i < N; ++i)
        if (p[i] == 1) pos_1 = i;
    auto pp = p;        
    auto add = [&] (int x, int y, string sign) {
        assert(abs(x-y)==1);
        string z;
        z += to_string(x+1);
        z += " ";
        z += sign;
        z += " ";
        z += to_string(y+1);
        if (sign == "+") pp[x] += pp[y];
        else pp[x] -= pp[y];
		//cout << "trying to push " << z << endl;
		//cout << pp[x] << ' ' << pp[y] << endl;
        //cout << flush;
        assert(max(pp[x], pp[y]) <= N);
        assert(min(pp[x], pp[y]) >= 1);
		//for (int i = max(0LL, min(x, y)-5); i <= min(N-1, max(x,y)+5); ++i) cout << pp[i] << ' ';
		//cout << endl << flush;
        ans.pb(z);
    };
    auto finish = [&] () {
        for (int i = 1; i < N; ++i)
            add(i, i-1, "+");
    };
    if (N <= 2200) {
        // fazer tudo na maozinha
        for (int j = pos_1-1; j >= 0; --j) {
            for (int k = 0; k < p[j]-1; ++k) add(j, j+1, "-");

        }
        for (int j = pos_1+1; j < N; ++j) {
            for (int k = 0; k < p[j]-1; ++k) add(j, j-1, "-");

        }
        finish();
        return ans;
    }
    int cn = 0, atv = 0;
    for (int i = pos_1+1; i < N; ++i) {
        if (cn < n) {
            cn++;
            while (pp[i] != 1) add(i, i-1, "-");
            if (cn == n) {
                atv = 1;
                for (int j = pos_1+1; j <= i; ++j) add(j, j-1, "+"), add(j, j-1, "+");
                for (int j = i; j > pos_1; --j) add(j, j-1, "-");
            }
            continue;
        }
        for (int j = i; j >= i-n; --j) {
            int target = (1 << (n-(i-j)));
            while (pp[j] > target) add(j, j-1, "-");
            if (pp[j] == target) {
                // fiz o W
                for (int k = j-1; k >= i-n; --k) add(k, k-1, "-");
                break;
            }
            add(j-1, j, "-");
            add(j, j-1, "+");
        }
    }
    if (atv) {
        for (int i = N-2; i >= N-cn-1; --i) for (int j = i; j < N-1; ++j) add(j+1, j, "-");
    }
    cn = atv = 0;
    for (int i = pos_1-1; i >= 0; --i) {
        if (cn < n) {
            cn++;
            while (pp[i] != 1) add(i, i+1, "-");
            if (cn == n) {
                atv = 1;
                for (int j = pos_1-1; j >= i; --j) add(j, j+1, "+"), add(j, j+1, "+");
                for (int j = i; j < pos_1; ++j) add(j, j+1, "-");
            }
            continue;
        }
        for (int j = i; j <= i+n; ++j) {
            int target = (1 << (n-(j-i)));
            while (pp[j] > target) add(j, j+1, "-");
            if (pp[j] == target) {
                // fiz o W
                for (int k = j+1; k <= i+n; ++k) add(k, k+1, "-");
                break;
            }
            add(j+1, j, "-");
            add(j, j+1, "+");
        }
    }
    if (atv) {
        for (int i = 1; i <= cn; ++i) for (int j = i; j; --j) add(j-1, j, "-");
    }
	//cout << "inicio: ";
	//for (int i = 0; i < 20; ++i) cout << pp[i] << ' ';
	//cout << endl;
	//cout << "fim: ";
	//for (int i = 0; i < 20; ++i) cout << pp[N-20+i] << ' ';
	//cout << endl;
    finish();
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    auto ans = solve(p);
    cout << sz(ans) << endl;
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
		int n = 30000;
        vector<int> p(n); iota(all(p), 1); shuffle(all(p), rng);
        //cout << n << endl;
        //for (auto x : p) cout << x << ' ';
        //cout << endl;
        //cout << flush;
        auto my = solve(p);
        cout << "Accepted on test " << t++ << endl << " - " << (2.5e6/sz(my)) << endl << flush;
    }
#endif
}
