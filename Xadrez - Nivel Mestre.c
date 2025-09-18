#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define N 8
typedef enum {VAZIO, TORRE, BISPO, RAINHA, CAVALO} Peca;

void init(Peca t[N][N]){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) t[i][j]=VAZIO;
    t[7][0]=TORRE; t[7][7]=TORRE;
    t[7][2]=BISPO; t[7][3]=RAINHA; t[7][1]=CAVALO;
}

void print(Peca t[N][N]){
    printf("  a b c d e f g h\n");
    for(int i=0;i<N;i++){
        printf("%d ", 8-i);
        for(int j=0;j<N;j++){
            char c='.';
            if(t[i][j]==TORRE) c='R';
            else if(t[i][j]==BISPO) c='B';
            else if(t[i][j]==RAINHA) c='Q';
            else if(t[i][j]==CAVALO) c='N';
            printf("%c ", c);
        } printf("\n");
    }
}

int pos(const char* s,int* r,int* c){
    if(strlen(s)!=2) return 0;
    char f=tolower(s[0]); char rk=s[1];
    if(f<'a'||f>'h'||rk<'1'||rk>'8') return 0;
    *c=f-'a'; *r=8-(rk-'0'); return 1;
}

int caminho_livre(Peca t[N][N],int r1,int c1,int r2,int c2){
    int dr=(r2>r1)?1:(r2<r1?-1:0);
    int dc=(c2>c1)?1:(c2<c1?-1:0);
    int rr=r1+dr, cc=c1+dc;
    while(rr!=r2||cc!=c2){
        if(t[rr][cc]!=VAZIO) return 0;
        rr+=dr; cc+=dc;
    }
    return 1;
}

int torre_valida(Peca t[N][N],int r1,int c1,int r2,int c2){
    if(r1!=r2 && c1!=c2) return 0; return caminho_livre(t,r1,c1,r2,c2);
}

int bispo_valido(Peca t[N][N],int r1,int c1,int r2,int c2){
    if(abs(r2-r1)!=abs(c2-c1)) return 0; return caminho_livre(t,r1,c1,r2,c2);
}

int rainha_valida(Peca t[N][N],int r1,int c1,int r2,int c2){
    if(r1==r2||c1==c2) return torre_valida(t,r1,c1,r2,c2);
    if(abs(r2-r1)==abs(c2-c1)) return bispo_valido(t,r1,c1,r2,c2);
    return 0;
}

int cavalo_valido(int r1,int c1,int r2,int c2){
    int dr=abs(r2-r1), dc=abs(c2-c1);
    return (dr==2&&dc==1)||(dr==1&&dc==2);
}

 
int torre_rec(Peca t[N][N],int r1,int c1,int r2,int c2){
    if(r1==r2 && c1==c2) return 1;
    if(r1!=r2 && c1!=c2) return 0;
    int dr=(r2>r1)?1:(r2<r1?-1:0);
    int dc=(c2>c1)?1:(c2<c1?-1:0);
    int nr=r1+dr, nc=c1+dc;
    if(nr==r2 && nc==c2) return 1;
    if(t[nr][nc]!=VAZIO) return 0;
    return torre_rec(t,nr,nc,r2,c2);
}

int main(){
    Peca tab[N][N]; init(tab);
    char a[8],b[8];
    printf("=== Xadrez - Nivel Mestre (Torre/Bispo/Rainha/Cavalo + Recursao) ===\n");
    while(1){
        print(tab);
        printf("Movimento (ex: b1 c3, 'sair'): ");
        if(scanf("%7s",a)!=1) break;
        if(strcmp(a,"sair")==0) break;
        if(scanf("%7s",b)!=1) break;
        int r1,c1,r2,c2;
        if(!pos(a,&r1,&c1)||!pos(b,&r2,&c2)){ printf("Entrada invalida.\n"); continue; }
        Peca p=tab[r1][c1]; if(p==VAZIO){ printf("Sem peca na origem.\n"); continue; }
        int ok=0;
        if(p==TORRE) ok=torre_valida(tab,r1,c1,r2,c2)&&torre_rec(tab,r1,c1,r2,c2);
        else if(p==BISPO) ok=bispo_valido(tab,r1,c1,r2,c2);
        else if(p==RAINHA) ok=rainha_valida(tab,r1,c1,r2,c2);
        else if(p==CAVALO) ok=cavalo_valido(r1,c1,r2,c2);
        if(!ok){ printf("Movimento invalido.\n"); continue; }
        tab[r2][c2]=p; tab[r1][c1]=VAZIO;
    }
    return 0;
}
