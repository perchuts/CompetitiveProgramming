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
const int maxn = 1005;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ii seg[4*maxn];
int best[maxn][maxn];
bool grid[maxn][maxn];
 
void upd(int i,int l,int r,int x,ii c, bool cima){
    if(l>x||r<x)return;
    if(l==r){
        if(cima){
            ckmax(seg[i].first,-(c.first+c.second));
            ckmax(seg[i].second,-c.first+c.second);
        }else{
            ckmax(seg[i].first, c.first-c.second);
            ckmax(seg[i].second,c.first+c.second);
        }
        return;
    }
    int md = (l+r)/2;
    upd(2*i,l,md,x,c,cima);
    upd(2*i+1,md+1,r,x,c,cima);
    seg[i].first = max(seg[2*i].first,seg[2*i+1].first);
    seg[i].second = max(seg[2*i].second,seg[2*i+1].second);
}
 
ii query(int i,int l,int r,int x,int y){
    if(l>y||r<x)return {-inf,-inf};
    if(x<=l&&r<=y)return seg[i];
    int md = (l+r)/2;
    ii le = query(2*i,l,md,x,y), ri = query(2*i+1,md+1,r,x,y);
    return {max(le.first,ri.first),max(le.second,ri.second)};
}
 
void solve(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            char a;cin>>a;
            grid[i][j] = a=='B'?1:0;
            best[i][j] = 0;
        }
    }
    //subindo, depois descendo
    for(int i=1;i<=4*m;++i)seg[i] = {-inf,-inf};
    
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            int esq = query(1,1,m,1,j).first, dir = query(1,1,m,j,m).second;
            ckmax(best[i][j],esq+i+j);
            ckmax(best[i][j],dir+i-j);
            if(grid[i][j])upd(1,1,m,j,{i,j},1);
        }
    }
 
    
 
    for(int i=1;i<=4*m;++i)seg[i] = {-inf,-inf};
 
    for(int i=n;i>=1;--i){
        for(int j=m;j>=1;--j){
            int esq = query(1,1,m,1,j).first, dir = query(1,1,m,j,m).second;
            ckmax(best[i][j],esq-i+j);
            ckmax(best[i][j],dir-i-j);
            if(grid[i][j])upd(1,1,m,j,{i,j},0);
        }
    }
 
    int melhor = inf;
    ii ans = {1,1};
 
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(ckmin(melhor,best[i][j]))ans = {i,j};
            // cout<<best[i][j]<<" \n"[j==m];
        }
    }
    
 
    cout<<ans.first<<" "<<ans.second<<endl;
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}