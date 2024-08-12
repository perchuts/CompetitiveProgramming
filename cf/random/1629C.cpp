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

int v[2*maxn],suf[2*maxn];
//pegar o prefixo mais a esq tal q mex(pref) = mex(v)
//excluir o pref e efetuar a mesma operacao
vector<int>ans;
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    suf[n+1] = 0;
    set<int>s2;
    for(int i=n;i>=1;i--){
        suf[i] = suf[i+1];
        s2.insert(v[i]);
        if(v[i]==suf[i]){
            for(int j=suf[i]+1;j<=n+1;j++){
                if(s2.count(j)==0){
                    suf[i] = j; 
                    break;
                }
            }
        }
    }   
    int l=1,mex,prev,now;
    while(l<=n){
        mex = suf[l],prev=0,now;
        set<int>s;
        for(;l<=n;l++){
            now = prev;
            s.insert(v[l]);
            if(v[l]==now){
                for(int j=now+1;j<=n+1;j++){
                    if(s.count(j)==0){
                        now = j;break;
                    }
                }
            }
            prev = now;
            if(now==mex)break;
        }
        l++;ans.pb(mex);
    }
    cout<<sz(ans)<<endl;
    for(auto x:ans)cout<<x<<" ";
    cout<<endl;
    ans.clear();

}


int main(){_
    int t;cin>>t;
    while(t--)solve();
}