#include <bits/stdc++.h>
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

ll coef(vector<ll>v){
    ll ans = 0;
    for(ll i=0;i<sz(v);++i){
        ans += v[i]*(i+1ll);
    }
    return ans;
}

void solve(){
    int n,m;cin>>n>>m;
    vector<vector<ll>>c(n+1,vector<ll>(m+1));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)cin>>c[i][j];
    vector<ll>v2(3);
    v2[0] = coef(c[1]), v2[1] = coef(c[2]), v2[2] = coef(c[3]);
    sort(all(v2));
    ll tot = v2[1];
    for(int i=1;i<=n;++i){
        ll cur = coef(c[i]);
        if(cur!=tot){
            cout << i << " " << cur - tot << endl;
            return;
        }
    }
    assert(false);

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}