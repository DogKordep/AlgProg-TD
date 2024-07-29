#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
#include "funcoes.h"

int main(void)
{
    struct pos_J J = {0.0, 0.0};  // Inicializa a posição de J

    InitWindow(LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, "TowerDefense");
    SetTargetFPS(60);

    carregaMapa("mapa1.txt");
    InitPosicaoJogador(&J);

    while (!WindowShouldClose())
    {

        MovimentoJogador(&J);

        PortaTrancada(&J);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DesenhaMapa();
        DrawRectangle(J.x, J.y, LARGURA_BLOCO, ALTURA_BLOCO, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

