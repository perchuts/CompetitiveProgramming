#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<pair<int,ll>>g[maxn];
ll want[maxn];
pair<ll,ll> dp[maxn]; // {custo total,soma dos fs}
ll dp2[maxn];//custo subindo

void dfs(int u,int p){
    for(auto x:g[u]){
        int v = x.first;
        ll c = x.second;
        if(v==p)continue;
        dfs(v,u);
        dp[u].first += dp[v].first;//custo na subarvore do filho
        dp[u].first += dp[v].second * c;//custo pra subir
        dp[u].second += dp[v].second;//somar o f do filho
    }
    dp[u].second+=want[u];//somar o f do vertice
}

ll sumf=0;

void dfs2(int u,int p,ll c){
    
    dp2[u] = dp[p].first - dp[u].first - dp[u].second*c +
    (dp[p].second-dp[u].second)*c;//dentro da subarvore de p mas fora de u
    dp2[u]+=dp2[p]+c*(sumf-dp[p].second);//fora da subarvore de p
    
    for(auto x:g[u]){
        int v = x.first;
        ll c = x.second;
        if(v==p)continue;
        dfs2(v,u,c);
    }
}


void solve(){
    int n;cin>>n;

    for(int i=1;i<n;i++){
        int a,b;
        ll t;cin>>a>>b>>t;
        g[a].pb({b,t});
        g[b].pb({a,t});
    }

    int m;cin>>m;
    for(int i=1;i<=m;i++){
        ll x,f;cin>>x>>f;
        want[x] = f;
        sumf+=f;
    }
    dfs(1,1);
    dfs2(1,1,0);

    vector<int>v(n);
    iota(all(v),1);
    sort(all(v),[&](int x,int y){
        if(dp[x].first+dp2[x]==dp[y].first+dp2[y])return x<y;
        return dp[x].first+dp2[x]<dp[y].first+dp2[y];
    });

    ll ans = dp[v[0]].first+dp2[v[0]];

    cout<<2LL*ans<<endl;
    for(int i=0;i<n;i++){
        if(dp[v[i]].first+dp2[v[i]]!=ans)break;
        cout<<v[i];
        if(i!=n-1&&dp[v[i+1]].first+dp2[v[i+1]]==ans)cout<<" ";
    }
    cout<<endl;

    for(int i=1;i<=n;i++){
        g[i].clear();
        dp[i] = {0,0};
        dp2[i] = 0;
        want[i] = 0;
    }
    sumf = 0;
}

int main(){_
    int t;cin>>t;
    while(t--)solve();
}
