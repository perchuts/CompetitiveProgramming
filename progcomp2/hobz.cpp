#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int v[maxn][2], basis[30][30], tmp[maxn];

void add(int x, int j) {
      for (int i = 0; i < 30; ++i) {
            if ((x >> i) & 1) {
                  if (!basis[j][i]) {
                        basis[j][i] = x;
                        return;
                  }
                  x ^= basis[j][i];
            }     
      }
}

bool check(int x, int j) {
      for (int i = 0; i < 30; ++i) {
            if ((x >> i) & 1) {
                  if (!basis[j][i]) {
                        return false;
                  }
                  x ^= basis[j][i];
            }     
      }
      return true;
}


bool on(int x, int j) {
      return ((x >> j) & 1);
}

int solve(int n, int k, vector<int> a, vector<int> b){


    for (int j = 0; j < 2; ++j) for (int i = 1; i <= n; ++i) v[i][0] = a[i-1], v[i][1] = b[i-1];

    int initial = 0;
    for (int i = 1; i <= n; ++i) initial ^= v[i][0];
    int ans = (initial <= k ? initial : 0), cur = initial ^ k;


    for (int i = 0; i < 30; ++i) {// considering a prefix of this number
        for (int j = 1; j <= n; ++j) { 
            int act = v[j][0] ^ v[j][1];
            if (on(act, 29 - i)) tmp[j] += (1<<(29-i));
            add(tmp[j], i);
        }
    }

    if (check(cur, 29)) ans = k;

    for (int i = 29; i >= 0; --i) {
        if (on(k, 29 - i)) {
            int tmp = cur ^ (1 << (29 - i));
            if (check(tmp, i)) {
                for (int j = i + 1; j < 30; ++j) {
                    if ((initial >>(29-j))&1) {
                        if (check(tmp, j)) {}
                        else {
                            tmp += (1<<(29 - j));
                            assert(check(tmp, j));
                        }
                    } else {
                        if (check(tmp + (1<<(29 - j)), j)) tmp += (1<<(29 - j));
                        else assert(check(tmp, j));
                    }
                }
                ckmax(ans, initial ^ tmp);
                break;
            }
        }
        if (on(cur, 29 - i)) cur -= (1 << (29 - i));
    }


    for (int i = 0; i < 30; ++i) for (int j = 0; j < 30; ++j) basis[i][j] = 0;
    for (int i = 1; i <= n; ++i) v[i][0] = v[i][1] = tmp[i] = 0;
    return ans;
}

int bira(int n, int k, vector<int> a, vector<int> b) {
        ll ans = 0;
        for(auto ai: a)ans ^= ai;
        int B[666];
        int bt = 0;
        for(int j = 0; j < n; ++j){
        int bj = b[j];
            bj ^= a[j];
            for (int i = 0; i < bt; i++) bj = min(bj, bj^B[i]);
            if (bj){
                for (int i = 0; i < bt; i++) B[i] = min(B[i], bj^B[i]);
                B[bt++] = bj;
                ans = min(ans, bj^ans);
            }
        }
        sort(begin(B), begin(B)+bt);
        for (int i = bt-1; i >= 0; i--){
            if((ans^B[i]) <= k){
                ans = ans^B[i];
            }
        }
       if(ans > k){
                ans = 0;
            }
    return ans;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int32_t main(){_
    int t = 0;
    while (true) {
        int n = rnd(1, 100), k = rnd(0, (1<<30)-1);
        vector<int> a(n), b(n);
        for (auto& x : a) x = rnd(0, (1<<30)-1);
        for (auto& x : b) x = rnd(0, (1<<30)-1);
        auto ans = solve(n, k, a, b);
        auto my = bira(n, k, a, b);
        if (ans != my) {
            cout << n << ' ' << k << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            for (auto x : b) cout << x << ' ';
            cout << endl;
            cout << "Bira output: " << my << endl;
            cout << "Correct answer: " << ans << endl;
            exit(0);
        }
        cout << "AC " << t++ << endl;
    }
}
