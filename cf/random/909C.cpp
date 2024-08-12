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

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }
bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

char v[maxn];
int dp[5001][5001],suf[5001];//dp[i][j] = ways of arranging first i lines of code with i-th line occuping the j-th level of indent
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>v[i];
    v[0]='s';
    int lvl=1;
    suf[1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=lvl;j++){
            if(v[i-1]=='f'){
                dp[i][j+1]=dp[i-1][j];
            }else{
                dp[i][j]=suf[j];
            }
        }
        if(v[i]=='f')lvl++;
        suf[lvl+1]=0;
        for(int j=lvl;j>=1;j--)
            suf[j]=(suf[j+1]+dp[i][j])%mod;        
    }
    int ans=0;
    for(int i=1;i<=lvl;i++)ans=(ans+dp[n][i])%mod;
    cout<<ans<<endl;
}

int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t=1;//cin>>t;
    while(t--)solve();
}