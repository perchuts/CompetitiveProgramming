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
#define inf (int)(2e9+1)
#define mod 998244353 //998244353 

using namespace std;
int p[5001],comb[5001][5001];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,k;cin>>n>>k;
    string s;cin>>s;
    int cnt=0,last=0;
    for(int i=1;i<=n;i++){
        p[i] = p[i-1]+(s[i-1]-'0');
    }
    comb[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(j==0){
                comb[i][j]=1;
            }else{
                comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
            }
        }
    }

    int ans=1;
    if(p[n]<k){
        cout<<ans<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int q1 = p[j]-p[i-1];
            int cnt = j-i-1;
            if(q1>k)break;
            if(s[i-1]=='0')q1--;
            if(s[j-1]=='0')q1--;
            if(q1>=0&&q1<=cnt)ans = (ans+comb[cnt][q1])%mod;
        }
    }
    cout<<ans<<endl;
}