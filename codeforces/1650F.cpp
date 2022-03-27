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

const ll inf = 1e17+10;
const int mod = 1e9+7;
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int v[maxn];

struct option{
    ll t, p;
    int ind;
}temp;
vector<option>o[maxn];
void solve(){
    int n,m;cin>>n>>m;
    vector<vector<ll>>dp(m+1,vector<ll>(205));
    for(int i=1;i<=n;++i)o[i].clear();
    vector<int>answer;
    for(int i=1;i<=n;++i)cin>>v[i];
    ll time = 0;
    for(int i=1;i<=m;++i){
        int x;cin>>x>>temp.t>>temp.p;
        temp.ind = i;
        o[x].pb(temp);
    }
    for(int i=1;i<=n;++i){
        int mx = sz(o[i]);
        for(int j=0;j<=mx;++j)
            for(int k=0;k<=200;++k)dp[j][k] = inf;
        
        dp[0][0] = 0;
        for(int j=1;j<=mx;++j){
            for(int k=0;k<=200;++k){
                dp[j][k] = dp[j-1][k];
                if(o[i][j-1].p<=k)ckmin(dp[j][k],dp[j-1][k-o[i][j-1].p]+o[i][j-1].t);
            }
        }
        ll best = inf,indbest = -1;
        for(int j=100;j<=200;++j)if(ckmin(best,dp[mx][j]))indbest = j;
        if(time+best>v[i]){
            cout<<-1<<endl;
            return;
        }
        int j = mx;
        time += best;
        while(j){
            if(indbest>=o[i][j-1].p&&
            dp[j][indbest]==dp[j-1][indbest-o[i][j-1].p]+o[i][j-1].t){
                indbest-=o[i][j-1].p;
                answer.pb(o[i][j-1].ind);
            }
            --j;
        }
    }
    cout<<sz(answer)<<endl;
    for(auto x:answer)cout<<x<<" ";
    cout<<endl;

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}