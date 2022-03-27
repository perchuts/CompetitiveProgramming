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

bool dp[20][(1<<20)], mark[20][(1<<20)];
vector<int>a,b;
vector<ii>g[(1<<20)];
int n,m;
int indmax;
bool solve(int i,int mask,int sum=0){
    if(i==n)return 1;
    if(mark[i][mask])return dp[i][mask];
    mark[i][mask] = 1;
    if(sum==a[i])return dp[i][mask] = solve(i+1,mask,0);
    else if(sum>a[i])return dp[i][mask] = 0;
    for(auto [a,b]:g[mask]){
        dp[i][mask]|=solve(i,a,sum+b);
    }
    return dp[i][mask];
}


int main(){_
    cin>>n>>m;
    a.resize(n);b.resize(m);
    sort(all(a));sort(all(b));
    for(auto& x:a)cin>>x;
    for(auto& x:b)cin>>x;
    for(int i=0;i<(1<<m);++i){
        int tmp = 0;
        while(tmp<m){
            if(((1<<tmp)&i)==0)g[i].pb({((1<<tmp)|i),b[tmp]});
            ++tmp;
        }
    }
    cout<<(solve(0,0)?"YES":"NO")<<endl;
}