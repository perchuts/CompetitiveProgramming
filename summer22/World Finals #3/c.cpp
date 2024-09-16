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

template<typename X, typename Y> bool ckmenor(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<vector<pair<ll,int>>>g;
pair<ll,int> mn[1005];
int n,m;
ll w = 0;

ll prim1(){
    vector<bool>vis(n+10,false);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
    pq.push({0,1});
    for(int i=1;i<=n;i++){
        mn[i] = {inf,0};
    }
    mn[1] = {0,1};
    ll weight = 0;
    while(!pq.empty()){
        ll c = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if(vis[v])continue;
        vis[v] = 1;
        weight += c;
        for(auto e:g[v]){
            if(!vis[e.second]&&mn[e.second].first>e.first){
                mn[e.second].first = e.first;
                mn[e.second].second = v;
                pq.push(e);
            }
        }
    }
    return weight;
}

bool prim2(int x,int y){
    vector<bool>vis(n+10,false);
    vector<ll>menor(n+10,inf);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
    pq.push({0,1});
    menor[1] = 0;
    ll weight = 0;
    while(!pq.empty()){
        ll c = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if(vis[v])continue;
        vis[v] = 1;
        weight += c;
        for(auto e:g[v]){
            if(!vis[e.second]&&menor[e.second]>e.first){
                if(max(e.second,v)==y&&min(e.second,v)==x)continue;
                menor[e.second] = e.first;
                pq.push(e);
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++)cnt+=vis[i];
    return !(weight==w&&cnt==n);    
}


int main(){_
    while((cin>>n>>m)){
        g.resize(n+10);
        for(int i=1;i<=m;i++){
            int a,b;ll c;cin>>a>>b>>c;
            g[a].pb({c,b}); 
            g[b].pb({c,a});
        }    
        w = prim1();//O(N^2)
        ll ans = 0,cost=0;
        for(int i=2;i<=n;i++){//O(n)
            if(prim2(min(i,mn[i].second),max(i,mn[i].second)))ans++,cost+=mn[i].first;
            //o(n2)
        }
        cout<<ans<<" "<<cost<<endl;
        g.clear();
    }
}