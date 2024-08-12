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


typedef enum GameScreen { LOGO = 0, TITULO, JOGO, OPCOES, FASES, PAUSE} GameScreen;

char mapa[ALTURA_MAPA][LARGURA_MAPA];

typedef struct botao
{
    Rectangle rect;
    Color cor;

} BOTAO;

typedef struct Inimigo
{
    float x,y;
    int dx, dy;
} INIMIGO;

typedef struct pos_J
{
    float x;
    float y;
    float dx, dy;
    int vida;
} JOGADOR;

int vidaBase = 3;

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
                Inimigo++;
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
    if (IsKeyDown(KEY_UP) && Jogador->y > 0 && mapa[(int)(Jogador->y - 1)/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] != 'W' &&
            mapa[(int)(Jogador->y - 1)/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        Jogador->dy = -1;
        printf("Moving up: J.y = %f\n", Jogador->y);
    }
    if (IsKeyDown(KEY_DOWN) && Jogador->y < ((ALTURA_MAPA*ALTURA_BLOCO)-ALTURA_BLOCO) &&
            mapa[(int)(Jogador->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] != 'W' &&
            mapa[(int)(Jogador->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] != 'W')
    {
        Jogador->dy = 1;
        printf("Moving down: J.y = %f\n", Jogador->y);
    }
    if (IsKeyDown(KEY_LEFT) && Jogador->x > 0 && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)(Jogador->x - 1)/LARGURA_BLOCO] != 'W' &&
            mapa[(int)(Jogador->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Jogador->x - 1)/LARGURA_BLOCO] != 'W' &&
            mapa[(int)(Jogador->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Jogador->x - 1)/LARGURA_BLOCO] != 'D')
    {
        Jogador->dx = -1;
        printf("Moving left: J.x = %f\n", Jogador->x);
    }
    if (IsKeyDown(KEY_RIGHT) && Jogador->x < ((LARGURA_MAPA*LARGURA_BLOCO)-LARGURA_BLOCO) && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W' && mapa[(int)(Jogador->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Jogador->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W')
    {
        Jogador->dx = 1;
        printf("Moving right: J.x = %f\n", Jogador->x);
    }
    if(IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT))
    {
        Jogador->dx = 0;
    }
    if(IsKeyDown(KEY_UP) && IsKeyDown(KEY_DOWN))
    {
        Jogador->dy = 0;
    }

    Jogador->x += Jogador->dx * 2;
    Jogador->y += Jogador->dy * 2;

    if(Jogador->dx == -1 && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] == 'H')
    {
        for(int i = (Jogador->x - 1)/LARGURA_BLOCO; i > 0; i--)
        {
            if(mapa[(int)Jogador->y/ALTURA_BLOCO][i] == 'H')
                Jogador->x = i * LARGURA_BLOCO;
        }
    }

    if(Jogador->dx == 1 && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] == 'H')
    {
        for(int i = (Jogador->x +LARGURA_BLOCO)/LARGURA_BLOCO; i < LARGURA_MAPA; i++)
        {
            if(mapa[(int)Jogador->y/ALTURA_BLOCO][i] == 'H')
                Jogador->x = i * LARGURA_BLOCO;
        }
    }

    if(Jogador->dy == -1 && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] == 'H')
    {
        for(int i = (Jogador->y - 1)/ALTURA_BLOCO; i > 0; i--)
        {
            if(mapa[i][(int)Jogador->x/LARGURA_BLOCO] == 'H')
                Jogador->y = i * ALTURA_BLOCO;
        }
    }

    if(Jogador->dy == 1 && mapa[(int)Jogador->y/ALTURA_BLOCO][(int)Jogador->x/LARGURA_BLOCO] == 'H')
    {
        for(int i = (Jogador->y + ALTURA_BLOCO)/ALTURA_BLOCO; i < ALTURA_MAPA; i++)
        {
            if(mapa[i][(int)Jogador->x/ALTURA_BLOCO] == 'H')
                Jogador->y = i * ALTURA_BLOCO;
        }
    }

    Jogador->dx = 0;
    Jogador->dy = 0;

}

void MovimentoInimigo(INIMIGO *Inimigo, int TAM, double tempo)
{
    if(fmod(tempo,1.5) < 0.016)
    {

        for(int i = 0; i < TAM; i++)
        {

            if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'W' &&
                    mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'W' ||
                    mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] != 'H' &&
                    mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'H')
                Inimigo->dx++;

            if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] != 'W' &&
                    mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'W' ||
                    mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] != 'H' &&
                    mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'H')
                Inimigo->dx--;

            if(mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'W' &&
                    mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] != 'W' ||
                    mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] != 'H' &&
                    mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'H')
                Inimigo->dy++;

            if(mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] != 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'W' || mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] != 'H' && mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'H')
                Inimigo->dy--;


            Inimigo->y += Inimigo->dy * 20;
            printf("Inimigo.dy = %d\n", Inimigo->dy);

            Inimigo->x += Inimigo->dx * 20;
            printf("Inimigo.dx = %d\n", Inimigo->dx);

            Inimigo++;

        }

    }
}

void DesenhaInimigo(INIMIGO *Inimigo, int TAM)
{
    for(int i = 0; i < TAM; i++)
    {
        DrawRectangle(Inimigo->x, Inimigo->y, LARGURA_BLOCO, ALTURA_BLOCO, RED);
        Inimigo++;
    }
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

bool botaopress(BOTAO botao)
{
    return CheckCollisionPointRec(GetMousePosition(), botao.rect);
}

void VidaJogador(JOGADOR *Jogador, INIMIGO *Inimigo, int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        if (fabs(Jogador->x - Inimigo->x) < LARGURA_BLOCO/2 && fabs(Jogador->y - Inimigo->y) < ALTURA_BLOCO/2)
        {
            Jogador->vida--;
        }
        Inimigo++;
    }

    if(Jogador->vida <= 0)
    {
        CloseWindow();
    }
}

void VidaBase(INIMIGO *Inimigo, int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'S')
        {
            vidaBase--;
        }
        Inimigo++;
    }

    if(vidaBase <= 0)
    {
        CloseWindow();
    }

    char textoVidasBase[20];
    sprintf(textoVidasBase, "Vidas da base: %d", vidaBase);
    DrawText(textoVidasBase, 100, 200, 50, ORANGE);
}





int main(void)
{
    double tempo = 0;

    BOTAO botaoNOVOJ = {0}, botaoCARREGAR = {0}, botaoSAIR = {0}, botaoFASE1 = {0}, botaoFASE2 = {0}, botaoFASE3 = {0}, botaoFASE4 = {0};
    BOTAO botaoCONT = {0}, botaoCARREGAR2 = {0}, botaoSALVAR = {0}, botaoVOLTAR = {0}, botaoSAIR2 = {0};
    JOGADOR Jogador = {0.0, 0.0};  // Inicializa a posi��o de J
    Jogador.vida = 1;
    INIMIGO Inimigo[5];
    //char mapa[11]


    GameScreen currentScreen = LOGO;

    int framesCounter = 0;


    SetTargetFPS(60);


    //carregaMapa("mapa1.txt");

    //InitPosicaoJogador(&Jogador);

    //for(int i=0; i<5; i++)
    //InitPosicaoInimigo(&Inimigo[i]);

    //for(int i=0; i<5; i++)
    //printf("%f %f\n",Inimigo[i].x, Inimigo[i].y);




    InitWindow(LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, "TowerDefense");

    IniciaBotao(&botaoNOVOJ,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 200,200,100
    }, YELLOW);
    IniciaBotao(&botaoCARREGAR,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 50,200,100
    }, YELLOW);
    IniciaBotao(&botaoSAIR,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 + 100,200,100
    }, YELLOW);

    IniciaBotao(&botaoFASE1,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 300, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 200,200,100
    }, YELLOW);
    IniciaBotao(&botaoFASE2,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 + 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 200,200,100
    }, YELLOW);
    IniciaBotao(&botaoFASE3,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 300, (ALTURA_MAPA * ALTURA_BLOCO)/2 + 100,200,100
    }, YELLOW);
    IniciaBotao(&botaoFASE4,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 + 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 + 100,200,100
    }, YELLOW);


    IniciaBotao(&botaoCONT,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 240,200,80
    }, YELLOW);
    IniciaBotao(&botaoCARREGAR2,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 140,200,80
    }, YELLOW);
    IniciaBotao(&botaoSALVAR,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 40,200,80
    }, YELLOW);
    IniciaBotao(&botaoVOLTAR,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 + 60,200,80
    }, YELLOW);
    IniciaBotao(&botaoSAIR2,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 + 160,200,80
    }, YELLOW);




    while (!WindowShouldClose())
    {
        tempo = GetTime();

        BeginDrawing();



        //PortaTrancada(&Jogador);
        switch(currentScreen)
        {
        case LOGO:
        {
            // TODO: Update LOGO screen variables here!

            framesCounter++;    // Count frames

            // Wait for 2 seconds (120 frames) before jumping to TITLE screen
            if (framesCounter > 300)
            {
                currentScreen = TITULO;
            }
        }
        break;
        case TITULO:
        {
            // TODO: Update TITLE screen variables here!

            // Press enter to change to GAMEPLAY screen
            //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            //{
            //    currentScreen = GAMEPLAY;
            //
            if(botaopress(botaoNOVOJ)) botaoNOVOJ.cor = WHITE;
            else botaoNOVOJ.cor = YELLOW;

            if(botaopress(botaoNOVOJ) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = FASES;
            }

            if(botaopress(botaoCARREGAR)) botaoCARREGAR.cor = WHITE;
            else botaoCARREGAR.cor = YELLOW;

            if(botaopress(botaoCARREGAR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //Carregar jogo salvo
                currentScreen = JOGO;
            }

            if(botaopress(botaoSAIR)) botaoSAIR.cor = WHITE;
            else botaoSAIR.cor = YELLOW;

            if(botaopress(botaoSAIR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                CloseWindow();
            }


        }
        break;
        case JOGO:
        {
            // TODO: Update GAMEPLAY screen variables here!

            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_TAB))
            {
                currentScreen = PAUSE;
            }
        }
        break;
        case OPCOES:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = TITULO;
            }
        }
        break;
        case FASES:
        {
            if(botaopress(botaoFASE1)) botaoFASE1.cor = WHITE;
            else botaoFASE1.cor = YELLOW;

            if(botaopress(botaoFASE1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa1.txt");
                InitPosicaoJogador(&Jogador);

                InitPosicaoInimigo(Inimigo);

                currentScreen = JOGO;

            }

            if(botaopress(botaoFASE2)) botaoFASE2.cor = WHITE;
            else botaoFASE2.cor = YELLOW;

            if(botaopress(botaoFASE2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa2.txt");
                InitPosicaoJogador(&Jogador);
                for(int i=0; i<5; i++)
                    InitPosicaoInimigo(&Inimigo[i]);
                currentScreen = JOGO;
            }


            if(botaopress(botaoFASE3)) botaoFASE3.cor = WHITE;
            else botaoFASE3.cor = YELLOW;

            if(botaopress(botaoFASE3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa3.txt");
                InitPosicaoJogador(&Jogador);

                //     int num = InitPosicaoInimigo(&Inimigo);


                currentScreen = JOGO;
            }

            if(botaopress(botaoFASE4)) botaoFASE4.cor = WHITE;
            else botaoFASE4.cor = YELLOW;

            if(botaopress(botaoFASE4) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa4.txt");
                InitPosicaoJogador(&Jogador);
                for(int i=0; i<5; i++)
                    InitPosicaoInimigo(&Inimigo[i]);
                currentScreen = JOGO;
            }

            //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            //{
            //    currentScreen = OPCOES;
            //}
        }
        break;
        case PAUSE:
        {
            // TODO: Update GAMEPLAY screen variables here!

            if(botaopress(botaoCONT)) botaoCONT.cor = WHITE;
            else botaoCONT.cor = YELLOW;

            if(botaopress(botaoCONT) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = JOGO;
            }

            if(IsKeyPressed(KEY_TAB))
            {
                currentScreen = JOGO;
            }

            if(botaopress(botaoCARREGAR2)) botaoCARREGAR2.cor = WHITE;
            else botaoCARREGAR2.cor = YELLOW;

            if(botaopress(botaoCARREGAR2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //carregar jogo salvo
                currentScreen = JOGO;
            }

            if(botaopress(botaoSALVAR)) botaoSALVAR.cor = WHITE;
            else botaoSALVAR.cor = YELLOW;

            if(botaopress(botaoSALVAR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva estado atual do jogo
                //currentScreen = OPCOES;
            }

            if(botaopress(botaoVOLTAR)) botaoVOLTAR.cor = WHITE;
            else botaoVOLTAR.cor = YELLOW;

            if(botaopress(botaoVOLTAR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = TITULO;
            }

            if(botaopress(botaoSAIR2)) botaoSAIR2.cor = WHITE;
            else botaoSAIR2.cor = YELLOW;

            if(botaopress(botaoSAIR2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                CloseWindow();
            }

            // Press enter to change to ENDING screen

        }
        break;
        default:
            break;
        }
        switch(currentScreen)
        {
        case LOGO:
        {
            // TODO: Draw LOGO screen here!
            ClearBackground(DARKBLUE);
            DrawText("MEIA BOCA JUNIORS", 280, 250, 60, YELLOW);
            //     DrawText("WAIT for 2 SECONDS...", 290, 220, 20, YELLOW);

        }
        break;
        case TITULO:
        {
            // TODO: Draw TITLE screen here!
            DrawRectangle(0, 0, LARGURA_MAPA * LARGURA_BLOCO, ALTURA_MAPA * ALTURA_BLOCO, DARKBLUE);
            //DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            //DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
            DrawRectangleRec(botaoNOVOJ.rect, botaoNOVOJ.cor);
            DrawText("NOVO JOGO", botaoNOVOJ.rect.x + botaoNOVOJ.rect.width/2 - MeasureText("NOVO JOGO",20)/2, botaoNOVOJ.rect.y + botaoNOVOJ.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoCARREGAR.rect, botaoCARREGAR.cor);
            DrawText("CARREGAR JOGO", botaoCARREGAR.rect.x + botaoCARREGAR.rect.width/2 - MeasureText("CARREGAR JOGO",20)/2, botaoCARREGAR.rect.y + botaoCARREGAR.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAIR.rect, botaoSAIR.cor);
            DrawText("SAIR", botaoSAIR.rect.x + botaoSAIR.rect.width/2 - MeasureText("SAIR",20)/2, botaoSAIR.rect.y + botaoSAIR.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        case JOGO:
        {
            // TODO: Draw GAMEPLAY screen here!

            ClearBackground(RAYWHITE);
            DesenhaMapa();


            DesenhaInimigo(Inimigo, 5);

            DrawRectangle(Jogador.x, Jogador.y, LARGURA_BLOCO, ALTURA_BLOCO, DARKBLUE);

            MovimentoJogador(&Jogador);

            MovimentoInimigo(Inimigo, 5, tempo);

            VidaJogador(&Jogador, Inimigo, 5);

            //      VidaBase(Inimigo, 5);

        }
        break;
        case OPCOES:
        {
            ClearBackground(DARKBLUE);
            DrawText("OPCOES", 30, 30, 40, WHITE);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);


        }
        break;
        case FASES:
        {
            ClearBackground(DARKBLUE);
            DrawRectangleRec(botaoFASE1.rect, botaoFASE1.cor);
            DrawText("FASE 1", botaoFASE1.rect.x + botaoFASE1.rect.width/2 - MeasureText("FASE 1",20)/2, botaoFASE1.rect.y + botaoFASE1.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoFASE2.rect, botaoFASE2.cor);
            DrawText("FASE 2", botaoFASE2.rect.x + botaoFASE2.rect.width/2 - MeasureText("FASE 2",20)/2, botaoFASE2.rect.y + botaoFASE2.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoFASE3.rect, botaoFASE3.cor);
            DrawText("FASE 3", botaoFASE3.rect.x + botaoFASE3.rect.width/2 - MeasureText("FASE 3",20)/2, botaoFASE3.rect.y + botaoFASE3.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoFASE4.rect, botaoFASE4.cor);
            DrawText("FASE 4", botaoFASE4.rect.x + botaoFASE4.rect.width/2 - MeasureText("FASE 4",20)/2, botaoFASE4.rect.y + botaoFASE4.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        case PAUSE:
        {
            ClearBackground(DARKBLUE);
            DrawText("OPÇÕES", 30, 30, 80, WHITE);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
            DrawRectangleRec(botaoCONT.rect, botaoCONT.cor);
            DrawText("CONTINUAR", botaoCONT.rect.x + botaoCONT.rect.width/2 - MeasureText("CONTINUAR",20)/2, botaoCONT.rect.y + botaoCONT.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoCARREGAR2.rect, botaoCARREGAR2.cor);
            DrawText("CARREGAR", botaoCARREGAR2.rect.x + botaoCARREGAR2.rect.width/2 - MeasureText("CARREGAR",20)/2, botaoCARREGAR2.rect.y + botaoCARREGAR2.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSALVAR.rect, botaoSALVAR.cor);
            DrawText("SALVAR", botaoSALVAR.rect.x + botaoSALVAR.rect.width/2 - MeasureText("SALVAR",20)/2, botaoSALVAR.rect.y + botaoSALVAR.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoVOLTAR.rect, botaoVOLTAR.cor);
            DrawText("VOLTAR", botaoVOLTAR.rect.x + botaoVOLTAR.rect.width/2 - MeasureText("VOLTAR",20)/2, botaoVOLTAR.rect.y + botaoVOLTAR.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAIR2.rect, botaoSAIR2.cor);
            DrawText("SAIR SEM SALVAR", botaoSAIR2.rect.x + botaoSAIR2.rect.width/2 - MeasureText("SAIR SEM SALVAR",20)/2, botaoSAIR2.rect.y + botaoSAIR2.rect.height/2 - 20/2,20, BLACK);
        }
        break;
        default:
            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
