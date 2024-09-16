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
int p[maxn],t[maxn],v[maxn];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n;cin>>n;
    for(int i=1;i<=n;i++)
        cin>>p[i];
    for(int i=1;i<=n;i++)
        cin>>t[i];
    for(int i=1;i<=n;i++)
        v[i]=p[i]-t[i];
    int ans=0;
    for(int i=1;i<=n;i++){
        if(v[i]>0&&v[i-1]>0){
            if(v[i]>v[i-1])ans+=v[i]-v[i-1];
        }   
        else if(v[i]<0&&v[i-1]<0){
            if(v[i]<v[i-1])ans+=v[i-1]-v[i];
        }
        else{
            ans+=abs(v[i]);
        }
    }
    cout<<ans<<endl;

}