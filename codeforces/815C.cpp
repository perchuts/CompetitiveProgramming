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
const int maxn = 5001;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ll c[maxn], d[maxn];
 
vector<int>g[maxn];
 
vector<ll> dp[maxn][2];//dp[i][t][j] = pego j caras na subarvore de i, t=0 nao posso usar desconto, t=1 caso contrario
 
vector<ll> merge(vector<ll>a,vector<ll>b){
    vector<ll>res(sz(a)+sz(b)-1, 1e18);
    for(int i=0;i<sz(a);++i){
        for(int j=0;j<sz(b);++j){
            ckmin(res[i+j], a[i] + b[j]); 
        }
    }
    return res;
}
 
void dfs(int u){
    dp[u][0] = {0, c[u]};
    dp[u][1] = {(ll)1e18, d[u]};
    for(auto v:g[u]){
        dfs(v);
        dp[u][0] = merge(dp[u][0], dp[v][0]);
        dp[u][1] = merge(dp[u][1], dp[v][1]);
    }
    for(int i=0;i<sz(dp[u][1]);++i)ckmin(dp[u][1][i], dp[u][0][i]);
}
 
int main(){_
    int n;ll b;cin>>n>>b;
    for(int i=1;i<=n;++i){
        cin >> c[i] >> d[i];
        d[i] = c[i] - d[i];
        if(i!=1){
            int x;cin>>x;
            g[x].pb(i);
        }
    }    
    dfs(1);
    for(int i=n;~i;--i){
        if(dp[1][1][i]<=b){
            cout<<i<<endl;
            return 0;
        }
    }
}