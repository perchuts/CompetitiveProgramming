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

bool hasL = 0;
int cnt = 0;
string s;
ll ans = 0;

void solve(int i,int cntC,int cntV){
    if(i==sz(s)){
        if(i>2&&s[i-1]==s[i-2]&&s[i-2]==s[i-3])return;
        ll powV=1LL,powC=1LL,powCwithoutL=1LL;
        for(int i=1;i<=cntV;i++)powV*=5LL;          
        for(int i=1;i<=cntC;i++)powC*=21LL,powCwithoutL*=20LL;
        ll add = powV*powC;
        if(!hasL)add = cntC ? powV*(powC-powCwithoutL) : 0;
        ans+=add;
        return;
    }
    if(s[i]!='_'){
        if(i>1&&s[i]==s[i-1]&&s[i-1]==s[i-2])return;
        solve(i+1,cntC,cntV);
    }else{
        s[i]='V';
        if(i<=1||(i>1&&!(s[i]==s[i-1]&&s[i-1]==s[i-2])))solve(i+1,cntC,cntV+1);
        s[i]='C';
        if(i<=1||(i>1&&!(s[i]==s[i-1]&&s[i-1]==s[i-2])))solve(i+1,cntC+1,cntV);
        s[i]='_';
    }
}
int main(){_
    cin>>s;
    for(int i=0;i<sz(s);i++){
        if(s[i]=='_'||s[i]=='L'){
            cnt+=s[i]=='_';
            hasL |= s[i]=='L';
            if(s[i]=='L')s[i]='C';
            continue;
        }
        if(s[i]=='A'||s[i]=='E'||s[i]=='I'||s[i]=='O'||s[i]=='U')s[i] = 'V';
        else s[i]='C';
    }
    if(!cnt){
        ans = hasL;
        for(int i=2;i<sz(s);i++){
            if(s[i]==s[i-1]&&s[i-2]==s[i-1]){
                ans=0;break;
            }
        }
    }else{
        solve(0,0,0);
    }
    cout<<ans<<endl;
}