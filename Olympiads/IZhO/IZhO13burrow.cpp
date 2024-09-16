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

int grid[1001][1001], pr[1001][1001], le[1001], ri[1001], n, m, k;

int best(int x){

    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            pr[i][j] = grid[i][j]>=x;

    for(int j=1;j<=m;++j)
        for(int i=1;i<=n;++i)
            pr[i][j] = pr[i][j]==1?1+pr[i-1][j]:0;
    
    int resp = 0;

    for(int i=1;i<=n;++i){

        stack<ii>l, r;
        
        for(int j=1;j<=m;++j){
            while(!l.empty()&&l.top().first>=pr[i][j])l.pop();
            if(l.empty())le[j] = j-1;
            else le[j] = j - l.top().second - 1;
            l.push({pr[i][j],j});
        }

        for(int j=m;j>=1;--j){
            while(!r.empty()&&r.top().first>=pr[i][j])r.pop();
            if(r.empty())ri[j] = m-j;
            else ri[j] = r.top().second - j - 1;
            r.push({pr[i][j],j});
        }

        for(int j=1;j<=m;++j){
            ckmax(resp,(le[j]+ri[j]+1)*pr[i][j]);
        }
    }

    return resp;
}


int main(){_
    // binary search the cheapest square
    // grid[i][j] = 0 if c[i][j] < x, 1 if otherwise
    // use monotonic stacks to find largest rectangle
    // if size of largest rectangle >= k, increase l
    // otherwise lower r  
    // total complexity: O(NMlog(1e9))
    cin>>n>>m>>k;

    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)   
            cin>>grid[i][j];
    
    int l = 1, r = 1e9, ans = 1, siz = 0;

    while(l<=r){
        int md = l + (r-l+1)/2;
        int b = best(md);
        if(b>=k)ans = md, siz = b, l = md + 1;
        else r = md - 1;
    }

    cout<<ans<<" "<<siz<<endl;
}