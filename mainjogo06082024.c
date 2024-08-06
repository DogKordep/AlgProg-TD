#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
#include "funcoes.h"

int main(void)
{
    JOGADOR Jogador = {0.0, 0.0};  // Inicializa a posição de J
    INIMIGO Inimigo[5];

    InitWindow(LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, "TowerDefense");
    SetTargetFPS(60);

    carregaMapa("mapa1.txt");

    InitPosicaoJogador(&Jogador);

    InitPosicaoInimigo(&Inimigo);

    for(int i=0; i<5; i++)
    printf("%f %f\n",Inimigo[i].x, Inimigo[i].y);


    while (!WindowShouldClose())
    {

        MovimentoJogador(&Jogador);
        MovimentoInimigo(&Inimigo, 5);

        PortaTrancada(&Jogador);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DesenhaMapa();
        DesenhaInimigo(&Inimigo, 5);
        DrawRectangle(Jogador.x, Jogador.y, LARGURA_BLOCO, ALTURA_BLOCO, DARKBLUE);



        EndDrawing();
    }

    CloseWindow();

    return 0;
}

