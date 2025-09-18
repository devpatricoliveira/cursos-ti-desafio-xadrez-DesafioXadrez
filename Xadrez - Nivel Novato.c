#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define N 8
typedef enum {VAZIO, TORRE, BISPO, RAINHA, CAVALO} Peca;

void init(Peca t[N][N]){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) t[i][j]=VAZIO;
    t[7][0]=TORRE; t[7][7]=TORRE;
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

int torre_valida(Peca t[N][N],int r1,int c1,int r2,int c2){
    if(r1!=r2 && c1!=c2) return 0;
    if(r1==r2){ int st=(c1<c2)?c1+1:c2+1, ed=(c1<c2)?c2:c1;
        for(int cc=st;cc<ed;cc++) if(t[r1][cc]!=VAZIO) return 0;
    } else { int st=(r1<r2)?r1+1:r2+1, ed=(r1<r2)?r2:r1;
        for(int rr=st;rr<ed;rr++) if(t[rr][c1]!=VAZIO) return 0;
    }
    return 1;
}

int main(){
    Peca tab[N][N]; init(tab);
    char a[8],b[8];
    printf("=== Xadrez - Nivel Novato (Torre) ===\n");
    while(1){
        print(tab);
        printf("Movimento (ex: a1 a4, 'sair' p/ encerrar): ");
        if(scanf("%7s",a)!=1) break;
        if(strcmp(a,"sair")==0) break;
        if(scanf("%7s",b)!=1) break;
        int r1,c1,r2,c2;
        if(!pos(a,&r1,&c1)||!pos(b,&r2,&c2)){ printf("Entrada invalida.\n"); continue; }
        if(tab[r1][c1]!=TORRE){ printf("Origem nao tem torre.\n"); continue; }
        if(!torre_valida(tab,r1,c1,r2,c2)){ printf("Movimento invalido.\n"); continue; }
        tab[r2][c2]=tab[r1][c1]; tab[r1][c1]=VAZIO;
    }
    return 0;
}
