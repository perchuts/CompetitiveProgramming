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

int dp[1001][10001];
int pref[10001];
int main(){_
    int n,c;cin>>n>>c;  
    for(int i=1;i<=n;i++){
        pref[0] = 1;
        int mn = i*(i-1)/2;
        for(int j=0;j<=c;j++){
            if(j<=i-1)dp[i][j] = pref[j];
            else if(j<=mn)dp[i][j] = (pref[j]-pref[j-i]+mod)%mod;
        }
        for(int j=1;j<=c;j++)pref[j] = (pref[j-1]+dp[i][j])%mod;       
    }
    cout<<dp[n][c]<<endl;
}