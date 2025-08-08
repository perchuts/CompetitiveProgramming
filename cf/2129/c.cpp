#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
string hidden;
int calc(string s) {
    int n = sz(s);
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int bal = 0, ok = 1;
            for (int k = i; k <= j; ++k) {
                bal += (s[k] == ')' ? -1 : 1);
                if (bal == -1) ok = 0;
            }
            ok &= (bal == 0);
            tot += ok;
        }
    }
    return tot;
}
int ask(vector<int> ind) {
#ifndef gato
	cout << "? ";
	cout << sz(ind) << ' ';
	for (auto x : ind) cout << x + 1 << ' ';
	cout << endl;
	int y; cin >> y;
	return y;
#else
    string sexo;
    for (auto i : ind) sexo += hidden[i];
    return calc(sexo);
#endif
}
string solve(int n) {
	int l = 0, r = n-1, best = n;
	int pf = -1, pa = -1;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		vector<int> sexo;
		for (int i = 0; i <= md; ++i) sexo.pb(i);
		int x = ask(sexo);
		if (x) best = md, r = md-1;
		else l = md+1;
	}
	if (best != n) pf = best, pa = pf-1;
	else {
		l = 0, r = n-1, best = -1;	
		while (l <= r) {
			int md = l + (r-l+1)/2;
			vector<int> sexo;
			for (int i = n-1; i >= md; --i) sexo.pb(i);
			int x = ask(sexo);
			if (x) best = md, l = md+1;
			else r = md-1;
		}
		pf = best, pa = best+1;
	}
	string ans(n, '*');
	vector<int> uepa = {1, 2, 3, 5, 7, 10, 15, 21, 30, 43, 61, 87, 123};
    for (int i = 0; i < n; i += 13) {
        vector<int> inds;
        for (int j = 0; j < 13; ++j) inds.pb((i+j)%n);
        vector<int> sexo;
        for (int j = 0; j < 13; ++j) {
            if (j) sexo.pb(pf);
            for (int w = 0; w < uepa[j]; ++w) sexo.pb(inds[j]), sexo.pb(pf);
        }
        int cnt = ask(sexo);
        for (int j = 12; ~j; --j) {
			int eu = uepa[j] * (uepa[j]+1) / 2;
            if (eu <= cnt) ans[inds[j]] = '(', cnt -= eu;
            else ans[inds[j]] = ')';
        }
    }
    return ans;
}

int32_t main() {_
    //int tot = 0, sum = 0, cnt = 0;
    //vector<int> caras;
    //for (int i = 1; cnt <= 12; ++i) {
    //    int eu = i * (i+1) / 2;
    //    if (eu <= tot) continue;
    //    tot += eu, sum += 2 * i + 1;
    //    caras.pb(i);
    //    cnt++;
    //}
    //for (auto x : caras) cout << x << ' ';
    //cout << endl;
    //cout << sum << endl;
    //exit(0);
    //int x = 6;
    //for (int i = 0; i < (1 << x); ++i) {
    //    for (int p1 = 0; p1 < x+2; ++p1) {
    //        for (int p2 = p1+1; p2 < x+2; ++p2) {
    //            for (int p3
    //            string ss;
    //            int cara = 0;
    //            for (int j = 0; j < x+2; ++j) {
    //                if (j == p1) ss += 'A';
    //                else if (j == p2) ss += 'B';
    //                else ss += (((i>>cara)&1) ? '(' : ')'), cara++;
    //            }
    //            vector<int> vals;
    //            vector<tuple<char, char, int>> sexo;
    //            for (auto v1 : {'(', ')'}) {
    //                for (auto v2 : {'(', ')'}) {
    //                    string sexoo = ss;
    //                    sexoo[p1] = v1;
    //                    sexoo[p2] = v2;
    //                    int tot = calc(sexoo);
    //                    sexo.pb({v1, v2, tot});
    //                    vals.pb(tot);
    //                }
    //            }
    //            sort(all(vals));
    //            vals.erase(unique(all(vals)), end(vals));
    //            if (sz(vals) == 4) {
    //                cout << ss << endl;
    //                for (auto [x, y, z] : sexo) {
    //                    cout << x << ' ' << y << ' ' << z << endl;
    //                }
    //                exit(0);
    //            }
    //        }
    //    }
    //}
    //cout << "Fez o L" << endl;
    //exit(0);
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        string ans = solve(n);
        cout << "! " << ans << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 30);
        string s(n, ')');
        int cnt = 0;
        for (auto& x : s) {
            int k = rnd(0, 1);
            if (k == 0) x = '(', cnt++;
        }
        if (cnt == 0 or cnt == n) continue;
        hidden = s;
		cout << hidden << endl;
        auto guess = solve(n);
        if (guess != hidden) {
            cout << "Wrong answer on test " << t << endl;
            cout << hidden << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
