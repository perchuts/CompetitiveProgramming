#include <bits/stdc++.h>

using namespace std;
int tempo[150];
int precisaresposta[150];
set<int>amigos;
int main(int argc, char const *argv[]) {
  memset(precisaresposta,-1,sizeof(precisaresposta));
  int n;
  cin>>n;
  int tempopassado=0;
  char anterior = '-';
  for(int i=0;i<n;i++){
    char a;
    int b;
    cin>>a>>b;
    if(a!='T'&&amigos.find(b)==amigos.end()){
      amigos.insert(b);
    }
    if(a=='R'){
      if(anterior!='-'&&anterior!='T'){
        tempopassado++;
      }
      precisaresposta[b]=tempopassado;
    }
    if(a=='E'){
      if(anterior!='-'&&anterior!='T'){
        tempopassado++;

      }
      tempo[b]+=abs(tempopassado-precisaresposta[b]);
      precisaresposta[b]=-1;
    }
    if(a=='T'){
      tempopassado+=b;
    }
    anterior = a;
  }
  for(set<int>::iterator it = amigos.begin();it!=amigos.end();++it){
    if(precisaresposta[*it]!=-1){
      cout<<*it<<" "<<"-1"<<endl;
    }else{
      cout<<*it<<" "<<tempo[*it]<<endl;
    }
  }
  return 0;
}
