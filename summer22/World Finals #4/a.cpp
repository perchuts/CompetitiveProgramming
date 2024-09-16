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
#define mp make_pair
using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<pair<ll,ii>>edges;
map<pair<ll,ii>,bool>can;

int n,m,lvl[maxn],par[maxn];

int findp(int x){return par[x] = (par[x]==x ? x : findp(par[x]));}

bool merge(int x,int y){
    x = findp(x),y = findp(y);
    if(x==y)return false;
    if(lvl[x]<lvl[y])swap(x,y);
    par[y] = x;
    if(lvl[x]==lvl[y])lvl[x]++;
    return true;
}

ll kruskal(){
    sort(all(edges));
    ll w = 0;
    for(auto x:edges){
        if(merge(x.second.first,x.second.second)){
            can[mp(x.first,mp(max(x.second.first,x.second.second),min(x.second.second,x.second.first)))] = 1;
            w += x.first;
        }
    }
    return w;
}


int it = 0;

void solve(){
    cin>>n>>m;
    ll ans = 0;
    for(int i=1;i<=m;i++){
        int a,b;
        ll c;cin>>a>>b>>c;
        ans+=c;
        edges.pb({-c,{a,b}});
    }
    for(int i=1;i<=n;i++)par[i] = i,lvl[i] = 0;
    ans+=kruskal();
    int mn = 0;
    for(auto x:edges)if(!can[mp(x.first,mp(max(x.second.first,x.second.second),min(x.second.second,x.second.first)))])ckmax(mn,-x.first);
    printf("Case #%d: %d %d\n",++it,ans,mn);
    edges.clear();
    can.clear();
}


int main(){_
    int t;cin>>t;
    while(t--)solve();
}