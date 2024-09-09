#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

int32_t main() {
  fast_io;
  int t; cin >> t;
  while (t--) {
     int a, b, c; cin >> a >> b >> c;
     int ranran = 1, ans = 9e18;
     for (int i = 0; ranran <= c; ++i, ranran += ranran) {
        int l = 0, r = ranran-1, best = 0;
        auto calc = [&] (int k) {
            if (k < 0 || k > ranran) return ans;
            if (k == 0) return a * i + (c+ranran-1)/(ranran) * b;
            int tempo = a * i + a, antes_copia = (ranran-k) * (a/b), falta = c - antes_copia;
            if (falta < 0) return tempo;
            int t2 = (b-(a%b))%b;
            tempo += falta/(ranran+k) * b;
            falta %= (ranran+k);
            if (falta <= 2*k) return tempo;
            return tempo + t2;
        };
        ans = min(ans, calc(0));
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (calc(md) >= calc(md+1)) best = md, l = md + 1;
            else r = md-1;
        }
        for (int j = -2; j <= 2; ++j) ans = min(ans, calc(best+j));
     }
     cout << ans << endl;
  }

}

