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

vector<int>g[maxn];
int ans = 1e8,n;
int dfs(int u,int p){
    int nodes = 1;
    for(auto v:g[u]){
        if(v==p)continue;
        int cur = dfs(v,u);
        ckmin(ans,abs(cur-n+cur));
        nodes+=cur;
    }
    return nodes;
}

int main(){_
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);        
    }    
    dfs(1,1);
    cout<<ans<<endl;
}