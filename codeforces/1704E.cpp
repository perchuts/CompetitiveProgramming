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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int>g[1005];

ll dp[1005];
int n,m,sink;

ll calc(int x){
    vector<ll>in(n+1), res(n+1);
    queue<int>q;
    q.push(x);
    while(!q.empty()){
        auto u = q.front();q.pop();
        for(auto v:g[u]){
            in[v]++;
            if(in[v]==1)q.push(v);
        }
    }
    res[x] = 1;
    q.push(x);
    while(!q.empty()){
        auto u = q.front();q.pop();
        for(auto v:g[u]){
            res[v] = (res[v]+res[u])%mod, --in[v];
            if(in[v]==0)q.push(v);
        }
    }
    return res[sink];
}

void solve(){
    cin>>n>>m;

    vector<ll>a(n+1), in(n+1);

    for(int i=1;i<=n;++i)cin>>a[i];

    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        in[v]++;
        g[u].pb(v);
    }

    for(int i=1;i<=n;++i){
        if(sz(g[i])==0)sink = i;
    }
    
    ll resp = 0;

    for(int __=1;__<=n;++__){
        vector<int>executa;
        for(int i=1;i<=n;++i){//pular o n, resposta está em a[n] + resp
            if(a[i])executa.pb(i);
        }
        if(!sz(executa))break;
        ++resp;
        for(auto x:executa){
            --a[x];
            for(auto y:g[x])++a[y];
        }
    }

    queue<int>q;

    for(int i=1;i<=n;++i){
        dp[i] = calc(i);
        resp = (resp+dp[i]*a[i])%mod;
    }
    
    for(int i=1;i<=n;++i){
        g[i].clear();
        dp[i] = 0;
    }

    cout << resp << endl;

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}