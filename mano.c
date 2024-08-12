//inclusão de bibliotecas utilizados no codigo
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
//declaração de constantes utilizadas pelo codigo
#define ALTURA_MAPA 30
#define LARGURA_MAPA 60
#define ALTURA_BLOCO 20
#define LARGURA_BLOCO 20

char mapa[ALTURA_MAPA][LARGURA_MAPA];
int vidaBase = 3;

//---------enumeração para facil controle de telas--------------//

typedef enum GameScreen { LOGO = 0, TITULO, JOGO, FASES, PAUSE, SALVA,CARREGA, GAMEOVER, FASE_GANHA, FIM} GameScreen;

//-----------criando estruturas para o codigo---------------//

typedef struct botao
{
    Rectangle rect;
    Color cor;

} BOTAO;

typedef struct Inimigo
{
    float x,y;
    int dx, dy;
    int vida;
}INIMIGO;

typedef struct pos_J
{
    float x;
    float y;
    float dx, dy;
    int vida;
    int recurso;
} JOGADOR;

//------função que recebe como parametro um nome de um arquivo txt, abre o arquivo e o tranfere para um matriz de char que será utilizada no logica do codigo------//
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

//--------função que utiliza o matriz criada na função carregaMapa e desanha o mapa-----------//
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
             if (mapa[i][j] == 'O')
             {
                 DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BROWN);
             }
            if (mapa[i][j] == 'D')
            {
                DrawRectangle(j * LARGURA_BLOCO, i * ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO, BROWN);
            }
        }
    }
}

//-------função que reconhece posição inicial de cada inimigo a partir de informações da //matriz gerada pela função carregaMapa---------//
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
                Inimigo->vida = 1;
                Inimigo++;
                n++;
            }
        }
    }
    return n;
}

//-------função que reconhece posição inicial do jogador a partir de informações da matriz gerada pela função carregaMapa-------//
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

// função com a logica de movimentação do personagem jogavel
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

    if(mapa[(int)(Jogador->y)/ALTURA_BLOCO][(int)(Jogador->x)/LARGURA_BLOCO] == 'R')
        {
            Jogador->recurso++;
            mapa[(int)(Jogador->y)/ALTURA_BLOCO][(int)(Jogador->x)/LARGURA_BLOCO] = ' ';
        }
    Jogador->dx = 0;
    Jogador->dy = 0;
}

//--------------função com a logica de movimentação dos inimigos----------------//
void MovimentoInimigo(INIMIGO *Inimigo, int TAM, double tempo)
{
    if(fmod(tempo,0.1) < 0.016)
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

            if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'O'){
                Inimigo->vida--;
                mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] = ' ';
            }
            Inimigo++;
        }
    }
}

//---------função para desenhar o inimigo----------------//
void DesenhaInimigo(INIMIGO *Inimigo, int TAM)
{
    for(int i = 0; i < TAM; i++)
    {
        if(Inimigo->vida==1)
        DrawRectangle(Inimigo->x, Inimigo->y, LARGURA_BLOCO, ALTURA_BLOCO, RED);
        Inimigo++;
    }
}

//-----------função Iniciabotão, função void que recebe como parametro um tamanho de um retangulo e uma cor e então cria um botão-----------//
void IniciaBotao(BOTAO *botao, Rectangle rect, Color cor)
{
    botao->rect = rect;
    botao->cor = cor;
}

//---------função botaopress é uma função do tipo booleana que reconhece o mouse emcima do botao-------------//
bool botaopress(BOTAO botao)
{
    return CheckCollisionPointRec(GetMousePosition(), botao.rect);
}

//-----que reconhece se o jogador tocou um inimigo e recebeu dano ------//
void VidaJogador(JOGADOR *Jogador, INIMIGO *Inimigo, int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        if (fabs(Jogador->x - Inimigo->x) < LARGURA_BLOCO/2 && fabs(Jogador->y - Inimigo->y) < ALTURA_BLOCO/2)
        {
            if(Inimigo->vida == 1)
                Jogador->vida--;
        }
        Inimigo++;
    }
}

//----função que reconhece se algum inimigo alcançou a base------//
void VidaBase(INIMIGO *Inimigo, int TAM)
{
    for(int i=0; i<TAM; i++)
    {
        if(mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x)/LARGURA_BLOCO] == 'S' && Inimigo->vida==1)
        {
            vidaBase--;
            Inimigo->vida--;
        }
        Inimigo++;
    }

    char textoVidasBase[20];
    sprintf(textoVidasBase, "Vidas da base: %d", vidaBase);
    DrawText(textoVidasBase, 100, 200, 50, ORANGE);
}


int main(void)
{
//--------------Criando variaves do tipo struct BOTAO para criar os botoes do jogo----------------//

    BOTAO botaoNOVOJ = {0}, botaoCARREGAR = {0}, botaoSAIR = {0}, botaoFASE1 = {0}, botaoFASE2 = {0}, botaoFASE3 = {0}, botaoFASE4 = {0};
    BOTAO botaoCONT = {0}, botaoCARREGAR2 = {0}, botaoSALVAR = {0}, botaoVOLTAR = {0}, botaoSAIR2 = {0};
    BOTAO botaoSAVE1 = {0}, botaoSAVE2 = {0}, botaoSAVE3 = {0}, botaoSAVE4 = {0};

//---------------variaveis diversas-------------------//

    JOGADOR Jogador = {0.0, 0.0};  // Inicializa a posi��o de J
    Jogador.vida = 1;
    INIMIGO Inimigo[5];
    double tempo = 0;
    GameScreen currentScreen = LOGO;
    int framesCounter = 0;

//----------------setando FPS e tamanhho da janela do jogo-------------------//

    SetTargetFPS(60);

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


    IniciaBotao(&botaoSAVE1,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 300, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 200,200,80
    }, YELLOW);
    IniciaBotao(&botaoSAVE2,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 + 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 - 200,200,80
    }, YELLOW);
    IniciaBotao(&botaoSAVE3,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 - 300, (ALTURA_MAPA * ALTURA_BLOCO)/2 +100,200,80
    }, YELLOW);
    IniciaBotao(&botaoSAVE4,(Rectangle)
    {
        (LARGURA_MAPA * LARGURA_BLOCO)/2 + 100, (ALTURA_MAPA * ALTURA_BLOCO)/2 + 100,200,80
    }, YELLOW);

//--------------------laço de repetição onde rodará o jogo-----------------------//

    while (!WindowShouldClose())
    {
        tempo = GetTime();   //variavel para controle do tempo

        BeginDrawing();

//--------------switch para controle das variaveis de cada tela individualmente-------------------//

        switch(currentScreen)
        {
        case LOGO:
        {
//---------------tela de logo do grupo------------------------//
            framesCounter++;    // Conta frames

            // espera 2 seconds (120 frames) antes de ir para a janela TITULO
            if (framesCounter > 300)
            {
                currentScreen = TITULO; //transfere para a tela do menu inicial
            }
        }
        break;
        case TITULO:
        {
//---------------------------------tela de menu principal do jogo--------------------------------------------//
            if(botaopress(botaoNOVOJ)) botaoNOVOJ.cor = WHITE;
            else botaoNOVOJ.cor = YELLOW;

            if(botaopress(botaoNOVOJ) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) //botão de criar um novo jogo
            {
                currentScreen = FASES;//transfere para a tela de selecionar fase
            }

            if(botaopress(botaoCARREGAR)) botaoCARREGAR.cor = WHITE; //botão de carregar um jogo salvo
            else botaoCARREGAR.cor = YELLOW;

            if(botaopress(botaoCARREGAR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //Carregar jogo salvo
                currentScreen = CARREGA;//transfere para a tela de selecionar save
                }

            if(botaopress(botaoSAIR)) botaoSAIR.cor = WHITE;  //botão sair do jogo
            else botaoSAIR.cor = YELLOW;

            if(botaopress(botaoSAIR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                CloseWindow();//fecha o jogo
            }


        }
        break;
        case JOGO:
        {
//--------------------o jogo em si, mais datelhas no outro switch case-----------------------//
            if (IsKeyPressed(KEY_TAB))  //se apertar a tecla tab pausa o jogo
            {
                currentScreen = PAUSE;////transfere para a tela de pause
            }
        }
        break;
        case FASES:
        {
//----------------------tela para selecionar fase a ser jogada------------------------//
            if(botaopress(botaoFASE1)) botaoFASE1.cor = WHITE;
            else botaoFASE1.cor = YELLOW;

            if(botaopress(botaoFASE1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa1.txt");
                InitPosicaoJogador(&Jogador);
                InitPosicaoInimigo(Inimigo);
                currentScreen = JOGO;//transfere para a tela de gameplay
            }

            if(botaopress(botaoFASE2)) botaoFASE2.cor = WHITE;
            else botaoFASE2.cor = YELLOW;

            if(botaopress(botaoFASE2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa2.txt");
                InitPosicaoJogador(&Jogador);
                InitPosicaoInimigo(Inimigo);
                currentScreen = JOGO;
            }

            if(botaopress(botaoFASE3)) botaoFASE3.cor = WHITE;
            else botaoFASE3.cor = YELLOW;

            if(botaopress(botaoFASE3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa3.txt");
                InitPosicaoJogador(&Jogador);
                InitPosicaoInimigo(Inimigo);
                currentScreen = JOGO;
            }

            if(botaopress(botaoFASE4)) botaoFASE4.cor = WHITE;
            else botaoFASE4.cor = YELLOW;

            if(botaopress(botaoFASE4) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                carregaMapa("mapa4.txt");
                InitPosicaoJogador(&Jogador);
                InitPosicaoInimigo(Inimigo);
                currentScreen = JOGO;
            }
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
                currentScreen = SALVA;
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
        case GAMEOVER:
        {

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
                //salva estado
                CloseWindow();
            }
        }
        break;
        case SALVA:
        {
            if(botaopress(botaoSAVE1)) botaoSAVE1.cor = WHITE;
            else botaoSAVE1.cor = YELLOW;

            if(botaopress(botaoSAVE1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 1
                currentScreen = PAUSE;
            }

            if(botaopress(botaoSAVE2)) botaoSAVE2.cor = WHITE;
            else botaoSAVE2.cor = YELLOW;

            if(botaopress(botaoSAVE2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 2
                currentScreen = PAUSE;
            }

            if(botaopress(botaoSAVE3)) botaoSAVE3.cor = WHITE;
            else botaoSAVE3.cor = YELLOW;

            if(botaopress(botaoSAVE3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 3
                currentScreen = PAUSE;
            }

            if(botaopress(botaoSAVE4)) botaoSAVE4.cor = WHITE;
            else botaoSAVE4.cor = YELLOW;

            if(botaopress(botaoSAVE4) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 4
                currentScreen = PAUSE;
            }

            if(IsKeyPressed(KEY_TAB))
            {
                currentScreen = JOGO;
            }
        }
        break;
        case FASE_GANHA:
        {
            if(botaopress(botaoVOLTAR)) botaoVOLTAR.cor = WHITE;
            else botaoVOLTAR.cor = YELLOW;

            if(botaopress(botaoVOLTAR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = TITULO;
//CAPETA
            }


        }
        break;
        case FIM:
        {
            if(botaopress(botaoVOLTAR)) botaoVOLTAR.cor = WHITE;
            else botaoVOLTAR.cor = YELLOW;

            if(botaopress(botaoVOLTAR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = TITULO;
            }
        }
        break;
        case CARREGA:
        {
            if(botaopress(botaoSAVE1)) botaoSAVE1.cor = WHITE;
            else botaoSAVE1.cor = YELLOW;

            if(botaopress(botaoSAVE1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 1
                currentScreen = PAUSE;
            }

            if(botaopress(botaoSAVE2)) botaoSAVE2.cor = WHITE;
            else botaoSAVE2.cor = YELLOW;

            if(botaopress(botaoSAVE2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 2
                currentScreen = PAUSE;
            }

            if(botaopress(botaoSAVE3)) botaoSAVE3.cor = WHITE;
            else botaoSAVE3.cor = YELLOW;

            if(botaopress(botaoSAVE3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 3
                currentScreen = PAUSE;
            }

            if(botaopress(botaoSAVE4)) botaoSAVE4.cor = WHITE;
            else botaoSAVE4.cor = YELLOW;

            if(botaopress(botaoSAVE4) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                //salva no slot 4
                currentScreen = PAUSE;
            }
        }
        break;
        default:
            break;
        }

//--------------------switch para desenhar telas e objetos individualmente----------------------//

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

                if(Jogador.vida <= 0)
                {
                    currentScreen = GAMEOVER;
                    Jogador.vida++;
                }
                VidaBase(Inimigo, 5);
                if(vidaBase <= 0)
                {
                    currentScreen = GAMEOVER;
                    vidaBase = 3;
                }

                if(IsKeyPressed(KEY_G) && Jogador.recurso>0){
                    Jogador.recurso--;
                    mapa[(int)(Jogador.y)/ALTURA_BLOCO][(int)(Jogador.x)/LARGURA_BLOCO] = 'O';
                }

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
            DrawText("PAUSE", 30, 30, 80, WHITE);
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
        case GAMEOVER:
        {
            ClearBackground(DARKBLUE);
            DrawText("VOCE MORREU", 300, 200, 80, WHITE);
            DrawRectangleRec(botaoVOLTAR.rect, botaoVOLTAR.cor);
            DrawText("VOLTAR", botaoVOLTAR.rect.x + botaoVOLTAR.rect.width/2 - MeasureText("VOLTAR",20)/2, botaoVOLTAR.rect.y + botaoVOLTAR.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAIR2.rect, botaoSAIR2.cor);
            DrawText("SAIR E SALVAR NO SLOT 1", botaoSAIR2.rect.x + botaoSAIR2.rect.width/2 - MeasureText("SAIR E SALVAR no SLOT 1",20)/2, botaoSAIR2.rect.y + botaoSAIR2.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        case SALVA:
        {
            ClearBackground(DARKBLUE);
            DrawRectangleRec(botaoSAVE1.rect, botaoSAVE1.cor);
            DrawText("SLOT 1", botaoSAVE1.rect.x + botaoSAVE1.rect.width/2 - MeasureText("SLOT 1",20)/2, botaoSAVE1.rect.y + botaoSAVE1.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAVE2.rect, botaoSAVE2.cor);
            DrawText("SLOT 2", botaoSAVE2.rect.x + botaoSAVE2.rect.width/2 - MeasureText("SLOT 2",20)/2, botaoSAVE2.rect.y + botaoSAVE2.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAVE3.rect, botaoSAVE3.cor);
            DrawText("SLOT 3", botaoSAVE3.rect.x + botaoSAVE3.rect.width/2 - MeasureText("SLOT 3",20)/2, botaoSAVE3.rect.y + botaoSAVE3.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAVE4.rect, botaoSAVE4.cor);
            DrawText("SLOT 4", botaoSAVE4.rect.x + botaoSAVE4.rect.width/2 - MeasureText("SLOT 4",20)/2, botaoSAVE4.rect.y + botaoSAVE4.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        case FASE_GANHA:
        {
            ClearBackground(DARKBLUE);
            DrawText("FASE VENCIDA", 300, 200, 80, WHITE);
            DrawRectangleRec(botaoVOLTAR.rect, botaoVOLTAR.cor);
            DrawText("VOLTAR", botaoVOLTAR.rect.x + botaoVOLTAR.rect.width/2 - MeasureText("VOLTAR",20)/2, botaoVOLTAR.rect.y + botaoVOLTAR.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        case FIM:
        {
            ClearBackground(DARKBLUE);
            DrawText("VOCE MORREU", 300, 200, 80, WHITE);
            DrawRectangleRec(botaoVOLTAR.rect, botaoVOLTAR.cor);
            DrawText("VOLTAR", botaoVOLTAR.rect.x + botaoVOLTAR.rect.width/2 - MeasureText("VOLTAR",20)/2, botaoVOLTAR.rect.y + botaoVOLTAR.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        case CARREGA:
        {
            ClearBackground(DARKBLUE);
            DrawRectangleRec(botaoSAVE1.rect, botaoSAVE1.cor);
            DrawText("SLOT 1", botaoSAVE1.rect.x + botaoSAVE1.rect.width/2 - MeasureText("SLOT 1",20)/2, botaoSAVE1.rect.y + botaoSAVE1.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAVE2.rect, botaoSAVE2.cor);
            DrawText("SLOT 2", botaoSAVE2.rect.x + botaoSAVE2.rect.width/2 - MeasureText("SLOT 2",20)/2, botaoSAVE2.rect.y + botaoSAVE2.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAVE3.rect, botaoSAVE3.cor);
            DrawText("SLOT 3", botaoSAVE3.rect.x + botaoSAVE3.rect.width/2 - MeasureText("SLOT 3",20)/2, botaoSAVE3.rect.y + botaoSAVE3.rect.height/2 - 20/2,20, BLACK);
            DrawRectangleRec(botaoSAVE4.rect, botaoSAVE4.cor);
            DrawText("SLOT 4", botaoSAVE4.rect.x + botaoSAVE4.rect.width/2 - MeasureText("SLOT 4",20)/2, botaoSAVE4.rect.y + botaoSAVE4.rect.height/2 - 20/2,20, BLACK);

        }
        break;
        default:
            break;
        }
        EndDrawing();
    }
    CloseWindow(); //fecha a janela
    return 0;
}
