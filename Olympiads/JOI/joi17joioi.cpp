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

int grid[2001][2001],n,m,okA[2001][2001],okB[2001][2001],mxA[2001],mxB[2001],mnA[2001],mnB[2001];
int mx = 0,mn = inf;

bool possible(int x){
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            okA[i][j] = grid[i][j] - mn <= x, okB[i][j] = mx - grid[i][j] <= x;

    for(int i=1;i<=n;++i)mxA[i] = mxB[i] = 0, mnA[i] = mnB[i] = inf;

    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(!okA[i][j]&&!okB[i][j])return false;
            if(!okA[i][j]&&okB[i][j])ckmax(mxB[i],j), ckmin(mnB[i],j);
            if(okA[i][j]&&!okB[i][j])ckmax(mxA[i],j), ckmin(mnA[i],j);
        }
    }
    bool ok1 = 1, ok2 = 1;//ok1: A cresce, ok2: B cresce
    int mxxA=0, mxxB=0;
    for(int i=1;i<=n;++i){
        if(mnB[i]<mxA[i])ok1 = 0;
        if(mnA[i]<mxB[i])ok2 = 0;
        if(mnB[i]<=mxxA)ok1 = 0;
        if(mnA[i]<=mxxB)ok2 = 0;
        ckmax(mxxA,mxA[i]);
        ckmax(mxxB,mxB[i]);
    }
    if(ok1+ok2)return true;
    ok1 = ok2 = 1, mxxA = mxxB = m+1;
    for(int i=1;i<=n;++i){//ok1: A diminui, ok2: B diminui
        if(mnB[i]<mxA[i])ok1 = 0;
        if(mnA[i]<mxB[i])ok2 = 0;
        if(mxA[i]>mxxA)ok1 = 0;
        if(mxB[i]>mxxB)ok2 = 0;
        ckmin(mxxA,mnB[i]-1);
        ckmin(mxxB,mnA[i]-1);
    }
    return ok1+ok2;
}

int main(){_
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>grid[i][j];     
            ckmax(mx,grid[i][j]);
            ckmin(mn,grid[i][j]);
        }
    }
    int l = 0, r = mx - mn, ans = r;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md))ans = md, r = md - 1;
        else l = md + 1;
    }
    cout<<ans<<endl;
}