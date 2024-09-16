#include <bits/stdc++.h>

using namespace std;
map<string,int>valores;
map<string,int>tradutor;
map<int,string>tradutorReverso;
string grid[150][150];
int linhaval[150],colval[150];
int linha[105][900],coluna[105][900],lq[105],cq[105];
int main(int argc, char const *argv[])
{
    int l,c;
    cin>>l>>c;
    for(int i=1;i<=l;i++){
        for(int j=1;j<=c;j++){
            string a;
            cin>>a;
            if(!valores.count(a)){
                valores[a]=1;
            }
            grid[i][j]=a;
        }
        int x;
        cin>>x;
        linhaval[i]=x;
    }
    for(int i=1;i<=c;i++){
        int x;
        cin>>x;
        colval[i]=x;
    }
    int e=0;
    for(auto [v,k]:valores){
        tradutorReverso[++e]=v;
        tradutor[v]=e;
    }
    for(int i=1;i<=l;i++){
        for(int j=1;j<=c;j++){
            int pos = tradutor[grid[i][j]];
            if(linha[i][pos]==0){
                linha[i][pos]=1;
                lq[i]++;
            }else{
                linha[i][pos]++;
            }
            if(coluna[j][pos]==0){
                coluna[j][pos]=1;
                cq[j]++;
            }else{
                coluna[j][pos]++;
            }
        }
    }
    int ok=0;
    while(ok<e){
        int lx=0,cx=0;
        for(int i=1;i<=l;i++){
            if(lq[i]==1){
                lx=i;
                break;
            }
        }
        if(lx){
            int x,ind;
            for(int i=1;i<=900;i++){
                if(linha[lx][i]){
                    string str = tradutorReverso[i];
                    valores[str]=linhaval[lx]/linha[lx][i];
                    x=valores[str],ind=i;
                    break;
                }
            }
            for(int i=1;i<=l;i++){
                if(linha[i][ind]){
                    linhaval[i]-=linha[i][ind]*x;   
                    linha[i][ind]=0;
                    lq[i]--;
                }
            }
            for(int i=1;i<=c;i++){
                if(coluna[i][ind]){
                    colval[i]-=coluna[i][ind]*x;
                    coluna[i][ind]=0;
                    cq[i]--;
                }
            }
            
        }else{
            for(int i=1;i<=c;i++){
                if(cq[i]==1){
                    cx=i;
                    break;
                }
            }
            int x,ind;
            for(int i=1;i<=900;i++){
                if(coluna[cx][i]){
                    string str = tradutorReverso[i];
                    valores[str]=colval[cx]/coluna[cx][i];
                    x=valores[str],ind=i;
                    break;
                }
            }
            for(int i=1;i<=l;i++){
                if(linha[i][ind]){
                    linhaval[i]-=linha[i][ind]*x;   
                    linha[i][ind]=0;
                    lq[i]--;
                }
            }
            for(int i=1;i<=c;i++){
                if(coluna[i][ind]){
                    colval[i]-=coluna[i][ind]*x;
                    coluna[i][ind]=0;
                    cq[i]--;
                }
            }
        }        
        ok++;
    }
    for(auto [v,k]:valores){
        cout<<v<<" "<<k<<endl;
    }

    return 0;
}
