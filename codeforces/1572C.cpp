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
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int>v;
int dp[3003][3003];
vector<int>idx[3003];
void solve(){
    int n;cin>>n;
    v.resize(n+1);
    for(int i=1;i<=n;++i)cin>>v[i];
    for(int i=1;i<=n;++i){
        idx[v[i]].pb(i);
    }
    for(int i=n;i>=1;--i){
        for(int j=i;j<=n;++j){
            if(i==j)dp[i][j] = 0;
            else{
                dp[i][j] = dp[i+1][j];
                for(auto k:idx[v[i]])
                    if(i<k&&k<=j)ckmax(dp[i][j],1+dp[i+1][k-1]+dp[k][j]);
            }
        }
    }

    cout<< n - 1 - dp[1][n] <<endl;
    for(int i=1;i<=n;++i)idx[i].clear();
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}