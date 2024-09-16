/*
    Seletiva IOI 2018
    Programa de Auditorio
    https://neps.academy/br/exercise/425
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
#define mod (int)(1e9+7)

using namespace std;
vector<int>dp[63000];//dp[i] = guarda a resposta para x = i
vector<int>values,added;
int v[251];
bool ok[65000];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,x;cin>>n>>x;
    for(int i=1;i<=n;i++)
        cin>>v[i];

    values.pb(0);ok[0]=1;
    for(int i=n;i!=0;i--){//iterar em ordem inversa para obter a solucao mais fria possivel
        for(auto j:values){
            if(!ok[j+v[i]]){
                dp[j+v[i]]=dp[j];
                dp[j+v[i]].pb(i);
                added.pb(j+v[i]);
                ok[j+v[i]]=1;
            }
        }
        
        for(auto j:added)
            values.pb(j);
        added.clear();
    }

    if(x<=250*250&&ok[x]){
        cout<<"S"<<endl;
        sort(all(dp[x]));
        for(auto u:dp[x])
            cout<<u-1<<" ";
    }
    else cout<<"N"<<endl;
    

}