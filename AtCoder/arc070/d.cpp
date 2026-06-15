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

mt19937 rng(67);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
string S;
string solve(int A, int B) {
    if (A <= B) return "Impossible";
    int N = A + B;
    vector<int> ans(N);
    auto ask = [&] (int i, int j) {
        #ifndef gato
        cout << "? " << i << " " << j << endl;
        char c; cin >> c;
        return (c == 'Y');
        #else
        cout << "Asking: " << i << " " << j << endl;
        cout << "Ans: ";
        if (S[i] == '1') {
            cout << (S[j] == '1' ? 'Y' : 'N') << endl;
            return (S[j] == '1');
        }
        bool res = (rnd(0, 1) == 1);
        cout << (res ? 'Y' : 'N') << endl;
        return res;
        #endif
    };
    int cnt = 1, repr = 0;
    for (int i = 1; i < N; ++i) {
        int z = ask(repr, i);
        if (z == 1) cnt++, repr = i;
        else cnt--;
        if (cnt == 0) {
            repr = i, cnt = 1;
        }
    }
    string s(N, '0');
    s[repr] = '1';
    for (int i = 0; i < N; ++i) {
        if (i != repr) s[i] = char('0' + ask(repr, i));
    }
    return s;
}

int32_t main() {_
#ifndef gato
    int A, B; cin >> A >> B;
    string s = solve(A, B);
    if (s[0] != 'I') cout << "! ";
    cout << s << endl;
#else
    int t = 1;
    while (true) {
        int A = rnd(2, 8), B = rnd(1, A-1);
        S.resize(A+B);
        for (int i = 0; i < A+B; ++i) S[i] = char('0'+(i < A));
        shuffle(all(S), rng);
        auto my = solve(A, B);
        if (my != S) {
            cout << "Wrong answer on test " << t << endl;
            cout << A << " " << B << endl;
            cout << "Hidden string: " << S << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
