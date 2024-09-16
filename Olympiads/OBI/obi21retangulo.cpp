#include <bits/stdc++.h>
#define maxn (int)(1e5+10)
using namespace std;
map<long long,int>vertices;
long long pref[maxn];
int main(int argc, char const *argv[])
{
    int n;
    
    cin>>n;
    for(int i=1;i<=n;i++){
        long long l;
        cin>>l;
        pref[i]=pref[i-1]+l;
        vertices[pref[i-1]]=i;
    }
    if(pref[n]&1){
        cout<<"N";
        return 0;
    }
    long long metade = pref[n]/2;
    int counter=0;
    for(int i=1;i<=n;i++){
        if(pref[i-1]>=metade)break;
        int par=vertices[pref[i-1]+metade];
        if(par!=0)counter++;
        if(counter>=2)break;
    }
    if(counter>=2){
        cout<<"Y";
    }else
        cout<<"N";
    return 0;
}
