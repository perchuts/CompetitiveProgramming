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


int main(){_
    while(true){
        int m,n;cin>>m;
        cin.ignore();
        if(!m)break;
        string s;getline(cin,s);
        map<char,int>mp;
        int r = 0,ans = 0,qnt = 0;
        n = sz(s);
        for(int l = 0;l<n;l++){
            while(r<n&&qnt<=m&&!(qnt==m&&mp[s[r]]==0)){
                mp[s[r]]++;
                qnt+=mp[s[r++]]==1;
            }
            if(qnt<=m)ckmax(ans,r-l);
            mp[s[l]]--;
            if(mp[s[l]]==0)qnt--;
        }
        cout<<ans<<" ";
    }        
}