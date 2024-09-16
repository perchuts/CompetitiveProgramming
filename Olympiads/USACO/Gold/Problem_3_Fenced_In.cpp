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

int a,b,n,m;
int par[2010*2010],lvl[2010*2010];

int findp(int x){return par[x] = (par[x]==x ? x : findp(par[x]));}

bool merge(int x,int y){
    x = findp(x),y = findp(y);
    if(x==y)return 0;
    if(lvl[x]<lvl[y])swap(x,y);
    if(lvl[y]==lvl[x])lvl[x]++;
    par[y] = x;
    return 1;
}

void init(){
    for(int i=0;i<=(n+5)*(m+5);i++)
        par[i]=i,lvl[i]=0;
}

int conv(int x,int y){
    return x*(m+1)+y;
} 

int main(){_
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    cin>>a>>b>>n>>m;
    vector<int>v(n+1),h(m+1);
    for(int i=0;i<n;i++)cin>>v[i];
    for(int i=0;i<m;i++)cin>>h[i];
    sort(all(v));sort(all(h));
    for(int i=0;i<n;i++)v[i] = v[i+1]-v [i];
    for(int i=0;i<m;i++)h[i] = h[i+1]-h[i];
    v[n] = a - v[n], h[m] = b - h[m];
    sort(all(v));sort(all(h));
    init();
    ll ans=0;
    for(int hi=0,vi=0;hi<=m||vi<=n;){
        if(hi==m+1||(vi<=n&&v[vi]<h[hi])){
            for(int i=0;i<m;i++)
                if(merge(conv(vi,i),conv(vi,i+1)))
                    ans+=1LL*v[vi];
            vi++;
        }else{
            for(int i=0;i<n;i++)
                if(merge(conv(i,hi),conv(i+1,hi)))
                    ans+=1LL*h[hi];
            hi++;
        }
    }
    cout<<ans<<endl;

}