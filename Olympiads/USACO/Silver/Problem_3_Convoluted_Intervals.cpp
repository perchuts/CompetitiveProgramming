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
#define mod (int)(1e9+7)

using namespace std;
ll a[10001],b[10001];
ll waysa[10001],waysb[10001],prefix[10001],suffix[10002];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n,m;cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x,y;cin>>x>>y;
        a[x]++,b[y]++;
    }   
    ll ans = n*n;
    for(int i=0;i<=2*m;i++){
        for(int j=0;j<=i;j++){
            waysa[i]+=a[j]*a[i-j];
            waysb[i]+=b[j]*b[i-j];
        }
    }

    prefix[0]=waysb[0];
    for(int i=1;i<=2*m;i++)
        prefix[i]=prefix[i-1]+waysb[i];

    for(int i=2*m;i>=0;i--)
        suffix[i]=suffix[i+1]+waysa[i];
        
    for(int i=0;i<=2*m;i++){
        cout<<ans-(i ? prefix[i-1] : 0LL)-suffix[i+1]<<endl;
    }
}