#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 600
#define LARGURA_matriz 60
#define ALTURA_matriz 30

int main(void)
{
    int matriz[ALTURA_matriz][LARGURA_matriz]= {};
    matriz[10][50] = 1;
    matriz[25][10] = 1;

    int y = 300, x = 600;
    int a,n,r=0;
//char texto[50] = {"Recursos: %d",r};//texto inicial
//--------------------------------------------------------------------------------------
//Inicializações
    InitWindow(LARGURA, ALTURA, "Quadrado");//Inicializa janela, com certo tamanho e título
    SetTargetFPS(60);// Ajusta a execução do jogo para 60 frames por segundo
//--------------------------------------------------------------------------------------
//Laço principal do jogo
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Trata entrada do usuário e atualiza estado do jogo
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_D)) x=x+20; //strcpy(texto,"Direita");
        if (IsKeyPressed(KEY_A)) x=x-20 ;//strcpy(texto,"Esquerda");
        if (IsKeyPressed(KEY_W)) y=y-20;//strcpy(texto,"Cima");
        if (IsKeyPressed(KEY_S))y=y+20; //strcpy(texto,"Baixo");

        for(a=0 ; a<ALTURA_matriz ; a++)  //matriz teste
        {
            for(n=0; n<LARGURA_matriz; n++)
            {
                if(matriz[a][n] == 1)
                    DrawRectangle(20*n, 20*a, 20, 20, GREEN);
                if(matriz[a][n] == 0)
                    DrawRectangle(20*n, 20*a, 20, 20, RED);
                if(matriz[a][n] == 2)
                    DrawRectangle(20*n, 20*a, 20, 20, BLACK);
            }
        }

        if(matriz[y/20][x/20]==1)
        {
            r=r+1;
        }

        if(IsKeyPressed(KEY_G))
        {
            if(r>0)
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
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
        //DrawText(texto, 200, 200, 40, GREEN);//Desenha um texto, com posição, tamanho e cor
        EndDrawing();//Finaliza o ambiente de desenho na tela
        //----------------------------------------------------------------------------------
        if(x>1200 || x<0 || y>600 || y<0)
            CloseWindow();
        ShowCursor();
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;
}
