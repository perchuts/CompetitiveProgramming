#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

ll qnt[101][101], tot[101], mx[26];

int main(){_
    ll n,k;cin>>n>>k;
    string s;cin>>s;
    //calcula numero de substrings de tamanho x pra todo 1<=x<=n    
    //pega as substrings em ordem decrescente de tamanho
    for(int i=0;i<=100;++i)qnt[0][i] = 1;
    
    tot[0] = 1;

    for(int tam=1;tam<=n;++tam){

        for(int i=0;i<26;++i)mx[i] = 0;

        for(int i=tam-1;i<n;++i){
            if(i)qnt[tam][i] = qnt[tam-1][i-1];
            else qnt[tam][i] = 1;
        }

        ll cur = 0;

        for(int i=tam-1;i<n;++i){
            if(qnt[tam][i]>mx[s[i]-'a'])cur += qnt[tam][i] - mx[s[i]-'a'], mx[s[i]-'a'] = qnt[tam][i];
            qnt[tam][i] = cur;
        }

        tot[tam] = cur;
    }

    // for(int i=1;i<=n;++i)for(int j=0;j<n;++j)cout<<qnt[i][j]<<" \n"[j==n-1];

    ll ans = 0;

    for(ll tam=n;~tam;--tam){
        ans += min(k,tot[tam])*n - min(k,tot[tam])*tam;
        k -= tot[tam];
        if(k<=0)break;
    }

    if(k>0)cout<<-1<<endl;
    else cout<<ans<<endl;
}