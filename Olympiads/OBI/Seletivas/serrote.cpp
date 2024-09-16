/*
    Seletiva IOI 2015
    Serrote
    https://neps.academy/br/exercise/359
    por Gabriel Lucas
*/

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
#define mod (ll)(1e9+7)

using namespace std;
ll dp[1001][1001];//dp[i][j] = numero de permutacoes com n=i e k=j
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n,k;cin>>n>>k;
    dp[1][0]=1;
    for(int i=2;i<=n;i++)//no caso k=0, n=i deve ser o ultimo ou o primeiro da permutacao => dp[i][0]=2^(i-1)
        dp[i][0]=(dp[i-1][0]+dp[i-1][0])%mod;

    for(int i=1;i<=n;i++){
        for(ll j=1;j<=(i-1)/2;j++){//lidar com a posicao de i na permutacao
            dp[i][j] = (2LL*dp[i-1][j]+(i-2LL*j)*dp[i-1][j-1]+dp[i-1][j]*2LL*j)%mod;
            //i ficando na borda (nao sendo um dente) + i criando um novo dente + i substituindo um dente ja existente 
        }

    }
    cout<<dp[n][k]<<endl;
}   