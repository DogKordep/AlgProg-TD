#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
//#include "funcoes.h"

#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED
#define NUM_FRAMES 3



#endif // FUNCOES_H_INCLUDED

#define ALTURA_MAPA 30
#define LARGURA_MAPA 60

#define ALTURA_BLOCO 20
#define LARGURA_BLOCO 20

#define TAM_POPUP 200

typedef enum GameScreen { LOGO = 0, TITULO, JOGO, OPCOES} GameScreen;

char mapa[ALTURA_MAPA][LARGURA_MAPA];

typedef struct botao{
    Rectangle rect;
    Color cor;

}BOTAO;

typedef struct Inimigo
{
    float x,y;
    int dx, dy;
} INIMIGO;

typedef struct pos_J
{
    float x;
    float y;
} JOGADOR;

void carregaMapa(const char *arquivoMapa)
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
            }
            else if (caractere == '\n')
            {
                j--;
            }
        }
    }
    fclose(file);
}

void DesenhaMapa()
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
            /* if (mapa[i][j] == 'M')
             {
                 DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, RED);
             }*/
            if (mapa[i][j] == 'D')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BROWN);
            }
        }
    }
}

int InitPosicaoInimigo(INIMIGO *Inimigo)
{
    int n=0;

    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {

            if (mapa[i][j] == 'M')
            {

                Inimigo->x = j * LARGURA_BLOCO;
                Inimigo->y = i * ALTURA_BLOCO;
                Inimigo->dx = -1;
                Inimigo->dy = 0;
                //Inimigo++;
                n++;
            }
        }
    }
    return n;

}

void InitPosicaoJogador(JOGADOR *Jogador)
{
    for (int i = 0; i < ALTURA_MAPA; i++)
    {
        for (int j = 0; j < LARGURA_MAPA; j++)
        {
            if (mapa[i][j] == 'J')
            {
                Jogador->x = j * LARGURA_BLOCO;
                Jogador->y = i * ALTURA_BLOCO;
                return;  // Encerra a busca ap�s encontrar a posi��o inicial do jogador
            }
        }
    }
}

void MovimentoJogador(JOGADOR *Jogador)
{
    if (IsKeyDown(KEY_UP) && Jogador->y > 0 && mapa[(int)(Jogador->y - 1)/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] != 'W' && mapa[(int)(Jogador->y - 1)/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        Jogador->y -= 1;
        printf("Moving up: J.y = %f\n", Jogador->y);
    }
    if (IsKeyDown(KEY_DOWN) && Jogador->y < ((ALTURA_MAPA*ALTURA_BLOCO)-ALTURA_BLOCO) && mapa[(int)(Jogador->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] != 'W' && mapa[(int)(Jogador->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        Jogador->y += 1;
        printf("Moving down: J.y = %f\n", Jogador->y);
    }
    if (IsKeyDown(KEY_LEFT) && Jogador->x > 0 && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)(Jogador->x - 1)/LARGURA_BLOCO] != 'W' && mapa[(int)(Jogador->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Jogador->x - 1)/LARGURA_BLOCO] != 'W' &&  mapa[(int)(Jogador->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Jogador->x - 1)/LARGURA_BLOCO] != 'D')
    {
        Jogador->x -= 1;
        printf("Moving left: J.x = %f\n", Jogador->x);
    }
    if (IsKeyDown(KEY_RIGHT) && Jogador->x < ((LARGURA_MAPA*LARGURA_BLOCO)-LARGURA_BLOCO) && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W' && mapa[(int)(Jogador->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W')
    {
        Jogador->x += 1;
        printf("Moving right: J.x = %f\n", Jogador->x);
    }

}

void MovimentoInimigo(INIMIGO *Inimigo, int TAM)
{

    //for(int i = 0; i < TAM; i++)
    //{

        if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'W' && mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W' || mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'H' && mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'H')
            Inimigo->dx++;

        if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] != 'W' && mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'W' || mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] != 'H' && mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'H')
            Inimigo->dx--;

        if(mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] != 'W' || mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] != 'H' && mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'H')
            Inimigo->dy++;

        if(mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] != 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'W' || mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] != 'H' && mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'H')
            Inimigo->dy--;


        Inimigo->y += Inimigo->dy*20;
        printf("Inimigo.dy %d = %d\n", Inimigo, Inimigo->dy);

        Inimigo->x += Inimigo->dx*20;
        printf("Inimigo.dx = %d\n", Inimigo->dx);

        //Inimigo++;

    //}

}

void DesenhaInimigo(INIMIGO *Inimigo, int TAM)
{
    //for(int i = 0; i < TAM; i++)
    //{
        DrawRectangle(Inimigo->x, Inimigo->y, LARGURA_BLOCO, ALTURA_BLOCO, RED);
        //Inimigo++;
    //}
}
void PortaTrancada (JOGADOR *Jogador)
{
    if(mapa[(int)Jogador->y/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] == 'D')
    {
        DrawText("CHAVE PARA PORTA", 200, 200, 50, BLACK);
    }
}

void IniciaBotao(BOTAO *botao, Rectangle rect, Color cor)
{
    botao->rect = rect;
    botao->cor = cor;
}

bool botaopress(BOTAO botao){
    return CheckCollisionPointRec(GetMousePosition(), botao.rect);
}



int main(void)
{
    BOTAO botao1 = {0}, botao2 = {0};
    JOGADOR Jogador = {0.0, 0.0};  // Inicializa a posi��o de J
    INIMIGO Inimigo[5];

    GameScreen currentScreen = LOGO;

    int framesCounter = 0;


    SetTargetFPS(60);


    carregaMapa("mapa1.txt");

    InitPosicaoJogador(&Jogador);

    for(int i=0; i<5; i++)
    InitPosicaoInimigo(&Inimigo[i]);

    for(int i=0; i<5; i++)
    printf("%f %f\n",Inimigo[i].x, Inimigo[i].y);




    InitWindow(LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, "TowerDefense");

    IniciaBotao(&botao1,(Rectangle){(LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 50,200,100}, RED);
    IniciaBotao(&botao2,(Rectangle){(LARGURA_MAPA * LARGURA_BLOCO)/2 - 100 , (ALTURA_MAPA * ALTURA_BLOCO)/2 + 100,200,100}, RED);


    while (!WindowShouldClose())
    {


        //PortaTrancada(&Jogador);
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITULO;
                }
            } break;
            case TITULO:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                //{
                //    currentScreen = GAMEPLAY;
                //
                if(botaopress(botao1)) botao1.cor = BLUE;
                else botao1.cor = RED;

                if(botaopress(botao1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currentScreen = JOGO;
                }

                if(botaopress(botao2)) botao2.cor = BLUE;
                else botao2.cor = RED;

                if(botaopress(botao2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currentScreen = OPCOES;
                }

            } break;
            case JOGO:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                //{
                //    currentScreen = ENDING;
                //}
            } break;
            case OPCOES:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITULO;
                }
            } break;
            default: break;
        }
        switch(currentScreen)
            {
                BeginDrawing();
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    ClearBackground(BLUE);
                    DrawText("MEIA BOCA JR", 300, 300, 60, YELLOW);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, YELLOW);

                } break;
                case TITULO:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
                    DrawRectangleRec(botao1.rect, botao1.cor);
                    DrawText("JOGAR", botao1.rect.x + botao1.rect.width/2 - MeasureText("JOGAR",20)/2, botao1.rect.y + botao1.rect.height/2 - 20/2,20, WHITE);
                    DrawRectangleRec(botao2.rect, botao2.cor);
                    DrawText("OPCOES", botao2.rect.x + botao2.rect.width/2 - MeasureText("OPCOES",20)/2, botao2.rect.y + botao2.rect.height/2 - 20/2,20, WHITE);


                } break;
                case JOGO:
                {
                    // TODO: Draw GAMEPLAY screen here!

                    ClearBackground(RAYWHITE);
                    DesenhaMapa();
                    for(int i=0; i<5; i++)
                        DrawRectangle(Inimigo[i].x, Inimigo[i].y, LARGURA_BLOCO, ALTURA_BLOCO, RED);
                    //DesenhaInimigo(&Inimigo[i], 5);
                    DrawRectangle(Jogador.x, Jogador.y, LARGURA_BLOCO, ALTURA_BLOCO, DARKBLUE);

                    MovimentoJogador(&Jogador);
                    for(int i=0; i<5; i++)
                        MovimentoInimigo(&Inimigo[i], 5);
                } break;
                case OPCOES:
                {
                    ClearBackground(RAYWHITE);
                    DrawText("OPCOES", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);


                } break;
                default: break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}



