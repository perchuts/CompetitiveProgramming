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

//2 6 
//3 7 
//dp[last_swapped] = min(dp[j]) 0<=j<last_swapped

int dp[105][105*105],a[105],b[105];
void solve(){
    int n;cin>>n;
    int suma=0,sumb=0,sq=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sq+=a[i]*a[i],suma+=a[i];
    }

    for(int i=1;i<=n;i++){
        cin>>b[i];
        sq+=b[i]*b[i],sumb+=b[i];
    }

    if(n==1){
        cout<<0<<endl;
        return;
    }
    
    sq*=(n-2);

    int mx = suma+sumb;

    for(int i=0;i<=n;i++)
        for(int j=0;j<=mx;++j)
            dp[i][j] = inf;
    //aaa
    dp[0][0] = 0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=mx;++j){
            if(dp[i-1][j]!=inf)dp[i][j+b[i]] = dp[i][j+a[i]] = 0;
        }
    }

    int resp = inf;

    for(int i=0;i<=mx;++i){
        if(dp[n][i]!=inf)ckmin(resp,sq+i*i+(mx-i)*(mx-i));
    }

    cout<<resp<<endl;

    
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}