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

ll tax[1010];
//so brutar na resposta

multiset<ll>iguais,remover,adicionar;
int n;
ll custoinicial;

ll compute(int x){
    multiset<ll>r = remover, a = adicionar;
    auto it = iguais.rbegin();
    for(int i=1;i<=x;i++){
        r.insert(*it);
        a.insert(*it);
        if(i!=sz(iguais))it = next(it);
    }
    ll taxa = custoinicial,custo = 0;
    it = r.rbegin();
    for(int i=0;i<sz(r);i++){
        taxa -= *it;
        custo += taxa;
        if(i!=sz(r)-1)it = next(it);
    }
    auto it2 = begin(a);
    for(int i=0;i<sz(a);i++){
        taxa += *it2;
        custo += taxa;
        if(i!=sz(a)-1)it2 = next(it2);
    }
    return custo;
}
int tc = 0;
int main(){_
    while(true){
        cin>>n;
        if(!n)break;
        string start,finish;cin>>start>>finish;
        for(int i=0;i<n;i++)cin>>tax[i];        
        custoinicial = 0;
        for(int i=0;i<n;i++){
            custoinicial+=1LL*(start[i]-'0')*tax[i];
            if(start[i]==finish[i]){
                if(start[i]=='1'){
                    iguais.insert(tax[i]);
                }
            }else{
                if(start[i]=='1'){
                    remover.insert(tax[i]);
                }else{
                    adicionar.insert(tax[i]);
                }   
            }
        }
        ll ans = 1e18;
        for(int i=0;i<=sz(iguais);i++)ckmin(ans,compute(i));
        printf("Case %d: %lld\n",++tc,ans);
        iguais.clear();remover.clear();adicionar.clear();
    }    
}