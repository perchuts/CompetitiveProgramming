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
 
int q[2*maxn],pref[2*maxn][20],best[2*maxn][20];
 
void solve(){
    int n;cin>>n;
 
    for(int i=1,x;i<=n;i++){
        cin>>x;
        q[x]++;
    }
 
    auto nextpower = [&](int x){
        for(int i=0;i<20;i++)if((1<<i)>=x)return i;
    };
 
    int ub=nextpower(n);
 
    for(int j=0;j<=ub;j++){
        int sum = 0;
        pref[0][j]=0;
        for(int i=1;i<=n;i++){
            sum+=q[i];
            int x = nextpower(sum);
            if(x==j)pref[i][j] = sum;
            else pref[i][j] = pref[i-1][j];
        }
    }
    
    for(int j=0;j<=ub;j++){
        int suf = 0;
        best[n+1][j]=0;
        for(int i=n;i>=1;i--){
            suf+=q[i];
            int x = nextpower(suf);
            if(x==j)best[i][j] = suf;
            else best[i][j] = best[i+1][j];
        }
    }
 
    int ans = 2+(1<<ub)-n;// 0 - 0 - n
    
    for(int j=0;j<=ub;j++){ 
        for(int i=1;i<=n;i++){
            for(int k=0;k<=ub;k++){
                int left = pref[i][j];
                int right = best[i+1][k];
                int restante = n - left - right;
                int mid = 1<<nextpower(restante);
                ckmin(ans,(1<<j)+(1<<k)+mid-n);
            }
        }
    }
 
    cout<<ans<<endl;
 
    for(int i=1;i<=n;i++)q[i]=0;    
}
 
 
int main(){_
    int t;cin>>t;
    while(t--)solve();
}