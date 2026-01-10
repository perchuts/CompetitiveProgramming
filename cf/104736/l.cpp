#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

int solve(string s) {
    int n = sz(s);
    for (auto& x : s) {
        if (x == ')' or x == '(') {}
        else if ('a' <= x and x <= 'z') x = 'a';
        else x = '+';
    }
    int ans = 0;
    for (auto x : s) ans += (x == 'a');
    vector<int> dp(n+1), match(n, -1);
    vector<int> helper(3*n+1);
    int p = 0;
    auto solve = [&] (auto&& self, int l, int r) -> void {
        if (l >= r) return;
        int md = (l+r)/2;
        // (-1) (-2) (-1)
        // dois tipos de expressao: veio A, veio )
        p = 0;
        for (int i = l; i <= r; ++i) {
            if (s[i] == 'a') {
                if (p==0) helper[p++]=-1;
                else if (helper[p-1] == -2) {
                    p--;
                    assert(helper[p-1] == -1 or helper[p-1] == -3);
                    p--;
                    helper[p++]=-1;
                } else if (helper[p-1] == -3) {
                    while (!(p==0)) p--;
                    helper[p++]=-1;
                } else if (helper[p-1] != -1) helper[p++]=-1;
            } else if (s[i] == '(') {
                if (!(p==0) and (helper[p-1] == -1 or helper[p-1] == -3)) while (!(p==0)) p--;
                helper[p++] = i;
            } else if (s[i] == '+') {
                if (!(p==0) and (helper[p-1] != -1 and helper[p-1] != -3)) while (!(p==0)) p--;
                if (!(p==0) and (helper[p-1] == -1 or helper[p-1] == -3)) helper[p++]=-2;
            } else {
                if (p==0) {}
                else if (helper[p-1] != -1 and helper[p-1] != -3) {
                    while (!(p==0)) p--;
                }
                else {
                    p--;
                    if (!(p==0)) {
                        assert(helper[p-1] != -2);
                        if (helper[p-1] == -1 or helper[p-1] == -3) {
                            while (!(p==0)) p--;
                        } else {
                            match[helper[p-1]] = i;
                            p--;
                            if (!(p==0) and helper[p-1] == -2) {
                                p--;
                                assert(helper[p-1] == -1 or helper[p-1] == -3);
                                p--;
                                helper[p++]=-3;
                            }
                            else helper[p++]=-3;
                        }
                    }
                }
            }
        }
        int limR = md;
        while (limR < r and (s[limR+1] != '(' or match[limR+1] != -1)) limR++;
        if (limR > md) {
            dp[limR] = (s[limR] == 'a');
            for (int i = limR-1; i > md; --i) {
                if (s[i] == 'a') {
                    if (s[i+1] == 'a') dp[i] = dp[i+1];
                    else if (s[i+1] == '+') dp[i] = dp[i+2];
                    dp[i]++;
                }
                if (s[i] == '(') {
                    dp[i] = 1 + (match[i] < r and s[match[i]+1] == '+' ? dp[match[i]+2] : 0);
                }
            }
            for (int i = md; i >= l; --i) {
                if (s[i] == 'a') {
                    if (s[i+1] == 'a') dp[i] = dp[i+1];
                    else if (s[i+1] == '+') dp[i] = dp[i+2];
                } 
                if (s[i] == '(') {
                    if (match[i] == -1) break;
                    if (match[i] == r) dp[i]++;
                    else {
                        if (s[match[i]+1] == '+') dp[i] = dp[match[i]+2]+(match[i] > md);
                        else dp[i] = (match[i] > md);
                    }
                }
                ans += dp[i];
            }
        }
        //cout << l << ' ' << r<< endl;
        //for (int i = l; i <= r; ++i) cout << s[i];
        //cout << endl;
        //for (int i = l; i <= r; ++i) cout << match[i] << ' ';
        //cout << endl;
        //for (int i = l; i <= r; ++i) cout << dp[i] << " |"[i==md];
        //cout << endl;
        for (int i = l; i <= r; ++i) match[i] = -1, dp[i] = 0;
        self(self, l, md), self(self, md+1, r);
    };
    solve(solve, 0, n-1);
    return ans;
}

int brute(string s) {
    for (auto& x : s) {
        if (x == ')' or x == '(') {}
        else if ('a' <= x and x <= 'z') x = 'a';
        else x = '+';
    }
    int n = sz(s);
    vector<vector<int>> dp(n+4, vector<int>(n+4));
    int ans = 0;
    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            if (l == r) {
                dp[l][r] = (s[l-1] == 'a');
                ans += dp[l][r];
                continue;
            }
            if (s[l-1] == 'a') {
                if (s[l] == '+') dp[l][r] = dp[l+2][r];
                else if (s[l] == 'a') dp[l][r] = dp[l+1][r];
                ans += dp[l][r];
                continue;
            }
            for (int k = l+1; k < r; ++k) {
                if (s[k-1] == '+' and dp[l][k-1] and dp[k+1][r]) dp[l][r] = 1;
            }
            if (s[l-1] == '(' and s[r-1] == ')' and dp[l+1][r-1]) dp[l][r] = 1;
            ans += dp[l][r];
        }
    }
    //for (int l = 1; l <= n; ++l) {
    //    for (int r = 1; r <= n; ++r) {
    //        if (dp[l][r]) {
    //            for (int k = l; k <= r; ++k) cout << s[k-1];
    //            cout << endl;
    //        }
    //    }
    //}
    return ans;
}
int32_t main() {_
#ifndef gato
    string s; cin >> s;
    //cout << brute(s) << endl;
    cout << solve(s) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 16);
        string s(n, 'a');
        for (auto& x : s) {
            int r = rnd(1, 20);
            if (r <= 6) x = 'a';
            else if (r <= 10) x = '(';
            else if (r <= 14) x = ')';
            else x = '+';
        }
        int my = solve(s), ans = brute(s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << s << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
