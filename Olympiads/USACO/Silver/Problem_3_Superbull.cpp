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

int v[2001];
vector<pair<ll,int>>g[2001];
int n;
ll prim(){
    vector<bool>vis(n+1);
    vector<int>mx(n+1,-1);
    set<pair<ll,int>>s;
    s.insert({0,1});
    ll ans = 0;
    while(!s.empty()){
        auto [w,v] = *s.rbegin();
        s.erase(prev(end(s)));
        vis[v]=1;
        ans+=w;
        for(auto [wu,u]:g[v]){
            if(!vis[u]&&mx[u]<wu){
                s.erase({mx[u],u});
                mx[u]=wu;
                s.insert({mx[u],u});
            }
        }
    }
    return ans;
}



int main(){_
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>v[i];
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            g[i].pb({v[i]^v[j],j});
            g[j].pb({v[i]^v[j],i});
        }
    }    
    cout<<prim()<<endl;   
}