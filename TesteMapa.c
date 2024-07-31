#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
#include <math.h>
//#include "funcoes.h"

#define ALTURA_MAPA 30
#define LARGURA_MAPA 60

#define ALTURA_BLOCO 20
#define LARGURA_BLOCO 20

#define TAM_POPUP 200

#define MAX_INIMIGOS 10
#define LARGURA 600
#define ALTURA 1200

char mapa[ALTURA_MAPA][LARGURA_MAPA];

struct pos_J  //estrutura para o jogador
{
    float x;
    float y;
};

typedef struct Inimigo{   //estrutura para o inimigo
    int x;
    int y;
    int dx;
    int dy;
    int x_ant;
    int y_ant;
} INIMIGO;

int deveMover(int x, int y, int dx, int dy, int x_ant , int y_ant , int larg, int alt) //funçãp para ver se inimigo pode continuar seu rumo atual
{
    if(x+1*dx > (larg-20)) return 0;
    if(x+1*dx < 0) return 2;
    if(y+1*dy > (alt-20)) return 3;
    if(y+1*dy < 0) return 4;
    return 1;
}

int moveInimigo( INIMIGO *Inimigo,int largura, int altura, double tempo){
    int p;
    if(fmod(tempo , 2) < 0.016 ){     //função da math.h para pegar resto de divisão de numeros com virgula
    Inimigo->x += Inimigo->dx*20;
    Inimigo->y += Inimigo->dy*20;

    p = deveMover(Inimigo->x,Inimigo->y,Inimigo->dx,Inimigo->dy, Inimigo->x_ant ,   Inimigo->y_ant ,largura,altura);

    Inimigo->x_ant = Inimigo->x;
    Inimigo->y_ant = Inimigo->y;
    return p;
    }
}

void iniciaDesloc(INIMIGO *Inimigo, int ddx,int ddy){

    Inimigo->dx = 0;//GetRandomValue(-1, 1);
    Inimigo->dy = -1;//GetRandomValue(-1, 1);
    Inimigo->x = ddx;
    Inimigo->y = ddy;
    while((Inimigo->dx ==0 && Inimigo->dy == 0)){
        Inimigo->dx = GetRandomValue(-1, 1);
        Inimigo->dy = GetRandomValue(-1, 1);
    }
}

void redefineDeslocamento(INIMIGO *Inimigo, int p)
{
    switch(p){
    case 0:
        Inimigo->dx = GetRandomValue(-1, 0);
        Inimigo->dy = GetRandomValue(-1, 1);
        break;
    case 2:
        Inimigo->dx = GetRandomValue(0, 1);
        Inimigo->dy = GetRandomValue(-1, 1);
        break;
    case 3:
        Inimigo->dx = GetRandomValue(-1, 1);
        Inimigo->dy = GetRandomValue(-1, 0);
        break;
    case 4:
        Inimigo->dx = GetRandomValue(-1, 1);
        Inimigo->dy = GetRandomValue(0, 1);
        break;
    case 5:
        Inimigo->dx = 0;//GetRandomValue(-1, 1);
        Inimigo->dy = 0;//GetRandomValue(0, 1);
        break;
    }
}

int main(void)
{
    struct pos_J J = {0.0, 0.0};  // Inicializa a posição de J

    double time = 0;
    int i=0, n, p;
    int ddx=0,ddy=0; //localização onde nasce os inimigos
    int bbx=0,bby=0; // localização da base

    INIMIGO inimigos[MAX_INIMIGOS];
    carregaMapa("mapa1.txt",&ddx,&ddy,&bbx,&bby);

    for(i = 0; i < MAX_INIMIGOS; i++){
        iniciaDesloc(&inimigos[i],ddx,ddy);
    }

    InitWindow(LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, "TowerDefense");
    SetTargetFPS(60);

    InitPosicaoJogador(&J, mapa);

    while (!WindowShouldClose()){

        time = GetTime();     //função raylib que pega o tempo desde de que a janela foi aberta

        DesenhaMapa(mapa);

        MovimentoJogador(&J, mapa);

        PortaTrancada(&J, mapa);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(J.x, J.y, LARGURA_BLOCO, ALTURA_BLOCO, DARKBLUE);

        for(int i=0; i<MAX_INIMIGOS; i++){        //laço que atualiza a posição dos inimigos, testa a sua posição e desanha cada 1
            moveInimigo(&inimigos[i], ALTURA, LARGURA, time);
            n = moveInimigo(&inimigos[i], ALTURA, LARGURA, time);
            if(moveInimigo(&inimigos[i], ALTURA, LARGURA, time ) != 1) redefineDeslocamento(&inimigos[i],n);
            DrawRectangle(inimigos[i].x, inimigos[i].y, ALTURA_BLOCO, LARGURA_BLOCO, ORANGE);
        }

        EndDrawing();

        //printf("%c", mapa[0][0]);
    }

    CloseWindow();
    return 0;
}

void carregaMapa(const char *arquivoMapa, int *ddx, int *ddy, int *bbx,int *bby)//, char mapa[][LARGURA_MAPA])
{
    FILE *file = fopen(arquivoMapa, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo do mapa!\n");
        exit(1);
    }

    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            int caractere = fgetc(file);
            if (caractere == 'W' || caractere == ' ' || caractere == 'J' || caractere == 'M' || caractere == 'H' || caractere == 'R' || caractere == 'S' || caractere == 'D')
            {
                mapa[i][j] = caractere;

            if(caractere == 'M'){
                *ddx = j*LARGURA_BLOCO;
                *ddy = i*ALTURA_BLOCO;
            }
            if(caractere == 'S'){
                *bbx = j*LARGURA_BLOCO;
                *bby = i*ALTURA_BLOCO;
            }

            }
            else if (caractere == '\n')
            {
                j--;
            }
        }
    }
    fclose(file);
}

void DesenhaMapa()//(char mapa[][LARGURA_MAPA])
{
    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            if (mapa[i][j] == 'W')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, GRAY);
            }
            if (mapa[i][j] == 'R')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, GREEN);
            }
            if (mapa[i][j] == 'H')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BLACK);
            }
            if (mapa[i][j] == 'S')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, SKYBLUE);
            }
            if (mapa[i][j] == 'M')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, RED);
            }
            if (mapa[i][j] == 'D')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BROWN);
            }
        }
    }
}


void InitPosicaoJogador(struct pos_J *J)//, char mapa[][LARGURA_MAPA])
{
    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            if (mapa[i][j] == 'J')
            {
                J->x = j * LARGURA_BLOCO;
                J->y = i * ALTURA_BLOCO;
                return;  // Encerra a busca após encontrar a posição inicial do jogador
            }
        }
    }
}

void MovimentoJogador(struct pos_J *J)//, char mapa[][LARGURA_MAPA])
{
    if (IsKeyDown(KEY_UP) && J->y > 0 && mapa[(int)(J->y - 1)/ALTURA_BLOCO][(int)J->x/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y - 1)/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        J->y -= 1;
        printf("Moving up: J.y = %f\n", J->y);
    }
    if (IsKeyDown(KEY_DOWN) && J->y < ((ALTURA_MAPA*ALTURA_BLOCO)-ALTURA_BLOCO) && mapa[(int)(J->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)J->x/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        J->y += 1;
        printf("Moving down: J.y = %f\n", J->y);
    }
    if (IsKeyDown(KEY_LEFT) && J->x > 0 && mapa[(int)J->y/ALTURA_BLOCO][(int)(J->x - 1)/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(J->x - 1)/LARGURA_BLOCO] != 'W' &&  mapa[(int)(J->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(J->x - 1)/LARGURA_BLOCO] != 'D')
    {
        J->x -= 1;
        printf("Moving left: J.x = %f\n", J->x);
    }
    if (IsKeyDown(KEY_RIGHT) && J->x < ((LARGURA_MAPA*LARGURA_BLOCO)-LARGURA_BLOCO) && mapa[(int)J->y/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W' && mapa[(int)(J->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(J->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W')
    {
        J->x += 1;
        printf("Moving right: J.x = %f\n", J->x);
    }
}

void PortaTrancada (struct pos_J *J)//, char mapa[][LARGURA_MAPA])
{
    if(mapa[(int)J->y/ALTURA_BLOCO][(int)J->x/LARGURA_BLOCO] == 'D')
    {
        DrawText("CHAVE PARA PORTA", 200, 200, 50, BLACK);
    }
}

int teste(int ddx,int ddy,int bbx,int bby){
    int x = ddx - bbx;
    int y = ddy - bby;

    if(x >= 0 && y >= 0){    //spawn inimigo a direita e abaixo da base, inimigo quer subir
        if(abs(x)>abs(y)) return 1;    //
        else return 2;
    }
    if(x >= 0 && y <= 0){    //spawn inimigo a direita e acima da base, inimigo quer subir
        if(abs(x)>abs(y)) return 3;
        else return 4;
    }
    if(x <= 0 && y >= 0){    //spawn inimigo a esquerda e abaixo da base, inimigo quer subir
        if(abs(x)>abs(y)) return 5;
        else return 6;
    }
    if(x <= 0 && y <= 0){    //spawn inimigo a esquerda e acima da base, inimigo quer subir
        if(abs(x)>abs(y)) return 7;
        else return 8;
    }
}
