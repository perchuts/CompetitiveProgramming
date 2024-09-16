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

ll dp[2*maxn][15];
pair<ll,ll>box[2*maxn];
int n,k;
bool ok[2*maxn][15];

ll solve(int i,int j){
    if(i==n+1)return 0;
    if(ok[i][j])return dp[i][j];
    ok[i][j] = 1;
    dp[i][j] = solve(i+1,j);
    if(j==0)return dp[i][j] = max(dp[i][j],box[i].first-box[i].second);
    ll imp = min(box[i].first-box[i].second,solve(i+1,j-1)-box[i].second);
    return dp[i][j] = max(dp[i][j],imp);
}

void solve(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>box[i].first>>box[i].second;
    }
    sort(box+1,box+1+n);
    cout<<solve(1,k)<<endl;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=k;j++)
            dp[i][j] = ok[i][j] = 0;
}


int main(){_
    int t;cin>>t;
    while(t--)solve();
}