  #include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 600
#define LARGURA_matriz 60
#define ALTURA_matriz 30

int deveMover(int x, int y, int dx, int dy, int larg, int alt)
{

    if(x+20*dx > (larg-20)) return 0;
    if(x+20*dx < 0) return 0;
    if(y-20*dy > (alt-20)) return 0;
    if(y-20*dy < 0) return 0;
    return 1;
}

void move(int dx, int dy, int *x, int *y)
{
    *x+=dx*20;
    *y-=dy*20;
}

//typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
int main(void)
{
    //GameScreen currentScreen = LOGO;
    int matriz[ALTURA_matriz][LARGURA_matriz]= {};
    matriz[10][50] = 1;
    matriz[25][10] = 1;
    //int framesCounter = 0;

    int y = 300, x = 600, y2 = 300, x2 = 600;
    int a,n,r=0,dx=0,dy=0;
    int dx2 = GetRandomValue(-1, 1);
    int dy2 = GetRandomValue(-1, 1);
//char texto[50] = {"Recursos: %d",r};//texto inicial
//--------------------------------------------------------------------------------------
//Inicializações
    InitWindow(LARGURA, ALTURA, "Quadrado");//Inicializa janela, com certo tamanho e título
    SetTargetFPS(60);// Ajusta a execução do jogo para 60 frames por segundo
//--------------------------------------------------------------------------------------
//Laço principal do jogo



    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);


    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ClearBackground(RAYWHITE);
        // Trata entrada do usuário e atualiza estado do jogo
        dx2 = GetRandomValue(-1, 1);
        dy2 = GetRandomValue(-1, 1);
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_D))  dx =  1;//x=x+20; //strcpy(texto,"Direita");
        if (IsKeyPressed(KEY_A))  dx = -1; //x=x-20 ;//strcpy(texto,"Esquerda");
        if (IsKeyPressed(KEY_W))  dy =  1; //y=y-20;//strcpy(texto,"Cima");
        if (IsKeyPressed(KEY_S))  dy = -1; //y=y+20; //strcpy(texto,"Baixo");

        if (deveMover(x,y,dx,dy,LARGURA,ALTURA)) move(dx,dy,&x,&y);
        if (deveMover(x2,y2,dx2,dy2,LARGURA,ALTURA)) move(dx2,dy2,&x2,&y2);

        for(a=0 ; a<ALTURA_matriz ; a++)  //matriz teste
        {
            for(n=0; n<LARGURA_matriz; n++)
            {
                if(matriz[a][n] == 1)
                    DrawRectangle(20*n, 20*a, 20, 20, GREEN);
                if(matriz[a][n] == 0)
                    DrawRectangle(20*n, 20*a, 20, 20, BLACK);
                if(matriz[a][n] == 2)
                    DrawRectangle(20*n, 20*a, 20, 20, WHITE);

            }
        }

        if(matriz[y/20][x/20]==1)
        {
            r=r+1;
            //WaitTime(0.05);
            matriz[y/20][x/20]=0;

        }

        if(IsKeyPressed(KEY_G))
        {
            if(r>0 && matriz[y/20][x/20]==0)
            {
                matriz[y/20][x/20] = 2;
                r=r-1;
            }
        }
        printf("Recursos: %d\n",r);
        //----------------------------------------------------------------------------------
        // Atualiza a representação visual a partir do estado do jogo
        //----------------------------------------------------------------------------------
        BeginDrawing();//Inicia o ambiente de desenho na tela
        DrawRectangle(x, y, 20, 20, GREEN);
        DrawRectangle(x2,y2, 20, 20, RED);
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
        //DrawText(texto, 200, 200, 40, GREEN);//Desenha um texto, com posição, tamanho e cor
        EndDrawing();//Finaliza o ambiente de desenho na tela
        //----------------------------------------------------------------------------------
        dx = 0;
        dy = 0;
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL

    return 0;
}


void tela()
{

}
