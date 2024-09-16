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
vector<int>g[maxn];
int ans=0;

void dfs(int u,int p){
    int necessary=sz(g[u])-(u==1?0:1);
    int x=0;
    while((1<<x)<necessary+1)x++;
    ans+=x+necessary;
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}
void solve(){
    int n;cin>>n;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1,1);
    cout<<ans<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t=1;//cin>>t;
    while(t--)solve();
}