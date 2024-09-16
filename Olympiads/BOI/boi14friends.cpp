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
 
const ll MOD = 1e9+9;
const ll P = 31;
 
vector<ll>pw,prHash;
 
 
int main(){_
    int n;string s;cin>>n>>s;
    pw.pb(1);
    while(sz(pw)!=n+1)pw.pb((pw.back()*P)%MOD);
    prHash.resize(n+1);
    prHash[0] = 0;
    if(n%2==0){
        cout<<"NOT POSSIBLE"<<endl;
        return 0;
    }
    for(int i=0;i<n;++i)prHash[i+1] = ((s[i]-'A'+1) + (P*prHash[i])%MOD)%MOD;
    
    auto calcHash = [&](int l,int r){
        return (MOD + prHash[r+1] - (prHash[l]*pw[r-l+1])%MOD)%MOD;
    };
    int ans = -1,anshash;
    for(int i=0;i<n;++i){//try to remove every character from string
        if(i<n/2){
            ll left = calcHash(0,i-1);
            ll right = calcHash(i+1,n/2);
            ll rest = calcHash(n/2+1,n-1);
            ll tot = ((left*pw[n/2-i])%MOD + right)%MOD; 
            if(tot==rest){
                if(ans==-1)ans=i,anshash=tot;
                else if(anshash!=tot){
                    cout<<"NOT UNIQUE"<<endl;
                    return 0;
                }
            }
        }else if(i==n/2){
            if(calcHash(0,n/2-1)==calcHash(n/2+1,n-1)){
                if(ans==-1)ans=i,anshash=calcHash(0,n/2-1);
                else if(anshash!=calcHash(0,n/2-1)){
                    cout<<"NOT UNIQUE"<<endl;
                    return 0;
                }
            }
        }else{
            ll rest = calcHash(0,n/2-1);
            ll left = calcHash(n/2,i-1);
            ll right = calcHash(i+1,n-1);
            ll tot = ((left*pw[n-i-1])%MOD+right)%MOD;
            if(tot==rest){
                if(ans==-1)ans=i,anshash=tot;
                else if(anshash!=tot){
                    cout<<"NOT UNIQUE"<<endl;
                    return 0;
                }
            }
        }
    }
    if(ans==-1)cout<<"NOT POSSIBLE";
    else cout<<(ans>=n/2?s.substr(0,n/2):s.substr(n/2+1,n/2));
}