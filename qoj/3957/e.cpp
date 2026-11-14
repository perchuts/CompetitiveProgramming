#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'
#define double long double

using namespace std;

using ll = long long;

const double sqrt2 = sqrtl(2);

int32_t main() {_
      int t;
      cin >> t;
      while(t--){
            cout << "? " << 0 << " " << 1 << endl;
            cout.flush();
            double x1, x2;
            cin >> x1;
            cout << "? " << 1 << " " << 1 << endl;
            cout.flush();
            cin >> x2;
            double x = x2*sqrt2/2;
            double theta = atan((x1 - x)/x), r = x1*cos(theta), l = 2.0*r;
            cout << "! " << fixed << setprecision(12) << llround(l*l) << endl;
            cout.flush();
      }
}
