#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED



#endif // FUNCOES_H_INCLUDED

#define ALTURA_MAPA 30
#define LARGURA_MAPA 60

#define ALTURA_BLOCO 20
#define LARGURA_BLOCO 20

#define TAM_POPUP 200

char mapa[ALTURA_MAPA][LARGURA_MAPA];

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

    for(int i = 0; i < TAM; i++)
    {



        if(mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'W' || mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'W')
        {
                Inimigo->dx = 0;

                if(mapa[(int)(Inimigo->y )/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y)/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] == 'W')
                    Inimigo->dy = 1;

                if(mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] == 'W')
                    Inimigo->dy = -1;
            }



        if(mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y - 1)/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] == 'W' || mapa[(int)(Inimigo->y + ALTURA_BLOCO)/ALTURA_BLOCO][(int)Inimigo->x/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO - 1)/LARGURA_BLOCO] == 'W')
        {
                Inimigo->dy = 0;

                if(mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Inimigo->x - 1)/LARGURA_BLOCO] == 'W')
                    Inimigo->dx = 1;

                if(mapa[(int)Inimigo->y/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'W' && mapa[(int)(Inimigo->y + ALTURA_BLOCO - 1)/ALTURA_BLOCO][(int)(Inimigo->x + LARGURA_BLOCO)/LARGURA_BLOCO] == 'W')
                    Inimigo->dx = -1;
            }


        Inimigo->y += Inimigo->dy*5;
        printf("Inimigo.dy %d = %d\n", Inimigo, Inimigo->dy);

        Inimigo->x += Inimigo->dx*5;
        printf("Inimigo.dx = %d\n", Inimigo->dx);

        Inimigo++;
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
