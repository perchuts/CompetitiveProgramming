/*
    Seletiva IOI 2019
    Torneio
    https://codeforces.com/group/2k70zKp2Ci/contest/263343/problem/B
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
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

int vencedorPartida(int a, int b);
int numeroVitorias(int competidor);
void responde(int tamanho, int array[]);

int saida[1001],par[1001],der[1001],mark[1001][1001],vis[1001],wins[1001];

int getposition(int x,int last){
    int resp = last;
    while(--x)resp = par[resp];
    return resp;
}

int procura(int x,int n){
    for(int i=1;i<=n;i++)if(i!=x&&der[i]<5&&!mark[x][i]&&!vis[i])return i;
    return -1;
}

int procura(int n){
    for(int i=1;i<=n;i++)if(!vis[i])return vis[i]=i;
    return -1;
}

void processaTorneio(int S, int N) {
    int tamanho = N; // Tamanho do array a retornar
    if(S==1){
        for(int i=1;i<=N;i++){
            for(int j=i+1;j<=N;j++){
                int vencedor = vencedorPartida(i,j);
                saida[i-1]+=vencedor==i,saida[j-1]+=vencedor==j;
            }
        }
    }else if(S==2){ 
        //é possível imaginar que cada jogador escolhe um número entre
        //1 e N. A ganha de B se número de A > número de B. Logo, o jogador que
        //escolhe N vencerá N-1 vezes, o que escolhe N-1 vencerá N-2 e etc.
        //Aplicar uma busca binária para obter a "ordem" atual de cada
        //jogador, baseado nas respostas das queries.
        //Pior caso: NlogN queries < 1e4
        int last = 1;
        for(int i=2;i<=N;i++){
            int l = 1,r = i-1,ans = 0;
            while(l<=r){
                int md = l + (r-l+1)/2;
                int pessoa = getposition(md,last);
                if(vencedorPartida(i,pessoa)==i){
                    ans = md, l = md+1;
                }else{
                    r = md - 1;
                }
            }
            if(ans==0)par[i] = last,last = i;
            else{
                int ganhei = getposition(ans,last);
                par[i] = par[ganhei],par[ganhei] = i;
            }
        }   
        int cur = last;
        for(int i=0;i<N;i++){
            saida[cur-1] = i;
            cur = par[cur];
        }
    }else if(S==3||S==4){
        //só haverá um jogador vencendo todos os outros se ele for o best após
        //iterarmos sobre todos os jogadores.
        //depois, verificar se o best realmente vence todos.
        //Pior caso: 2N - 1 queries < 2e3
        int best = 1;
        for(int i=2;i<=N;i++){
            if(vencedorPartida(best,i)==i)best = i;
        }
        bool ok = true;
        for(int i=1;i<=N;i++){
            if(i==best)continue;
            if(vencedorPartida(best,i)!=best)ok = 0;
        }
        if(ok)tamanho = 1,saida[0] = best;
        else tamanho = 0;
    }else if(S==5){
        //Verificar o resultado do jogo entre dois jogadores que ainda têm menos que
        //5 derrotas até não dar mais. 
        //Pior caso: 5N
        //
        //Lema: após o procedimento acima, sobrarão no máximo 9 jogadores com menos
        //que 5 derrotas.
        //Prova: Seja K o número de jogadores que "sobraram" após o procedimento.
        //Vamos analisar apenas os jogos que ocorreram entre esses K jogadores.
        //Seja X o número de derrotas do jogador que mais perdeu.
        //Temos que X>= (K-1)/2. Pelo problema, (K-1)/2 <= X <= 4  
        //(K-1)/2 <= 4. K <= 9.
        //
        //Com isso, basta verificar se cada jogador que sobrou realmente perdeu
        //menos que 5 partidas.
        //Pior caso: 9N
        //Total: 14N < 2e4.
        int cur = 1;
        while(true){
            if(der[cur]>4||vis[cur])cur = procura(cur,N);
            if(cur==-1)break;
            int target = procura(cur,N);
            if(target==-1){
                vis[cur] = 1;
                continue;
            }
            mark[cur][target] = mark[target][cur] = 1;
            if(vencedorPartida(cur,target)==cur){
                der[target]++;
                cur = target;
            }else der[cur]++;
        }
        tamanho = 0;
        for(int i=1;i<=N;i++){
            if(der[i]<5){
                int cnt = 0;
                for(int j=1;j<=N;j++){
                    if(j==i)continue;
                    cnt+=vencedorPartida(i,j)!=i;
                }
                if(cnt<5)saida[tamanho++] = i;
            }
        }
    }else{
        //Registrar o número de vitórias de cada jogador. Perceba que o jogador que
        //vence N-1 partidas nunca participará da resposta. Logo, podemos removê-lo
        //da busca. Caso esse jogador realmente exista, perceba que os jogadores que
        //venceram N-2 partidas também nunca participarão da resposta. É possível
        //repetir esse argumento sucessivamente para N-3,N-4... e analogamente para 
        //0,1...
        //Todos os jogadores restantes venceram pelo menos um jogo e perderam 
        //pelo menos um para outro jogador que também não foi eliminado.
        //Seja B o jogador que, dentre os que restaram, venceu mais partidas. Iremos
        //tentar encontrar outros jogadores A,C tais que A ganha de B, B ganha de C e
        //C ganha de A, assim formando um ciclo.
        //podemos encontrar A facilmente em no máximo N-1 buscas.
        //Como B venceu mais partidas que todos, precisamos de no máximo 
        // (N-3)/2 + (N-1) queries.
        //Pior caso: N + N-1 + N-1 + (N-3)/2 > 3e3
        //entretanto, esse caso nunca irá acontecer. Quanto mais demoramos para 
        //encontrar A, menos demoramos para encontrar C. Isso é 
        //suficiente para achar a resposta.
        for(int i=1;i<=N;i++)wins[i] = numeroVitorias(i);
        for(int i=N-1;~i;i--){
            bool bad = 0;
            for(int j=1;j<=N;j++){
                if(wins[j]==i)bad = 1, vis[j] = 1;
            }
            if(!bad)break;
        }  
        for(int i=0;i<N;i++){
            bool bad = 0;
            for(int j=1;j<=N;j++){
                if(wins[j]==i)bad = 1, vis[j] = 1;
            }
            if(!bad)break;
        } 
        int a,b,c,mx=-1;
        for(int i=1;i<=N;i++){//make b = max(wins[i])
            if(!vis[i]&&wins[i]>mx){
                mx = wins[i], b = i;
            }
        }
        vis[b] = 1;
        for(int i=1;i<=N;i++){
            if(!vis[i]&&vencedorPartida(b,i)==i){
                a = i;break;
            }
        }//2N-1 queries so far
        vis[a] = 1;
        for(int i=1;i<=N;i++){
            if(!vis[i]){
                if(vencedorPartida(i,b)==b&&vencedorPartida(i,a)==i){
                    c=i;break;
                }
            }
        }
        tamanho = 3, saida[0] = a, saida[1] = b, saida[2] = c;
    }
    responde(tamanho, &saida[0]);
}